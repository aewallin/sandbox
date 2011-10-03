

//
// an attempt in October 2011 to convert this example 
// http://doc.qt.nokia.com/qq/qq06-glimpsing.html#writingmultithreadedglapplications
// from 2003 into something that compiles and runs on qt47.
//
// Anders Wallin, anders.e.e.wallin@gmail.com
//
// double-buffering doesn't seem to work.


#include <QApplication>
#include <Qt>

#include "appwindow.hpp"
#include <X11/Xlib.h>

int main(int argc, char *argv[])
{
    // this would maybe work in qt4.8: QApplication::setAttribute(  Qt::AA_X11InitThreads );
    XInitThreads();
    
    QApplication app(argc, argv); 
    AppWindow aw;
    aw.show();
    return app.exec();
}
