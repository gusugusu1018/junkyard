import sys
import os
import numpy as np
import matplotlib.pyplot as plt
from PyQt5 import QtCore, QtWidgets
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas

class Application(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.initFigure()

    def initUI(self):
        self.setGeometry(0,0,800,700)
        self.setWindowTitle('Ikenyzer')
        self.Lcd = QtWidgets.QLCDNumber(self)
        self.Slider = QtWidgets.QSlider(QtCore.Qt.Horizontal, self)
        self.Slider.valueChanged.connect(self.Lcd.display)
        self.Slider.valueChanged.connect(self.updateFigure)
        self.Filebutton = QtWidgets.QPushButton('Select File',self)
        self.FigureWidget = QtWidgets.QWidget(self)
        self.FigureLayout = QtWidgets.QVBoxLayout(self.FigureWidget)
        hbox = QtWidgets.QHBoxLayout()
        hbox.addStretch(1)
        hbox.addWidget(self.Slider)
        hbox.addWidget(self.Lcd)
        vbox = QtWidgets.QVBoxLayout()
        vbox.addStretch(1)
        vbox.addWidget(self.FigureWidget)
        vbox.addLayout(hbox)
        self.setLayout(vbox)

    def initFigure(self):
        self.Figure = plt.figure()
        self.FigureCanvas = FigureCanvas(self.Figure)
        self.FigureLayout.addWidget(self.FigureCanvas)
        self.t = np.arange(100)
        self.y = np.sin(self.t)
        self.axes = self.Figure.add_subplot(111)
        self.li, = self.axes.plot(self.t, self.y)

    def updateFigure(self, value):
        self.t = np.arange(100)
        self.y = np.sin(self.t*float(value)*.01)
        self.li, = self.axes.plot(self.t, self.y)
        self.FigureCanvas.draw()


if __name__ == '__main__':
    QApp = QtWidgets.QApplication(sys.argv)
    app = Application()
    app.show()
    sys.exit(QApp.exec_())