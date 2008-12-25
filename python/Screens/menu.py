
from Star import Screen, Widgets
from Star.Screen import Screen
from Star.I18n import _
from Star.Keys import KEY_DOWN, KEY_UP, KEY_ENTER, KEY_ESC

class Menu(Screen):
    def __init__(self, name, entries):
        self._title = name
        self._entries = [ (_(name), action) for name, action in entries ]
        self._marker = 0

        self.widgets = [ MenuItem(i) for i, j in self._entries ]

    def keyboard_callback(self, key, state):
        if state != STATE_PRESS:
            return
        if key == KEY_UP:
            if self._marker == 0:
                self._marker = len(self._entries)
            self._marker -= 1

        elif key == KEY_DOWN:
            self._marker += 1
            if self._marker == len(self._entries):
                self._marker = 0

        elif key == KEY_ENTER:
            entry = self._entries[self._marker]
            if hasattr(entry, "set_parent"):
                entry.set_parent(self)
            entry()

        elif key == KEY_ESC:
            if self._parent:
                self._parent()

