#!/usr/bin/env python

from tkinter import *
from tkinter import ttk

import sys


def exit():
    sys.exit(0)


root = Tk()

style = ttk.Style()
style.configure('Red.TButton', background='#ff8080')

button1 = Button(root, text="sunken", relief="sunken")
button2 = Button(root, text="solid", relief="solid")
button3 = Button(root, text="flat", relief="flat")
button4 = Button(root, text="groove", relief="groove")
button5 = Button(root, text="raised", relief="raised")
button6 = Button(root, text="ridge", relief="ridge")

quitButton = ttk.Button(root, text="Exit", style='Red.TButton',
                        command=exit)

button1.grid(column=1, row=1, sticky="we")
button2.grid(column=1, row=2, sticky="we")
button3.grid(column=1, row=3, sticky="we")
button4.grid(column=1, row=4, sticky="we")
button5.grid(column=1, row=5, sticky="we")
button6.grid(column=1, row=6, sticky="we")

quitButton.grid(column=2, row=6, sticky="we")

root.mainloop()
