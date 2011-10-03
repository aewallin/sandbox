
#ifndef APPWINDOW
#define APPWINDOW

#include <QObject>
#include <QThread>
#include <QGLWidget>
#include <QWorkspace>
#include <QMainWindow>
#include <QMenuBar>

#include "glthread.hpp"
#include "glwidget.hpp"

class AppWindow : public QMainWindow {
        Q_OBJECT
    public:
        AppWindow(): QMainWindow(0)
        {
            exitAction = new QAction(tr("E&xit"), this);
            exitAction->setShortcut(tr("Ctrl+X"));
            exitAction->setStatusTip(tr("Exit the application"));
            connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
            
            newThreadAction = new QAction(tr("New Thread"), this);
            newThreadAction->setShortcut(tr("Ctrl+N"));
            newThreadAction->setStatusTip(tr("&New thread"));
            connect(newThreadAction, SIGNAL(triggered()), this, SLOT(newThread()) );
            
            killThreadAction = new QAction(tr("Kill Thread"), this);
            killThreadAction->setShortcut(tr("Ctrl+K"));
            killThreadAction->setStatusTip(tr("&Kill thread"));
            connect(killThreadAction, SIGNAL(triggered()), this, SLOT(killThread()) );
            
            tMenu = menuBar()->addMenu( tr("&Thread") );
                tMenu->addAction( newThreadAction );
                tMenu->addAction( killThreadAction );
                tMenu->addSeparator();
                tMenu->addAction( exitAction );

            ws = new QWorkspace(this);
            setCentralWidget(ws);
        }
    
    protected:
        void closeEvent(QCloseEvent *evt){
            QWidgetList windows = ws->windowList();
            for (int i = 0; i < int(windows.count()); ++i) {
                GLWidget *window = (GLWidget *)windows.at(i);
                window->stopRendering();
            }
            QMainWindow::closeEvent(evt);
        }
    
    private slots:
        void newThread(){
            QWidgetList windows = ws->windowList();
            GLWidget *widget = new GLWidget(ws);
            widget->setWindowTitle("Thread #" + QString::number(windows.count() + 1));
            widget->show();
            widget->startRendering();
            ws->addWindow(widget);
        }
        void killThread(){
            GLWidget *widget = (GLWidget *)ws->activeWindow();    
            if (widget) {
                widget->stopRendering();
                delete widget;
            }
        }
        
    private:
        QWorkspace *ws;
        QMenu *tMenu;
        QAction *exitAction;
        QAction *newThreadAction;
        QAction *killThreadAction;
};


#endif
