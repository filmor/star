
from Plane import Plane

class LyricsPlane(Plane):
    def __init__(self, song):
        self.__song = song
        self.__text = song.lyrics.lines()

    def draw(self, output):
        s = self.__song
        t = self.__text

        if s.pos > self.__line[0]:
            self.__line = _get_line()
        
    def _get_line():
        for i in self.__text:
            yield i

