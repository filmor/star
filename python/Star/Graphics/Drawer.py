from OpenGL.GL import glPushMatrix, glPopMatrix

def glProtectMatrix(func):
    def wrapper(*args, **kwargs):
        glPushMatrix()
        res = func(*args, **kwargs)
        glPopMatrix()
        return res
    return wrapper

class Drawer:
    def __init__(self):
        _star.enqueue_init(self.once)
        _star.set_drawer(self)
        self.dimensions = _star.get_dimensions()

    def once(self):
        pass

    def __call__(self):
        pass

