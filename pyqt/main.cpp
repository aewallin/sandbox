
#include <QtGui>

#include "mainwindow.hpp"

int main(int argc, char ** argv) {
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(1000,700);
    window.show();
    return app.exec();
}
