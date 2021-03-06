#!/usr/bin/env python

from appJar import gui
import tkinter


def onMenuItemSelect(menuItem):
    if menuItem == "Quit":
        app.stop()


app = gui()

app.setSticky("news")

fileMenu = ["Quit"]
app.addMenuList("File", fileMenu, onMenuItemSelect)

app.addMicroBit("microbit")
app.setMicroBitImage("microbit", "90009:99099:90909:90009:90009")
app.go()
