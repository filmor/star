def SongInfo(name):
    import os
    from os.path import join
    return _star.song_info(join("..", "examples", name + ".star"))

def SongSelector():
    pass

def Song():
    return _star.song()
