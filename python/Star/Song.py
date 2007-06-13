def Song(name):
    import os
    from os.path import join
    return _star.song(join("..", "examples", name + ".star"))

def SongSelector():
    pass

def Player():
    return _star.player()
