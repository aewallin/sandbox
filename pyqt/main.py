import sys
# sys.path.append('sip')

from PyQt4.QtCore import *
from PyQt4.QtGui import *
import mainwindow

class RunScript(QObject):
    def __init__(self, mainWindow):
        QObject.__init__(self)
        self.mainWindow = mainWindow

    def runScript(self, script):
        mainWindow = self.mainWindow
        exec(str(script))

a = QApplication(sys.argv)
w = mainwindow.MainWindow()
r = RunScript(w)
#w.setWindowTitle('PyQtHybrid')
#w.resize(1000,800)
#w.show()
a.connect(w, SIGNAL('runPythonCode(QString)'), r.runScript)
a.connect(a, SIGNAL('lastWindowClosed()'), a, SLOT('quit()') )
a.exec_()
