
class Node:
    def __init__(self):
        self._children = []

    def initialize(self):
        pass
    def finalize(self):
        pass
    def draw(self):
        pass

    def __call__(self):
        self.draw()
        for i in self._children:
            i.draw()
        self.finalize()

    def add_children(self, node):
        self._children.append()


class Tree(Node):
    def __init__(self):
        Node.__init__(self)
        _star.enqueue_init(self.initialize)
        _star.set_drawer(self)

class Plane(Node):
    def __init__(self, pos):
        self._pos = pos
        self._neg_pos = tuple([-i for i in pos])

    def initialize(self):
        glTranslate3f(*pos)

    def finalize(self):
        glTranslate3f(*(-i for i in pos))

