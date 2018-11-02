#!/usr/bin/env python
# vim: set fileencoding=utf-8

# Demonstrační příklady využívající knihovnu Pyglet

import pyglet


window = pyglet.window.Window(width=640,
                              height=480,
                              caption="Pyglet library")


@window.event
def on_draw():
    window.clear()


pyglet.app.run()
