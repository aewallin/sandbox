#ifndef VIEWER
#define VIEWER

#include <QGLViewer/qglviewer.h>
#include <QObject>
#include <QThread>
#include <QGLWidget>
#include <QResizeEvent>
#include <QtDebug>
#include <QVarLengthArray>

#include "gldata.hpp"

class Viewer : public QGLViewer {
public:
    Viewer(QWidget *parent);
protected :
    void drawGLData(GLData* gl);
    void drawImmediate();
    //GLThread glt;
    void makeData();
    virtual void draw(); // also emits drawNeeded()
    virtual void init();
    virtual QString helpString() const;
    GLData* g;
};

#endif
