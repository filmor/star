from OpenGL.GL import *

def glProtectMatrix(func):
    def wrapper(*args, **kwargs):
        glPushMatrix()
        res = func(*args, **kwargs)
        glPopMatrix()
        return res
    return wrapper

