import standard

if __name__ == "__main__":
    song = Tools.SongSelector().select(supports = "duet")
    
    Display = compose()
    song.start(lyrics_output = lyrics_out)

