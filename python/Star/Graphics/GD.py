from ctypes import *
from GL import *
from Texture import TextureDrawer

try:
    import numpy
    zeros = lambda (tuple) : numpy.zeros(tuple, dtype=int)
except:
    import Numeric
    zeros = lambda (tuple) : Numeric.zeros(tuple, typecode='i')

try:
    gd = windll.bgd
except NameError:
    gd = CDLL("libgd.so")


gd.gdImageStringFT.argtypes = [
                                c_int, 
                                POINTER(c_int * 8), 
                                c_int, 
                                c_char_p, 
                                c_double, 
                                c_double, 
                                c_int, 
                                c_int, 
                                c_char_p
                              ]

gd.gdImageStringFT.restype = c_char_p

gd.gdImageCreate.restype = c_int


class GDImage(object):
    def __del__(self):
        gd.gdImageDestroy(self.img)

    def texture(self):
        data = zeros((self.width, self.height))
        for y in range(self.height):
            for x in range(self.width):
                data[y, x] = gd.gdImageGetTrueColorPixel(self.img, x, self.height - y)
        return data << 8 | 0xff


class String(GDImage):
    def __init__(self, string, size=40.):
        dimensions = (c_int * 8)()
        string = str(string)
        gd.gdImageStringFT(0, dimensions, 0, "verdana.ttf", size, 0., 0, 0, string)
        width = abs(dimensions[2] + dimensions[0])
        height = abs(dimensions[7] - dimensions[1])
        img = gd.gdImageCreateTrueColor(width, height)
        white = gd.gdImageColorResolve(img, 255, 255, 255)
        x, y = -dimensions[6], -dimensions[7]
        gd.gdImageStringFT(img, dimensions, white, "verdana.ttf", size, 0., 0, height, string)
        self.img = img
        self.width = width
        self.height = height
    
class StringDrawer(TextureDrawer):
    def __init__(self, string, size=40.):
        s = String(string, size)
        super(StringDrawer, self).__init__(s.texture(), s.height, s.width, 
                                           blend = True)


try:
    libc = cdll.mscvrt
except OSError:
    libc = CDLL("libc.so.6")

libc.fopen.argtypes = [c_char_p, c_char_p]

class PngDrawer(TextureDrawer):
    def __init__(self, filename, width, height):
        file = libc.fopen(filename, "rb")
        m = GDImage()
        m.img = gd.gdImageCreateFromPng(file)
        libc.fclose(file)
        m.width = width
        m.height = height
        super(PngDrawer, self).__init__(m.texture(), m.width, m.height, blend = True)

