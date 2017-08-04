#!/usr/bin/env python

import tkinter

import sys

root = tkinter.Tk()

radio_var = tkinter.StringVar()

radio1 = tkinter.Radiobutton(root, variable=radio_var, value="Assembler",
                             text="Assembler")

radio2 = tkinter.Radiobutton(root, variable=radio_var, value="Basic",
                             text="Basic")

radio3 = tkinter.Radiobutton(root, variable=radio_var, value="Brainfuck",
                             text="Brainfuck")

radio4 = tkinter.Radiobutton(root, variable=radio_var, value="C",
                             text="C")

radio5 = tkinter.Radiobutton(root, variable=radio_var, value="Python",
                             text="Python")

showButton = tkinter.Button(root, text="Show var",
                            command=lambda: print(radio_var.get()))

quitButton = tkinter.Button(root, text="Exit", background='#ff8080',
                            command=exit)

radio1.grid(column=1, row=1)
radio2.grid(column=1, row=2)
radio3.grid(column=1, row=3)
radio4.grid(column=1, row=4)
radio5.grid(column=1, row=5)

showButton.grid(column=2, row=6, sticky="we", padx=6, pady=6)
quitButton.grid(column=2, row=7, sticky="we", padx=6, pady=6)

root.mainloop()
