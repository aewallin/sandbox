from PyQt4 import QtGui
from PyQt4 import QtCore
import sys
 
def main():
 
	app 	= QtGui.QApplication(sys.argv)
	tabs	= QtGui.QTabWidget()
 
	# Create tabs
	tab1	= QtGui.QWidget()
	tab2	= QtGui.QWidget()
	tab3	= QtGui.QWidget()
	tab4	= QtGui.QWidget()
 
	# Resize width and height
	tabs.resize(250, 150)
 
	# Set layout of first tab
	vBoxlayout	= QtGui.QVBoxLayout()
	pushButton1 = QtGui.QPushButton("Start")
	pushButton2 = QtGui.QPushButton("Settings")
	pushButton3 = QtGui.QPushButton("Stop")
	vBoxlayout.addWidget(pushButton1)
	vBoxlayout.addWidget(pushButton2)
	vBoxlayout.addWidget(pushButton3)
	tab1.setLayout(vBoxlayout)
 
	# Add tabs
	tabs.addTab(tab1,"Tab 1")
	tabs.addTab(tab2,"Tab 2")
	tabs.addTab(tab3,"Tab 3")
	tabs.addTab(tab4,"Tab 4")
 
	# Set title and show
	tabs.setWindowTitle('PyQt QTabWidget @ pythonspot.com')
	tabs.show()
 
	sys.exit(app.exec_())
 
if __name__ == '__main__':
	main()
