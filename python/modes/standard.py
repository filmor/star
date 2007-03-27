import Display

song = SongSelector().select()

STD_POINTS = 14
STD_SPECIAL_POINTS = 100


multiplicator = 1

start = 0


def whole_note(note):
    note.blink()
    multiplicator += 1
    points += multiplicator * STD_SPECIAL_POINTS

def on_hit_note(note, special):
    note.emphasize()
    if start == 0:
        start = note.pos()
        points += STD_POINTS * multiplicator
    else:
        if note.end() and start == 0:
            whole_note(note)

def on_fail_note(note, failure):
    multiplicator = 1
    start = 0

song.hit += on_hit_note
song.fail += on_fail_note

song.start()
