#include <QTime>
#include <QtDebug>
#include <QMutexLocker>

#include "simpleviewer.hpp"
#include "gldata.hpp"

using namespace std;

Viewer::Viewer(QWidget *parent)  {
    g = new GLData();
    glt = new GLThread(g);
    glt->start(); // makes and updates the GLData
    connect( glt, SIGNAL( signalUpdate() ),     // when glthread has a modified the gldata
           this,   SLOT(  slotDraw() )   );     // draw it by calling updateGL
               
}

Viewer::~Viewer() {
    glt->stop();
    glt->wait();
    delete glt;
    delete g;
}

// Draws a spiral
void Viewer::draw()
{
    qDebug() << QTime::currentTime() << " Viewer::draw() ";
    drawGLData(g);
}

void Viewer::drawGLData(GLData* gl) {
    QMutexLocker locker( &(g->mutex) );
    glPolygonMode( gl->polygonMode_face, gl->polygonMode_mode ); 
    // draw using vertex-array
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    // http://www.opengl.org/sdk/docs/man/xhtml/glNormalPointer.xml
    //                 type,                          stride,                 offset/pointer
    glNormalPointer( GLData::coordinate_type, sizeof( GLData::vertex_type ),    ((GLbyte*)g->getVertexArray()  + GLData::normal_offset ) );
    // http://www.opengl.org/sdk/docs/man/xhtml/glColorPointer.xml
    //             coords/vert,                    type,                        stride,  offset/pointer
    glColorPointer(  3, GLData::color_type     , sizeof( GLData::vertex_type ), ((GLbyte*)g->getVertexArray()  + GLData::color_offset  ) ); 
    glVertexPointer( 3, GLData::coordinate_type, sizeof( GLData::vertex_type ), ((GLbyte*)g->getVertexArray()  + GLData::vertex_offset  ) ); 
    // http://www.opengl.org/sdk/docs/man/xhtml/glDrawElements.xml
    //              mode       idx-count             type               offset/pointer
    glDrawElements( gl->type , gl->indexCount() , GLData::index_type, g->getIndexArray());
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    
}

void Viewer::postDraw() {
    QGLViewer::postDraw();
    drawCornerAxis();
}

void Viewer::init() {
  // Restore previous viewer state.
  restoreStateFromFile();
  // Opens help window
  help();
}

void Viewer::drawCornerAxis() {
    int viewport[4];
    int scissor[4];
    // The viewport and the scissor are changed to fit the lower left
    // corner. Original values are saved.
    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetIntegerv(GL_SCISSOR_BOX, scissor);
    // Axis viewport size, in pixels
    const int size = 150;
    glViewport(0,0,size,size);
    glScissor(0,0,size,size);
    // The Z-buffer is cleared to make the axis appear over the
    // original image.
    glClear(GL_DEPTH_BUFFER_BIT);
    // Tune for best line rendering
    glDisable(GL_LIGHTING);
    glLineWidth(3.0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glMultMatrixd( camera()->orientation().inverse().matrix() );
    glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0); // red X-axis
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);
        glColor3f(0.0, 1.0, 0.0); // green Y-axis
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);
        glColor3f(0.0, 0.0, 1.0); // blue Z-axis
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    // The viewport and the scissor are restored.
    glScissor(scissor[0],scissor[1],scissor[2],scissor[3]);
    glViewport(viewport[0],viewport[1],viewport[2],viewport[3]);
}


QString Viewer::helpString() const {
  QString text("<h2>S i m p l e V i e w e r</h2>");
  text += "Use the mouse to move the camera around the object. ";
  text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
  text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
  text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
  text += "Simply press the function key again to restore it. Several keyFrames define a ";
  text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
  text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
  text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
  text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
  text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
  text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
  text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
  text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
  text += "Press <b>Escape</b> to exit the viewer.";
  return text;
}
