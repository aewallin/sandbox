import sys
from PyQt4.QtCore import pyqtSlot
from PyQt4.QtGui import *

# create our window
app = QApplication(sys.argv)
w = QWidget()
w.setWindowTitle('Button click example @pythonspot.com')

# Create a button in the window
btn = QPushButton('Click me', w)

# Create the actions
@pyqtSlot()
def on_click():
	print('clicked')

@pyqtSlot()
def on_press():
	print('pressed')

@pyqtSlot()
def on_release():
	print('released')

# connect the signals to the slots
btn.clicked.connect(on_click)
btn.pressed.connect(on_press)
btn.released.connect(on_release)

# Show the window and run the app
w.show()
app.exec_()
