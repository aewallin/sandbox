#include <QtGui>

#include <cmath>

#include "mandelbrotwidget.hpp"

const double DefaultCenterX = -0.637011f;
const double DefaultCenterY = -0.0395159f;
const double DefaultScale = 0.00403897f;

const double ZoomInFactor = 0.8f;
const double ZoomOutFactor = 1 / ZoomInFactor;
const int ScrollStep = 20;

MandelbrotWidget::MandelbrotWidget(QWidget *parent)
 : QWidget(parent)
{
    centerX = DefaultCenterX;
    centerY = DefaultCenterY;
    pixmapScale = DefaultScale;
    curScale = DefaultScale;

    qRegisterMetaType<QImage>("QImage");
    connect(&thread, SIGNAL(renderedImage(QImage,double)),     // when RenderThread has a new QIMage ready
               this,   SLOT(updatePixmap(QImage,double))   ); // draw it by calling updatePixmap

    setWindowTitle(tr("Mandelbrot"));
    setCursor(Qt::CrossCursor);
    resize(550, 400);
}

void MandelbrotWidget::paintEvent(QPaintEvent * /* event */) {
    qDebug() << "MandelbrotWidget::paintEvent() ";
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    if (pixmap.isNull()) {
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, tr("Rendering initial image, please wait..."));
        return;
    }

    if (curScale == pixmapScale) {
        painter.drawPixmap(pixmapOffset, pixmap);
    } else {
        double scaleFactor = pixmapScale / curScale;
        int newWidth = int(pixmap.width() * scaleFactor);
        int newHeight = int(pixmap.height() * scaleFactor);
        int newX = pixmapOffset.x() + (pixmap.width() - newWidth) / 2;
        int newY = pixmapOffset.y() + (pixmap.height() - newHeight) / 2;

        painter.save();
        painter.translate(newX, newY);
        painter.scale(scaleFactor, scaleFactor);
        QRectF exposed = painter.matrix().inverted().mapRect(rect()).adjusted(-1, -1, 1, 1);
        painter.drawPixmap(exposed, pixmap, exposed);
        painter.restore();
    }

    QString text = tr("Use mouse wheel or the '+' and '-' keys to zoom. "
                   "Press and hold left mouse button to scroll.");
    QFontMetrics metrics = painter.fontMetrics();
    int textWidth = metrics.width(text);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 127));
    painter.drawRect((width() - textWidth) / 2 - 5, 0, textWidth + 10, metrics.lineSpacing() + 5);
    painter.setPen(Qt::white);
    painter.drawText((width() - textWidth) / 2, metrics.leading() + metrics.ascent(), text);
}

void MandelbrotWidget::resizeEvent(QResizeEvent * /* event */) {
    qDebug() << "MandelbrotWidget::resizeEvent() ";
    thread.render(centerX, centerY, curScale, size());
}

void MandelbrotWidget::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Plus:
            zoom(ZoomInFactor);
            break;
        case Qt::Key_Minus:
            zoom(ZoomOutFactor);
            break;
        case Qt::Key_Left:
            scroll(-ScrollStep, 0);
            break;
        case Qt::Key_Right:
            scroll(+ScrollStep, 0);
            break;
        case Qt::Key_Down:
            scroll(0, -ScrollStep);
            break;
        case Qt::Key_Up:
            scroll(0, +ScrollStep);
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void MandelbrotWidget::wheelEvent(QWheelEvent *event) {
    int numDegrees = event->delta() / 8;
    double numSteps = numDegrees / 15.0f;
    zoom(pow(ZoomInFactor, numSteps));
}

void MandelbrotWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        lastDragPos = event->pos();
}

void MandelbrotWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        pixmapOffset += event->pos() - lastDragPos;
        lastDragPos = event->pos();
        update();
    }
}

void MandelbrotWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        pixmapOffset += event->pos() - lastDragPos;
        lastDragPos = QPoint();
        int deltaX = (width() - pixmap.width()) / 2 - pixmapOffset.x();
        int deltaY = (height() - pixmap.height()) / 2 - pixmapOffset.y();
        scroll(deltaX, deltaY);
    }
}

// this slot is called from RenderThread when a new image is available
void MandelbrotWidget::updatePixmap(const QImage &image, double scaleFactor) {
    if (!lastDragPos.isNull())
        return;
    pixmap = QPixmap::fromImage(image);
    pixmapOffset = QPoint();
    lastDragPos = QPoint();
    pixmapScale = scaleFactor;
    update();
}

void MandelbrotWidget::zoom(double zoomFactor) {
    qDebug() << "MandelbrotWidget::zoom() ";
    curScale *= zoomFactor;
    update();
    thread.render(centerX, centerY, curScale, size());
}

void MandelbrotWidget::scroll(int deltaX, int deltaY) {
    qDebug() << "MandelbrotWidget::scroll() ";
    centerX += deltaX * curScale;
    centerY += deltaY * curScale;
    update();
    thread.render(centerX, centerY, curScale, size());
}
