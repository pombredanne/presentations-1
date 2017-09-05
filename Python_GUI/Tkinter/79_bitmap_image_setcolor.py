#!/usr/bin/env python

import tkinter
from tkinter import ttk
import sys


WIDTH = 400
HEIGHT = 400
GRID_SIZE = 100


def exit():
    sys.exit(0)


def basic_canvas(root, width, height, grid_size):
    canvas = tkinter.Canvas(root, width=width, height=height,
                            background='#ccffcc')
    canvas.pack()

    draw_grid(canvas, width, height, grid_size)
    return canvas


def draw_grid(canvas, width, height, grid_size):
    for x in range(0, width, grid_size):
        canvas.create_line(x, 0, x, height, dash=7, fill="gray")
    for y in range(0, height, grid_size):
        canvas.create_line(0, y, width, y, dash=7, fill="gray")


root = tkinter.Tk()

bitmap_image = tkinter.BitmapImage(file="test.xbm",
                                   background="black",
                                   foreground="yellow")

canvas = basic_canvas(root, WIDTH, HEIGHT, GRID_SIZE)

canvas.create_image((200, 200), image=bitmap_image)

root.mainloop()
