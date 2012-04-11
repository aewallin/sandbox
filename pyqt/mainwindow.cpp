#include <QtGui>

#include <boost/python.hpp>
namespace bp = boost::python;

#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent) {
    QSplitter * splitter = new QSplitter;
    setCentralWidget(splitter);

    QWidget * editorContent = new QWidget;
    splitter->addWidget(editorContent);

    QVBoxLayout * layout = new QVBoxLayout;
    editorContent->setLayout(layout);

    editor = new QPlainTextEdit;
    layout->addWidget(editor);

    pb_commit = new QPushButton(tr("Commit"));
    connect(pb_commit, SIGNAL(clicked()),
            this, SLOT(runPythonCode()));
    layout->addWidget(pb_commit);

    scene = new QGraphicsScene(this);
    viewer = new QGraphicsView;
    viewer->setScene(scene);
    splitter->addWidget(viewer);

    splitter->setSizes(QList<int>() << 400 << 600);
}

MainWindow::~MainWindow() {;}

void MainWindow::runPythonCode() {
    emit runPythonCode(editor->toPlainText());
}

BOOST_PYTHON_MODULE(mainwindow) {
    bp::class_<MainWindow, boost::noncopyable>("MainWindow" )
    ;
}
