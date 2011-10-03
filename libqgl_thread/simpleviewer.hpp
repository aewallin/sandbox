
#ifndef VIEWER
#define VIEWER

#include <QGLViewer/qglviewer.h>

#include <QObject>
#include <QThread>
#include <QGLWidget>
#include <QResizeEvent>
#include <QtDebug>

#include "glthread.hpp"

class Viewer : public QGLViewer {
public:
    Viewer(QWidget *parent) :  glt(this) {
        //glt= GLThread(this);
        //this->doneCurrent();
    }
    //void startRendering() {
    //    glt.start();
    //}
    void stopRendering(){
        glt.stop();
        glt.wait();
    }
protected :
    void resizeEvent(QResizeEvent *evt) {
        glt.resizeViewport(evt->size());
        //this->doneCurrent();
    }
    void paintEvent(QPaintEvent *){
        // Handled by the GLThread.
        this->doneCurrent();
    }
    void closeEvent(QCloseEvent *evt){
        stopRendering();
        QGLViewer::closeEvent(evt);
    }
    
    GLThread glt;
    virtual void draw(); // also emits drawNeeded()
    virtual void init();
    virtual QString helpString() const;
};

#endif
