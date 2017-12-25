#!/usr/bin/env python
# vim: set fileencoding=utf-8

import sys

# import "jádra" frameworku Qt i modulu pro GUI
from PySide import QtCore
from PySide import QtGui


# nový widget bude odvozen od obecného widgetu
class MainWindowContent(QtGui.QWidget):

    def __init__(self, parentWidget):
        # zavoláme konstruktor předka
        super(MainWindowContent, self).__init__()
        self._parentWidget = parentWidget

        # konfigurace GUI + přidání widgetu do okna
        self.prepareGUI()

    def prepareGUI(self):
        # tlačítko
        quitButton = QtGui.QPushButton('Quit', self)
        quitButton.resize(quitButton.sizeHint())

        # navázání akce na signál
        quitButton.clicked.connect(QtCore.QCoreApplication.instance().quit)

        # seznam prvků
        listWidget = QtGui.QListWidget(self)
        QtGui.QListWidgetItem(QtGui.QIcon('icons/battery-low.png'), u'0%', listWidget)
        QtGui.QListWidgetItem(QtGui.QIcon('icons/battery-040.png'), u'40%', listWidget)
        QtGui.QListWidgetItem(QtGui.QIcon('icons/battery-060.png'), u'60%', listWidget)
        QtGui.QListWidgetItem(QtGui.QIcon('icons/battery-080.png'), u'80%', listWidget)
        QtGui.QListWidgetItem(QtGui.QIcon('icons/battery-100.png'), u'100%', listWidget)

        # události vyvolávané manipulací se seznamem
        listWidget.itemActivated.connect(self.onItemActivated)
        listWidget.itemPressed.connect(self.onItemPressed)

        # vytvoření správce geometrie
        layout = QtGui.QVBoxLayout()

        # umístění widgetů do okna
        layout.addWidget(listWidget)
        layout.addWidget(quitButton)

        # nastavení správce geometrie a vložení všech komponent do okna
        self.setLayout(layout)

    def showMessage(self, message):
        self._parentWidget.statusBar().showMessage(message)

    def onItemPressed(self, item):
        message = u"kliknuto na prvek: {text}".format(text=item.text())
        self.showMessage(message)

    def onItemActivated(self, item):
        message = u"aktivován prvek: {text}".format(text=item.text())
        self.showMessage(message)


# nový widget bude odvozen od obecného hlavního okna
class MainWindow(QtGui.QMainWindow):

    def __init__(self):
        # zavoláme konstruktor předka
        super(MainWindow, self).__init__()

        # konfigurace GUI + přidání widgetu do okna
        self.prepareGUI()

    def prepareGUI(self):
        # velikost není potřeba specifikovat
        # self.resize(320, 240)
        self.setWindowTitle("QMainWindow + QListWidget")

        # vytvoření stavového řádku
        self.statusBar().showMessage('QMainWindow')

        # vložení komponenty do okna
        self.setCentralWidget(MainWindowContent(self))

    def run(self, app):
        # zobrazení okna na obrazovce
        self.show()
        # vstup do smyčky událostí (event loop)
        app.exec_()


def main():
    app = QtGui.QApplication(sys.argv)
    MainWindow().run(app)


if __name__ == '__main__':
    main()
