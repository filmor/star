STD_POINTS = 14
STD_SPECIAL_POINTS = 100

EPS = 0.05

class Game:
    def __init__ (self, player, song, notes_plane):
        self.__multiplicator = 1
        self.__start = -1
        self.__points = 0
        self.__output = notes_plane
        self.__player = player
        self.__song = song
        player.notes_callback = self.__callback

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
        self.__player.start(self.__song)


if __name__ == '__main__':
    song = Song('sample_song')

    player = Player()

    Display = compose ({ ((-1.0, -0.8, 0.0), (1.0, 0.8, 0.0)) : NotesPlane(song)
                       , ((-1.0, 0.8, 0.0),  (1.0, 1.0, 0.0)) : LyricsPlane(song)
                       })

    p = Game(player, song, Display[0])

    p.start()
