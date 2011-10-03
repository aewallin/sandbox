
#ifndef GLTHREAD
#define GLTHREAD

#include <QObject>
#include <QThread>
#include <QSize>

class GLWidget;

class GLThread : public QThread {
    Q_OBJECT
public:
    GLThread(GLWidget *glWidget);
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
    GLWidget *glw;
    int id;
    static int count;
};
    
#endif
