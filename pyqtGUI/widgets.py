#! /usr/bin/env python
# -*- coding: utf-8 -*-
#
import sys
from PyQt4.QtGui import *
 
# Create an PyQT4 application object.
a = QApplication(sys.argv)
 
# The QWidget widget is the base class of all user interface objects in PyQt4.
w = QMainWindow()
 
# Set window size.
w.resize(320, 100)
 
# Set window title
w.setWindowTitle("PyQT Python Widget!")
 
# Create textbox
textbox = QLineEdit(w)
textbox.move(20, 20)
textbox.resize(280,40)
 

# Create combobox
combo = QComboBox(w)
combo.addItem("Python")
combo.addItem("Perl")
combo.addItem("Java")
combo.addItem("C++")
combo.move(20,20)


# Create calendar
cal = QCalendarWidget(w)
cal.setGridVisible(True)
cal.move(0, 0)
cal.resize(320,240)

# Show window
w.show()
 
sys.exit(a.exec_())
