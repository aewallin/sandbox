
#pragma once

#include <QMainWindow>

class QPushButton;
class QGraphicsView;
class QGraphicsScene;
class QPlainTextEdit;

class MainWindow : public QMainWindow { 
    Q_OBJECT
public:
    MainWindow(QWidget * parent = 0L);
    virtual ~MainWindow();

signals:
    void runPythonCode(QString);

private slots:
    void runPythonCode();

public:
    QGraphicsView * viewer;
    QGraphicsScene * scene;
    QPlainTextEdit * editor;
    QPushButton * pb_commit;
};

