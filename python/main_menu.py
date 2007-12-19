import sys

from Star import Menu

Menu(
        "Main Menu",
        [
          ("Play", PlayMenu)
        , ("Settings", SettingsMenu)
        , ("Quit", lambda : sys.exit (0))
        ]
    ).show ()

