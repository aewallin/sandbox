
#include <QTime>
#include <QtDebug>
#include <GL/glut.h>

#include "glthread.hpp"
#include "glwidget.hpp"

GLThread::GLThread(GLWidget *glWidget) : QThread(), glw(glWidget)
{
    qDebug() << "GLThread constructor..";
    doRendering = true;
    doResize = false;
    qDebug() << "done";
}
    
void GLThread::resizeViewport(const QSize &size){
    qDebug() << "resizeViewport..";
    w = size.width();
    h = size.height();
    doResize = true;
    qDebug() << "done";
}   
void GLThread::run(){
    qDebug() << "run..";
    //srand(QTime::currentTime().msec());
    rotAngle = rotAngle + 0.1; //rand() % 360;
        
    glw->makeCurrent();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();        
    glOrtho(-5.0, 5.0, -5.0, 5.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, 200, 200);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    
    
    while (doRendering) {
        if (doResize) {
            glViewport(0, 0, w, h);
            doResize = false;
        }
        // Rendering code goes here
        glDrawTriangle();
        //
        glw->swapBuffers();
        msleep(400);
    }
    qDebug() << "done";
}
void GLThread::stop()   {
    doRendering = false;
}
    
void GLThread::glDrawTriangle() {
    glRotatef(rotAngle,0.0f,1.0f,0.0f);		// Rotate The Pyramid On The Y axis 

    // draw a pyramid (in smooth coloring mode)
    glBegin(GL_POLYGON);				// start drawing a pyramid

    // front face of pyramid
    glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
    glVertex3f(0.0f, 1.0f, 0.0f);		        // Top of triangle (front)
    glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Green
    glVertex3f(-1.0f,-1.0f, 1.0f);		// left of triangle (front)
    glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
    glVertex3f(1.0f,-1.0f, 1.0f);		        // right of traingle (front)	

    // right face of pyramid
    glColor3f(1.0f,0.0f,0.0f);			// Red
    glVertex3f( 0.0f, 1.0f, 0.0f);		// Top Of Triangle (Right)
    glColor3f(0.0f,0.0f,1.0f);			// Blue
    glVertex3f( 1.0f,-1.0f, 1.0f);		// Left Of Triangle (Right)
    glColor3f(0.0f,1.0f,0.0f);			// Green
    glVertex3f( 1.0f,-1.0f, -1.0f);		// Right Of Triangle (Right)

    // back face of pyramid
    glColor3f(1.0f,0.0f,0.0f);			// Red
    glVertex3f( 0.0f, 1.0f, 0.0f);		// Top Of Triangle (Back)
    glColor3f(0.0f,1.0f,0.0f);			// Green
    glVertex3f( 1.0f,-1.0f, -1.0f);		// Left Of Triangle (Back)
    glColor3f(0.0f,0.0f,1.0f);			// Blue
    glVertex3f(-1.0f,-1.0f, -1.0f);		// Right Of Triangle (Back)

    // left face of pyramid.
    glColor3f(1.0f,0.0f,0.0f);			// Red
    glVertex3f( 0.0f, 1.0f, 0.0f);		// Top Of Triangle (Left)
    glColor3f(0.0f,0.0f,1.0f);			// Blue
    glVertex3f(-1.0f,-1.0f,-1.0f);		// Left Of Triangle (Left)
    glColor3f(0.0f,1.0f,0.0f);			// Green
    glVertex3f(-1.0f,-1.0f, 1.0f);		// Right Of Triangle (Left)

    glEnd();					// Done Drawing The Pyramid
}
