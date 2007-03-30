import Display

song = Song("sample_song") # SongSelector().select()

STD_POINTS = 14
STD_SPECIAL_POINTS = 100

multiplicator = 1

start = -1

Display = compose ({ ((-1.0, -0.8, 0.0), (1.0, 0.8, 0.0)) : NotesPlane
                   , ((-1.0, 0.8, 0.0),  (1.0, 1.0, 0.0)) : LyricsPlane
                   })

def callback(note, sung_note, syllable):
# Ignoriert die Oktave
    if abs (note.value - sung_note.value) <= EPS:
        syllable.emphasize (note.pos)
        points += multiplicator * STD_POINTS
        if note.pos < start:
            start = note.pos
        if start == 0 and note.pos == syllable.end:
            syllable.blink ()
            multiplicator += 0.1
            start = -1
    else:
        syllable.failure (note.pos, note.value - sung_note.value)
        multiplicator = 1

song.start(note_callback = callback)
