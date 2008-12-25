import Graphics

class NotesPlane(Graphics.DrawerNode):
    def __init__(self, song):
        self._song = song
        self._lyrics = song.lyrics
        self._syllable = 0

    def emphasize(self, position):
        pass

    def blink(self, position):
        pass

    def failure(self, position, delta):
        pass

    def _next_line(self)

    # The callback
    def _next_syllable(self): 
        pass

    def draw(self):
        pass
