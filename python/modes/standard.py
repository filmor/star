STD_POINTS = 14
STD_SPECIAL_POINTS = 100

EPS = 0.05

class Player:
    def __init__ (self, notes_plane):
        self.__multiplicator = 1
        self.__start = -1
        self.__points = 0
        self.__output = notes_plane

    def callback(note, sung_note, syllable):
        """
            note und sung_note haben den Typ star::note, syllable in etwa folgenden
            class Syllable:
                def __init__ (self):
                    self.pos = ... # Aktuelle Position innerhalb der Silbe
                    self.end = ... # Länge der Silbe, abhängig von der Auflösung
                                   # der Aufnahme (z.B. 100 ms: 4 s => 40)
                    self.ref = ... # Verweis auf die entsprechende Silbe in der 
                                   # NotesPlane
        """
        # Ignoriert die Oktave
        if abs (note.value - sung_note.value) <= EPS:
            self.__output.emphasize(syllable)
            self.__points += self.__multiplicator * STD_POINTS
            
            if note.pos < self.__start:
                self.__start = syllable.pos
            if self.__start == 0 and syllable.pos == syllable.end:
                self.__output.blink(syllable)
                self.__multiplicator += 0.1
                s = -1
        else:
            o.failure (syllable, sung_note)
            self.__multiplicator = 1

if __name__ == '__main__':
    song = Song ('sample_song')

    Display = compose ({ ((-1.0, -0.8, 0.0), (1.0, 0.8, 0.0)) : NotesPlane(song)
                       , ((-1.0, 0.8, 0.0),  (1.0, 1.0, 0.0)) : LyricsPlane(song)
                       })

    p = Player(Display[0])

    song.start(note_callback = p.callback)

