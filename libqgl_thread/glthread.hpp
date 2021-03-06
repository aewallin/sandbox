#ifndef GLTHREAD_HPP
#define GLTHREAD_HPP

#include <QObject>
#include <QThread>
#include <QSize>

#include <vector>

#include "glvertex.hpp"
#include "nanotimer.hpp"

class GLData;

class GLThread : public QThread {
    Q_OBJECT
public:
    GLThread(GLData *gl);
    void run();
    void stop();
signals:
    void signalUpdate(); // when data is modified, emit signalUpdate()
private:
    void makeData();
    GLData* g;
    bool doRendering;
    float rotAngle;
    int id;
    static int count;
    std::vector<GLVertex> verts;
    Nanotimer timer;
    int sleepMilliseconds;
};
    
#endif
