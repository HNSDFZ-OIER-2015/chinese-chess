#
# Copyright 2016 HNSDFZ-OIER
#

try:
    from sfml.system import *
    from sfml.window import *
    from sfml.graphics import *
except ImportError:
    from sfml import *

DEFAULT_WIDTH = 800
DEFAULT_HEIGHT = 600
DEFAULT_TITLE = "Chinese Chess"
DEFAULT_STYLE = Style.TITLEBAR | Style.CLOSE

class GameWindow(object):
    """Game window"""
    def __init__(self,
        width=DEFAULT_WIDTH,
        height=DEFAULT_HEIGHT,
        title=DEFAULT_TITLE,
        style=DEFAULT_STYLE
    ):
        super(GameWindow, self).__init__()
        self.width = width
        self.height = height
        self.title = title
        self.style = style

        self.window = RenderWindow(
            VideoMode(width, height), title, style
        )
        self.handlers = {}

    def add_handler(self, event, handler, args=()):
        if not event in self.handlers:
            self.handlers[event] = []

        self.handlers[event].append((handler, args))

    def close(self):
        self.window.close()

    def is_open(self):
        return self.window.is_open

    def clear(self, background_color=Color.BLACK):
        self.window.clear(background_color)

    def draw(self, target):
        self.window.draw(target)

    def present(self):
        self.window.display()

    def do_events(self):
        for event in self.window.events:
            if not type(event) in self.handlers:
                continue

            for callback in self.handlers[type(event)]:
                handler, args = callback
                handler(self, event, *args)


class Enitiy(object):
    """Respect an object to be rendered"""
    def __init__(self, window):
        super(Enitiy, self).__init__()
        self.window = window
        
    def render(self):
        pass


class BlockEnitiy(Enitiy):
    """Respect a chess"""
    def __init__(self, window, sprite):
        super(BlockEnitiy, self).__init__(window)
        self.window = window
        self.sprite = sprite
        self._half_width = sprite.texture_rectangle.width / 2
        self._half_height = sprite.texture_rectangle.height / 2
        self.sprite.position -= (self._half_width, self._half_height)
        self._visible = True
    
    @property
    def x(self):
        return self.sprite.position.x + self._half_width
    @x.setter
    def x(self, value):
        self.sprite.position = (
            value - self._half_width, self.sprite.position.y
        )

    @property
    def y(self):
        return self.sprite.position.y + self._half_height

    @y.setter
    def y(self, value):
        self.sprite.position = (
            self.sprite.position.x, value - self._half_height
        )

    @property
    def visible(self):
        return self._visible

    @visible.setter
    def visible(self, value):
        self._visible = value

    def render(self):
        if self.visible:
            self.window.draw(self.sprite)
