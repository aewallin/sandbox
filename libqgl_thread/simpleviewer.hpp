#ifndef VIEWER
#define VIEWER

#include <QGLViewer/qglviewer.h>
#include <QObject>
#include <QThread>
#include <QGLWidget>
#include <QResizeEvent>
#include <QtDebug>
#include <QVarLengthArray>
#include <QTime>

#include "gldata.hpp"
#include "glthread.hpp"

class Viewer : public QGLViewer {
    Q_OBJECT
public:
    Viewer(QWidget *parent);
    ~Viewer();
public slots:
    void slotNewDataWaiting() { 
        if ( time.elapsed() > 17)  // 60fps = 1 frame per 17 milliseconds)
            updateGL(); // only call if sufficient time elapsed since last draw()
    }
protected :
    void drawGLData(GLData* gl);
    virtual void draw(); // also emits drawNeeded()
    virtual void init();
    virtual void postDraw();
    virtual QString helpString() const;
    void drawCornerAxis();
    GLThread* glt;
    GLData* g;
    QTime time;
};

#endif
