 #ifndef MANDELBROTWIDGET_H
 #define MANDELBROTWIDGET_H

 #include <QPixmap>
 #include <QWidget>

 #include "renderthread.hpp"

 class MandelbrotWidget : public QWidget
 {
     Q_OBJECT

 public:
     MandelbrotWidget(QWidget *parent = 0);

 protected:
     void paintEvent(QPaintEvent *event);
     void resizeEvent(QResizeEvent *event);
     void keyPressEvent(QKeyEvent *event);
     void wheelEvent(QWheelEvent *event);
     void mousePressEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);

 private slots:
     void updatePixmap(const QImage &image, double scaleFactor);

 private:
     void zoom(double zoomFactor);
     void scroll(int deltaX, int deltaY);

     RenderThread thread;
     QPixmap pixmap;
     QPoint pixmapOffset;
     QPoint lastDragPos;
     double centerX;
     double centerY;
     double pixmapScale;
     double curScale;
 };

 #endif
