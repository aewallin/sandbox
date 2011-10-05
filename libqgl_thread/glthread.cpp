
#include <QTime>
#include <QtDebug>
#include <GL/glut.h>
#include <QMutexLocker>

#include <QGLViewer/qglviewer.h>

#include "glthread.hpp"
#include "gldata.hpp"

int GLThread::count = 0;

GLThread::GLThread(GLData* gl) : QThread(), g(gl) {
    id = count++;
    qDebug() << "time=" << QTime::currentTime().msec() << " thread=" << id << " Created";
}
  
void GLThread::run(){
    qDebug() << id << ":run..";
    makeData();

    while (doRendering) {
        rotAngle = rotAngle + (id+1)*3; // threads rotate pyramid at different rate!
        qDebug() << "time=" << QTime::currentTime().msec() << " thread=" << id << ":rendering...";

        g->mutex.lock();
        g->removeVertex(0);
        g->mutex.unlock();
        emit signalUpdate();
        msleep(400);
    }
}

void GLThread::stop()   {
    qDebug() << "time=" << QTime::currentTime().msec() << " thread=" << id << " STOP";
    doRendering = false;
}

void GLThread::makeData() {
    g->setQuadStrip();
    g->setPolygonModeFill();
    //g->setPolygonModeLine();
    //g->setPolygonModeFrontAndBack();
    g->setPolygonModeFront();
    const float nbSteps = 200.0;
    for (int i=0; i<nbSteps; ++i) {
        const float ratio = i/nbSteps;
        const float angle = 21.0*ratio;
        const float c = cos(angle);
        const float s = sin(angle);
        const float r1 = 1.0 - 0.8f*ratio;
        const float r2 = 0.8f - 0.8f*ratio;
        const float alt = ratio - 0.5f;
        const float nor = 0.5f;
        const float up = sqrt(1.0-nor*nor);
        
        const float red = 1.0f-ratio; const float gre=0.2f; const float blu=ratio;
        float nx= nor*c; float ny=up; float nz=nor*s;
        float p1_x=r1*c; float p1_y=alt; float p1_z=r1*s;
        float p2_x=r2*c; float p2_y=alt+0.05f; float p2_z=r2*s;
                
        std::vector<GLuint> p1;
        unsigned int id1 = g->addVertex( p1_x, p1_y, p1_z, red, gre, blu, nx, ny, nz );
        p1.push_back(id1);
        g->addPolygon(p1);
        std::vector<GLuint> p2;
        unsigned int id2 = g->addVertex( p2_x, p2_y, p2_z, red, gre, blu, nx, ny, nz );
        p2.push_back(id2);
        g->addPolygon(p2);
    }
}
