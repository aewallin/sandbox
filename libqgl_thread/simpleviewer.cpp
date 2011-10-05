#include <QTime>
#include <QtDebug>

#include "simpleviewer.hpp"
#include "gldata.hpp"

using namespace std;

Viewer::Viewer(QWidget *parent)  {
    g = new GLData();
    makeData();
}
// Draws a spiral
void Viewer::draw()
{
    qDebug() << QTime::currentTime() << " Viewer::draw() ";
    drawGLData(g);
    //drawImmediate();
}

void Viewer::drawImmediate() {
    const float nbSteps = 200.0;
    glBegin(GL_QUAD_STRIP);
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
        glColor3f(1.0-ratio, 0.2f , ratio);
        glNormal3f(nor*c, up, nor*s);
        glVertex3f(r1*c, alt, r1*s);
        glVertex3f(r2*c, alt+0.05f, r2*s);
    }
    glEnd();
}

void Viewer::makeData() {
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
        //glColor3f(1.0-ratio, 0.2f , ratio);
        //glNormal3f(nor*c, up, nor*s);
        //glVertex3f(r1*c, alt, r1*s);
        //glVertex3f(r2*c, alt+0.05f, r2*s);
                
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
  
void Viewer::drawGLData(GLData* gl) {

    // void glPolygonMode(GLenum  face,  GLenum  mode);
    // face = GL_FRONT | GL_BACK  | GL_FRONT_AND_BACK
    // mode = GL_POINT, GL_LINE, GL_FILL
    glPolygonMode( gl->polygonMode_face, gl->polygonMode_mode ); 
    glShadeModel(GL_FLAT);
         
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
    glDrawElements( gl->type , gl->polygonCount() , GLData::index_type, g->getIndexArray());
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void Viewer::init() {
  // Restore previous viewer state.
  restoreStateFromFile();
  // Opens help window
  help();
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
