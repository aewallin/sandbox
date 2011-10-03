
// attempt drawing to libqglviewer in a separate thread.

#include "simpleviewer.hpp"
#include <QApplication>
#include <X11/Xlib.h>
int main(int argc, char** argv)
{
    XInitThreads();
    QApplication application(argc,argv);
    Viewer viewer(0);
    viewer.setWindowTitle("simpleViewer");
    viewer.show();
    return application.exec();
}
