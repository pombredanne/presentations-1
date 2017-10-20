#!/usr/bin/env python

from appJar import gui


def onButtonPress(buttonName):
    if buttonName == "Quit":
        app.stop()
    else:
        msg = "You type: {text}".format(text=app.getEntry("Login:"))
        app.infoBox("You type:", msg)


app = gui()

app.setSticky("news")
app.setPadding(2, 2)

app.addLabelEntry("Login:", 0, 0, colspan=2)

app.addHorizontalSeparator(1, 0, colspan=3)

app.addButton("Show input", onButtonPress, 2, 1)
app.addButton("Quit", onButtonPress, 2, 2)

app.go()
