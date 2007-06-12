from OpenGL.GLU import *
from OpenGL.GL import *

from Drawer import *

class SimpleDrawer(Drawer):
    @glProtectMatrix
    def __call__(self):
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        glLoadIdentity()
        glTranslatef(-1.5,0,-6)
        glColor3f(*self.Color)
        glBegin(GL_TRIANGLES)
        glVertex3f(1,0,1)
        glVertex3f(0,1,1)
        glVertex3f(1,1,-6)
        glEnd()
        glTranslatef(3.0, 0.0, 0.0)
        self.Color[0] += 0.001
        self.Color[1] -= 0.001
        self.Color[2] -= 0.001
    def once(self):
        self.Color = [ 0, 1, 1 ]

def Gradient(fStartX, fStartY, fWidth, fHeight):
    glBegin (GL_QUADS)

    glColor3f(0.85, 0.85, 0.85)
    glVertex3f(fStartX, fStartY, 0.0)
    glColor3f(0.85, 0.85, 0.85)
    glVertex3f(fStartX + fWidth, fStartY, 0.0)
    glColor3f(1.0, 1.0, 1.0)
    glVertex3f(fStartX + fWidth, fStartY + fHeight / 3.0, 0.0)
    glColor3f(1.0, 1.0, 1.0)
    glVertex3f(fStartX, fStartY + fHeight / 3.0, 0.0)

    glColor3f (1.0, 1.0, 1.0)
    glVertex3f(fStartX, fStartY + fHeight / 3.0, 0.0)
    glVertex3f(fStartX + fWidth, fStartY + fHeight / 3.0, 0.0)
    glVertex3f(fStartX + fWidth, fStartY + 2.0 * fHeight / 3.0, 0.0)
    glVertex3f(fStartX, fStartY + 2.0 * fHeight / 3.0, 0.0)

    glColor3f(1.0, 1.0, 1.0)
    glVertex3f(fStartX, fStartY + 2.0 * fHeight / 3.0, 0.0)
    glColor3f(1.0, 1.0, 1.0)
    glVertex3f(fStartX + fWidth, fStartY + 2.0 * fHeight / 3.0, 0.0)
    glColor3f(0.62, 0.66, 0.69)
    glVertex3f(fStartX + fWidth, fStartY + fHeight, 0.0)
    glColor3f(0.62, 0.66, 0.69)
    glVertex3f(fStartX, fStartY + fHeight, 0.0)
    glEnd()


class BackgroundDrawer(Drawer):
    @glProtectMatrix
    def __call__(self):
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()

        gluOrtho2D (0, self.dimensions[0], 0, self.dimensions[1])
        glDisable (GL_TEXTURE_RECTANGLE_ARB);
        glDisable (GL_TEXTURE_2D);
        glDisable (GL_LIGHTING);

        Gradient(0, 0, self.dimensions[0], self.dimensions[1])

        glEnable (GL_TEXTURE_2D);
        glEnable (GL_LIGHTING);
