STD_POINTS = 14
STD_SPECIAL_POINTS = 100

EPS = 0.05

class Game:
    def __init__ (self, player, notes_plane):
        self._multiplicator = 1
        self._start = -1
        self._points = 0
        self._output = notes_plane
        self._player = player
        player.notes_callback = self._callback

    def _callback(note, sung_note, syllable):
        # Ignoriert die Oktave
        if abs (note.value - sung_note.value) <= EPS:
            self._output.emphasize(self.pos)
            self._points += self._multiplicator * STD_POINTS
            
            if syllable.pos < self.__start:
                self._start = syllable.pos
            if self._start == 0 and syllable.pos == syllable.end:
                self._output.blink(self.pos)
                self._multiplicator += 0.1
                s = -1
        else:
            self._output.failure (syllable.pos, sung_note.value - note.value)
            self._multiplicator = 1

    def start():
        self._player.start()


if __name__ == '__main__':
    from Star import Song, Player, LyricsPlane, NotesPlane
    from Star.Graphics import Scene, compose

    song = Song('sample_song')

    player = Player(song)

    lyrics = LyricsPlane(song)
    notes = NotesPlane(song)

    # \todo Register notes and lyrics to the players event queue

    p = Game(player, notes)

    scene = Scene(compose ({ ((-1.0, -0.8, 0.0), (1.0, 0.8, 0.0)) : song
                           , ((-1.0, 0.8, 0.0),  (1.0, 1.0, 0.0)) : lyrics
                           }))

    p.start()
