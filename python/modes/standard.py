STD_POINTS = 14
STD_SPECIAL_POINTS = 100

EPS = 0.05

class Player:
    def __init__ (self, song, notes_plane):
        self.__multiplicator = 1
        self.__start = -1
        self.__points = 0
        self.__output = notes_plane
        self.__song = song
        song.notes_callback = self.__callback

    def __callback(note, sung_note, syllable):
        # Ignoriert die Oktave
        if abs (note.value - sung_note.value) <= EPS:
            self.__output.emphasize(self.pos)
            self.__points += self.__multiplicator * STD_POINTS
            
            if syllable.pos < self.__start:
                self.__start = syllable.pos
            if self.__start == 0 and syllable.pos == syllable.end:
                self.__output.blink(self.pos)
                self.__multiplicator += 0.1
                s = -1
        else:
            self.__output.failure (syllable.pos, sung_note.value - note.value)
            self.__multiplicator = 1

    def start():
        self.__song.start()


if __name__ == '__main__':
    info = SongInfo('sample_song')

    song = Song()

    Display = compose ({ ((-1.0, -0.8, 0.0), (1.0, 0.8, 0.0)) : NotesPlane(song)
                       , ((-1.0, 0.8, 0.0),  (1.0, 1.0, 0.0)) : LyricsPlane(song)
                       })

    p = Player(song, Display[0])

    p.start(info)
