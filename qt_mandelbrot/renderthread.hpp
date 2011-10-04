#ifndef RENDERTHREAD_HPP
#define RENDERTHREAD_HPP

#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>

class QImage;

class RenderThread : public QThread {
    Q_OBJECT
public:
    RenderThread(QObject *parent = 0);
    ~RenderThread();
    void render(double centerX, double centerY, double scaleFactor, QSize resultSize);
signals:
    void renderedImage(const QImage &image, double scaleFactor); // triggers updatePixmap in parent-widget
protected:
    void run();
private:
    uint rgbFromWaveLength(double wave);

    QMutex mutex;
    QWaitCondition condition;
    double centerX;
    double centerY;
    double scaleFactor;
    QSize resultSize;
    bool restart;
    bool abort;
    enum { ColormapSize = 512 };
    uint colormap[ColormapSize];
};

#endif
