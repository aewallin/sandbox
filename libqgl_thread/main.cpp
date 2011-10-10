// attempt drawing to libqglviewer in a separate thread.
#include "simpleviewer.hpp"
#include <QApplication>
#include <QObject>
#include <QWidget>

#include <X11/Xlib.h>
int main(int argc, char** argv)
{
    XInitThreads();
    QApplication app(argc,argv);
    Viewer viewer(0);
    
    QObject::connect( &app, SIGNAL( lastWindowClosed() ),     // when glthread has a modified the gldata
           &viewer,   SLOT(  close() )   ); 
           
    viewer.setWindowTitle("simpleViewer");
    viewer.show();
    return app.exec();
}
