from GL import *
from Scene import SceneNode

def _is_power_of_2(i):
    if i == 0:
        return False
    while i != 1:
        if i % 2:
            return False
        i = i // 2
    return True

class TextureDrawer(SceneNode):
    def __init__(self, data, width, height, blend = False):
        self._data = data
        self._width = width
        self._height = height
        self._blend = blend
        self._texture_handle = 0
        if _is_power_of_2 (width * height):
            self._texture_mode = GL_TEXTURE_2D
        else:
            self._texture_mode = GL_TEXTURE_2D # GL_TEXTURE_RECTANGLE
        super(TextureDrawer, self).__init__()

    def initialize(self):
        self._texture_handle = glGenTextures(1)
        glBindTexture(self._texture_mode, self._texture_handle)
        glTexImage2D(self._texture_mode, 0, GL_RGBA, self._width, self._height, \
                     0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, self._data)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
        del self._data
        
    def draw(self):
        if self._blend:
            glEnable(GL_BLEND)
            glBlendEquation(GL_MAX)
        glEnable(self._texture_mode)
        glBindTexture(self._texture_mode, self._texture_handle)
        glBegin(GL_QUADS)
        glTexCoord2f(0, 0)
        glVertex(0, 0)
        glTexCoord2f(0, 1)
        glVertex(0, self._height)
        glTexCoord2f(1, 1)
        glVertex(self._width, self._height)
        glTexCoord2f(1, 0)
        glVertex(self._width, self._height)
        glEnd()
        glDisable(self._texture_mode)
        if self._blend:
            glDisable(GL_BLEND)

    def uninitialize(self):
        glDeleteTextures(self._texture_handle)

