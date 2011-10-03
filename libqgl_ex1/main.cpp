
// This is the first libqglviewer example from:
// http://www.libqglviewer.com/examples/simpleViewer.html

#include "simpleviewer.hpp"
#include <QApplication>

int main(int argc, char** argv)
{
  QApplication application(argc,argv);
  Viewer viewer;
  viewer.setWindowTitle("simpleViewer");
  viewer.show();
  return application.exec();
}
