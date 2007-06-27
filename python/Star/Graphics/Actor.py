from Scene import SceneNode
from GL import glProtectMatrix

def Actor(function, arguments = ()):
    class _Actor(SceneNode):
        def __init__(self, *children):
            self.args = arguments
            super(Actor, self).__init__(*children)

        @glProtectMatrix
        def draw(self):
            function(*self.args)
            super(Actor, self).draw()

    return _Actor

def Rotator(angle, vector, *args):
    from OpenGL.GL import glRotatef
    return Actor(glRotatef, tuple([angle] + [ i for i in vector ]))(*args)

def Translator(vector, *args):
    from OpenGL.GL import glTranslate
    return Actor(glTranslate, *vector)(*args)

