import standard

if __name__ == "__main__":
    song = Tools.SongSelector().select(supports = "duet")
    lyrics_out = Display.compose(Lyrics().Split(2))
    song.start(lyrics_output = lyrics_out)

