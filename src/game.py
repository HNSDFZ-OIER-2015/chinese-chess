#
# Copyright 2016 HNSDFZ-OIER
#

import core
import graphics
import resource

try:
    from sfml.window import *
    from sfml.graphics import *
except ImportError:
    from sfml import *

class Game(object):
    """Respect a game instance"""
    def __init__(self):
        super(Game, self).__init__()

        self.window = graphics.GameWindow(
            width=resource.config["window_width"],
            height=resource.config["window_height"]
        )
        self.window.add_handler(CloseEvent, Game.on_close)
        self.window.add_handler(
            MouseMoveEvent, Game.on_mouse_move, args=(self, )
        )

        self.background = Sprite(resource.get("chessboard"))
        self.board_layout = resource.BoardLayout(resource.config["board_layout"])
        self.board = core.Board(
            resource.config["chess_layout"],
            current=core.CHESS_RED,
            searcher=NonePositionSearcher()
        )

        self.scan_board()

        self.current_block = graphics.BlockEnitiy(
            self.window, Sprite(resource.get("normal_select"))
        )
        self.current_block.x = -1000
        self.current_block.y = -1000
    
    def replace_current_block(self, x, y):
        indexes = self.board_layout.get_index(
            x, y,
            resource.config["chess_width"],
            resource.config["chess_height"]
        )

        if not indexes is None:
            i, j = indexes
            position = self.board_layout.get_position(i, j)
            self.current_block.x, self.current_block.y = position

    def scan_board(self):
        self.chesses = []

        for i in range(1, 11):
            for j in range(1, 10):
                chess = self.board.get_chess(i, j)

                if chess != core.CHESS_NONE:
                    name = core.to_chess_name(chess)

                    self.chesses.append(
                        graphics.BlockEnitiy(
                            self.window, Sprite(resource.get(name))
                        )
                    )

                    x, y = self.board_layout.get_position(
                        i, j
                    )
                    self.chesses[-1].x = x
                    self.chesses[-1].y = y


    ##################
    # Event handling #
    ##################

    def on_close(sender, event):
        sender.close()

    def on_mouse_move(sender, event, self):
        self.replace_current_block(
            event.position.x, event.position.y
        )

    ##################
    # Updating       #
    ##################

    def update(self):
        pass

    ##################
    # Rendering      #
    ##################

    def render(self):
        self.window.clear()
        self.window.draw(self.background)

        for chess in self.chesses:
            chess.render()

        self.current_block.render()
        self.window.present()

    def run(self):
        while self.window.is_open():
            self.window.do_events()
            self.update()
            self.render()
