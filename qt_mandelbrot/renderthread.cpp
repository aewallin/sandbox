#include <QtGui>

#include <cmath>

#include "renderthread.hpp"

RenderThread::RenderThread(QObject *parent) : QThread(parent) {
    restart = false;
    abort = false;
    for (int i = 0; i < ColormapSize; ++i)
        colormap[i] = rgbFromWaveLength(380.0 + (i * 400.0 / ColormapSize));
}

RenderThread::~RenderThread() {
    mutex.lock();
        abort = true;
        condition.wakeOne();
    mutex.unlock();
    wait();
}

void RenderThread::render(double centerX, double centerY, double scaleFactor, QSize resultSize) {
    QMutexLocker locker(&mutex); // mutex locked for the whole of this function
        this->centerX = centerX;
        this->centerY = centerY;
        this->scaleFactor = scaleFactor;
        this->resultSize = resultSize;
        if (!isRunning()) {
            start(LowPriority);
        } else {
            restart = true;
            condition.wakeOne(); // allows the forever{} loop (below) to roll over
        }
}

void RenderThread::run() {
    forever {
        qDebug() << " RenderThread::run() ";
        mutex.lock(); // don't allow parent-thread to change these while we read them
            QSize resultSize = this->resultSize;
            double scaleFactor = this->scaleFactor;
            double centerX = this->centerX;
            double centerY = this->centerY;
        mutex.unlock();

        int halfWidth = resultSize.width() / 2;
        int halfHeight = resultSize.height() / 2;
        QImage image(resultSize, QImage::Format_RGB32); // new image

        const int NumPasses = 3;
        int pass = 0;
        while (pass < NumPasses) {
            const int MaxIterations = (1 << (2 * pass + 6)) + 32;
            const int Limit = 4;
            bool allBlack = true;

            for (int y = -halfHeight; y < halfHeight; ++y) {
                if (restart)
                    break;
                if (abort)
                    return;

                uint *scanLine = reinterpret_cast<uint *>(image.scanLine(y + halfHeight));
                double ay = centerY + (y * scaleFactor);

                for (int x = -halfWidth; x < halfWidth; ++x) {
                    double ax = centerX + (x * scaleFactor);
                    double a1 = ax;
                    double b1 = ay;
                    int numIterations = 0;
                    do {
                        ++numIterations;
                        double a2 = (a1 * a1) - (b1 * b1) + ax;
                        double b2 = (2 * a1 * b1) + ay;
                        if ((a2 * a2) + (b2 * b2) > Limit)
                        break;

                        ++numIterations;
                        a1 = (a2 * a2) - (b2 * b2) + ax;
                        b1 = (2 * a2 * b2) + ay;
                        if ((a1 * a1) + (b1 * b1) > Limit)
                            break;
                    } while (numIterations < MaxIterations);
                    if (numIterations < MaxIterations) {
                        *scanLine++ = colormap[numIterations % ColormapSize];
                        allBlack = false;
                    } else {
                        *scanLine++ = qRgb(0, 0, 0);
                    }
                }
            }

            if (allBlack && pass == 0) {
                pass = 4;
            } else {
                if (!restart) {
                    qDebug() << "   pass=" << pass << " emit renderedImage()";
                    emit renderedImage(image, scaleFactor); // triggers updatePixmap in parent-widget
                }
                ++pass;
            }
        }
        //qDebug() << " while() done.";
        
        mutex.lock();
            //qDebug() << " got mutex.";
            if (!restart) {
                condition.wait(&mutex); // release mutex, wait on condition( wakeOne() is called from render(), above)
                //qDebug() << " condition.wait(&mutex) done.";
            }
            restart = false;
        mutex.unlock();
    }
}

uint RenderThread::rgbFromWaveLength(double wave) {
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;

    if (wave >= 380.0 && wave <= 440.0) {
        r = -1.0 * (wave - 440.0) / (440.0 - 380.0);
        b = 1.0;
    } else if (wave >= 440.0 && wave <= 490.0) {
        g = (wave - 440.0) / (490.0 - 440.0);
        b = 1.0;
    } else if (wave >= 490.0 && wave <= 510.0) {
        g = 1.0;
        b = -1.0 * (wave - 510.0) / (510.0 - 490.0);
    } else if (wave >= 510.0 && wave <= 580.0) {
        r = (wave - 510.0) / (580.0 - 510.0);
        g = 1.0;
    } else if (wave >= 580.0 && wave <= 645.0) {
        r = 1.0;
        g = -1.0 * (wave - 645.0) / (645.0 - 580.0);
    } else if (wave >= 645.0 && wave <= 780.0) {
        r = 1.0;
    }

    double s = 1.0;
    if (wave > 700.0)
        s = 0.3 + 0.7 * (780.0 - wave) / (780.0 - 700.0);
    else if (wave <  420.0)
        s = 0.3 + 0.7 * (wave - 380.0) / (420.0 - 380.0);

    r = pow(r * s, 0.8);
    g = pow(g * s, 0.8);
    b = pow(b * s, 0.8);
    return qRgb(int(r * 255), int(g * 255), int(b * 255));
}
