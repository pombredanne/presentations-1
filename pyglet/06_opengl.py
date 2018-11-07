#!/usr/bin/env python
# vim: set fileencoding=utf-8

# Demonstrační příklady využívající knihovnu Pyglet

import pyglet
import pyglet.gl

# vytvoření okna
window = pyglet.window.Window(width=640,
                              height=480,
                              caption="Pyglet+OpenGL")


@window.event
def on_draw():
    pyglet.gl.glClear(pyglet.gl.GL_COLOR_BUFFER_BIT)
    pyglet.gl.glLoadIdentity()
    pyglet.gl.glBegin(pyglet.gl.GL_TRIANGLES)
    pyglet.gl.glVertex2f(0, 0)
    pyglet.gl.glVertex2f(window.width, 0)
    pyglet.gl.glVertex2f(window.width, window.height)
    pyglet.gl.glEnd()


pyglet.app.run()
