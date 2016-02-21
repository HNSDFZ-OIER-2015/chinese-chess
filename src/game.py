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
        self.window.add_handler(
            MouseButtonEvent, Game.on_mouse_click, args=(self, )
        )

        self.setup_board()
        self.setup_status()
    
    ##################
    # Utility        #
    ##################

    def setup_board(self):
        self.background = Sprite(resource.get("chessboard"))
        self.board_layout = resource.BoardLayout(resource.config["board_layout"])
        self.board = core.Board(
            resource.config["chess_layout"],
            current=core.CHESS_RED,
            searcher=core.NonePositionSearcher()
        )

        self.scan_board()
        self.candidates = []
        self.placable = []

    def setup_status(self):
        self.current_block = graphics.BlockEnitiy(
            self.window, Sprite(resource.get("current_select"))
        )
        self.current_block.x = -1000
        self.current_block.y = -1000

        self.selected_x = 0
        self.selected_y = 0

    def update_current_block(self, x, y):
        indexes = self.board_layout.get_index(
            x, y,
            resource.config["chess_width"],
            resource.config["chess_height"]
        )

        if not indexes is None:
            i, j = indexes
            position = self.board_layout.get_position(i, j)
            self.current_block.x, self.current_block.y = position

    def update_candidates_graphics(self):
        for position in self.placable:
            x, y = position

            if self.board.get_chess(x, y) == core.CHESS_NONE:
                self.candidates.append(
                    graphics.BlockEnitiy(
                        self.window, Sprite(resource.get("move_select"))
                    )
                )
            else:
                self.candidates.append(
                    graphics.BlockEnitiy(
                        self.window, Sprite(resource.get("attack_select"))
                    )
                )

            cx, cy = self.board_layout.get_position(x, y)
            self.candidates[-1].x = cx
            self.candidates[-1].y = cy

    def clear_candidates(self):
        self.candidates = []
        self.placable = []
        self.update_candidates_graphics()

    def update_candidates(self, i, j):
        self.candidates = []
        self.placable = self.board.compute_placable(i, j)
        self.update_candidates_graphics()

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
        self.update_current_block(
            event.position.x, event.position.y
        )

    def on_mouse_click(sender, event, self):
        if event.released:
            if event.button == Mouse.RIGHT or event.button == Mouse.MIDDLE:
                self.clear_candidates()
                return

            x, y = event.position

            indexes = self.board_layout.get_index(
                x, y,
                resource.config["chess_width"],
                resource.config["chess_height"]
            )

            if indexes is None:
                self.selected = False
                self.clear_candidates()
                return

            i, j = indexes
            chess = self.board.get_chess(i, j)

            if not (i, j) in self.placable:
                self.selected_x = i
                self.selected_y = j
                self.update_candidates(i, j)
            else:
                self.board.move_chess(
                    self.selected_x, self.selected_y,
                    i, j
                )
                self.clear_candidates()
                self.scan_board()

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

        for candidate in self.candidates:
            candidate.render()

        self.current_block.render()
        self.window.present()

    def run(self):
        while self.window.is_open():
            self.window.do_events()
            self.update()
            self.render()
