class Song(_star.song):
    def __init__(self, name):
        from os.path import join
        super(Song, self).__init__(join("..", "examples", name + ".star"))

def SongSelector():
    pass

class Player(_star.player):
    def __init__(self, song = None):
        self._song = song
        super(Player, self).__init__()

    def start(self, song = None):
        if super(Player, self).is_playing():
            return
        if song != None:
            super(Player, self).start(song)
        else:
            if self._song == None:
                return
            else:
                super(Player, self).start(self._song)

