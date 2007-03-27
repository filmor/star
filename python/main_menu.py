import sys

Menu(
        {
          "Play" : file ("multi_player.menu.py")
        , "Settings" : file ("settings.menu.py")
        , "Quit" : lambda : sys.exit (0)
        }
    ).show ()
