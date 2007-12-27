from I18n import _
import Keys
from Keys import KEY_DOWN, KEY_UP, KEY_ENTER, KEY_ESC

class Menu:
    def __init__(self, name, entries):
        self._title = name
        self._entries = [ (_(name), action) for name, action in entries ]
        self._marker = 0

        self._scene = MenuScene(name, [ i for i, j in self._entries ])

    def _keyboard_callback(self, key, state):
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
            self.unshow()
            entry = self._entries[self._marker]
            if hasattr(entry, "set_parent"):
                entry.set_parent(self)
            entry()

        else key == KEY_ESC:
            if self._parent:
                self.unshow()
                self._parent()

    def show(self):
        Keys.RegisterKeyCallback(self._keyboard_callback)
        self._scene()

    __call__ = show

    def unshow():
        Keys.ClearKeyCallback()


