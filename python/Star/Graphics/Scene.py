from GL import glGetError

# \todo Redo!

# \todo getattribute
class SceneNode(_star.scene):
    def __init__(self, *children):
        self._children = []
        for i in children:
            self.add_children(i)
        try:
            _star.enqueue_init(self.initialize)
        except AttributeError:
            pass

    def __del__(self):
        try:
            _star.enqueue_init(self.uninitialize)
        except AttributeError:
            pass

    def draw(self):
        for i in self._children:
            i.draw()
        error = glGetError()
        if error != 0:
            print error

    def add_children(self, node):
        self._children.append(node)

class Scene(SceneNode):
    def __init__(self, *children):
        super(Scene, self).__init__(*children)

    def __call__(self):
        _star.set_drawer(self.draw)

