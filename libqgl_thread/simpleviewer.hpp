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
#include "glthread.hpp"

class Viewer : public QGLViewer {
    Q_OBJECT
public:
    Viewer(QWidget *parent);
    ~Viewer();
public slots:
    void slotDraw() { updateGL(); }
protected :
    void drawGLData(GLData* gl);
    virtual void draw(); // also emits drawNeeded()
    virtual void init();
    virtual void postDraw();
    virtual QString helpString() const;
    void drawCornerAxis();
    GLThread* glt;
    GLData* g;
};

#endif
