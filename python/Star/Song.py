
def SongInfo(path):
    return _star.song_info(path)

def Song(str):
    info = SongInfo(str)
    return _star.song(info)
