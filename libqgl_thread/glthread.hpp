
#ifndef GLTHREAD_HPP
#define GLTHREAD_HPP

#include <QObject>
#include <QThread>
#include <QSize>

class Viewer;

class GLThread : public QThread {
    //Q_OBJECT
public:
    GLThread(Viewer *glWidget);
    void resizeViewport(const QSize &size);  
    void run();
    void stop();
private:
    void glDrawTriangle();
    bool doRendering;
    bool doResize;
    int w;
    int h;
    float rotAngle;
    Viewer *glw;
    int id;
    static int count;
};
    
#endif
