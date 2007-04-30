import sys

import Menu

Menu(
        [
          "play"
        , "settings"
        , ("Quit", lambda : sys.exit (0))
        ]
    ).show ()

