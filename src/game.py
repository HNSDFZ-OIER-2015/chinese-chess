#
# Copyright 2016 HNSDFZ-OIER
#

import time
import socket
import threading

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
        self.window.add_handler(
            CloseEvent, Game.on_close, args=(self, )
        )
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
            layout_name=core.CHESS_RED,
            searcher=core.RealSearchEngine()
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

        self.selected_block1 = graphics.BlockEnitiy(
            self.window, Sprite(resource.get("selected"))
        )
        self.selected_block1.x = -1000
        self.selected_block1.y = -1000

        self.selected_block2 = graphics.BlockEnitiy(
            self.window, Sprite(resource.get("selected"))
        )
        self.selected_block2.x = -1000
        self.selected_block2.y = -1000

        self.selected_x = 0
        self.selected_y = 0

        self.disabled = False
        self.finished = False
        self.enable_networking = False

        self.last_data = None

    def update_current_block(self, x, y):
        indexes = self.board_layout.get_index(
            x, y,
            resource.config["chess_width"],
            resource.config["chess_height"]
        )

        if not indexes is None:
            self.current_block.visible = True
            i, j = indexes
            position = self.board_layout.get_position(i, j)
            self.current_block.x, self.current_block.y = position
        else:
            self.current_block.visible = False

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

    def find_board(self, chess):
        for i in range(1, 11):
            for j in range(1, 10):
                if self.board.get_chess(i, j) == chess:
                    return i, j

        return None

    def move(self, from_x, from_y, to_x, to_y):
        origin = self.board.get_chess(
            to_x, to_y
        )
        self.board.move_chess(
            from_x, from_y,
            to_x, to_y
        )

        kx, ky = 0, 0

        if self.board.current == core.CHESS_RED:
            kx, ky = self.find_board(core.CHESS_RED_KING)
        else:
            kx, ky = self.find_board(core.CHESS_BLACK_KING)

        if self.board.is_dangerous(kx, ky):
            if self.board.current == core.CHESS_RED:
                print("(warn) Red king is in danger")
            else:
                print("(warn) Black king is in danger")     

            # No hard changes
            # self.board.move_chess(
            #     to_x, to_y,
            #     from_x, from_y
            # )
            # self.board.set_chess(
            #     to_x, to_y, origin
            # )
            # self.clear_candidates()
            # self.scan_board()
            # return

        self.selected_block2.visible = True
        x, y = self.board_layout.get_position(to_x, to_y)
        self.selected_block2.x = x
        self.selected_block2.y = y
        x, y = self.board_layout.get_position(from_x, from_y)
        self.selected_block1.x = x
        self.selected_block1.y = y

        if self.enable_networking:
            self.last_data = (from_x, from_y, to_x, to_y)

        self.board.switch_current()
        self.clear_candidates()
        self.scan_board()

        if origin == core.CHESS_RED_KING or origin == core.CHESS_BLACK_KING:
            print("(info) Game finished")

            if origin == core.CHESS_RED_KING:
                self.image = Sprite(resource.get("black_win"))
                print("(info) Black is winner")
            else:
                self.image = Sprite(resource.get("red_win"))
                print("(info) Red is winner")

            self.image.position = (0, 0)

            self.disabled = True
            self.finished = True

    ##################
    # Networking     #
    ##################

    def reverse(self, x, y):
        return 11 - x, y

    def setup_server(self, address, port):
        self.enable_networking = True
        print("(info) Networking is enabled")

        # Setup
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.bind((address, port))
        self.socket.listen(1)

        # Setup thread
        self.address = address
        self.port = port
        self.server_thread = threading.Thread(
            target=Game.server, args=(self, )
        )
        self.server_thread.start()

    def setup_client(self, address, port):
        self.enable_networking = True
        print("(info) Networking is enabled")

        # Setup
        # Reset chess board layout
        self.board = core.Board(
            resource.config["chess_layout"],
            layout_name=core.CHESS_BLACK,
            searcher=core.RealSearchEngine()
        )
        self.scan_board()

        self.disabled = True
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Setup thread
        self.address = address
        self.port = port
        self.client_thread = threading.Thread(
            target=Game.client, args=(self, )
        )
        self.client_thread.start()

    def wait_for_data(self):
        print("(info) Waiting for user input")

        self.last_data = None
        self.disabled = False
        while not self.finished and self.last_data is None:
            time.sleep(0.01)

        self.disabled = True

        return self.last_data

    def server(self):
        # Wait for connection
        self.disabled = True
        self.connection, address = self.socket.accept()
        print("(info) New connection from %s:%s" % address)
        self.disabled = False

        try:
            while not self.finished:
                data = self.wait_for_data()
                self.connection.send(("%s %s %s %s" % data).encode("ascii"))
                print("(info) sent data: (%s, %s, %s, %s)" % data)

                if self.finished:
                    return

                print("(info) Waiting for remote data")
                buf = self.connection.recv(1024)
                fx, fy, tx, ty = map(int, buf.decode("ascii").split(" "))
                fx, fy = self.reverse(fx, fy)
                tx, ty = self.reverse(tx, ty)
                print("(info) received data: (%s, %s, %s, %s)" % (fx, fy, tx, ty))

                self.move(fx, fy, tx, ty)
        finally:
            self.connection.close()
            self.socket.close()

    def client(self):
        # Wait for connection
        self.disabled = True
        self.socket.connect((self.address, self.port))
        print("(info) Connected to the server")

        try:
            while not self.finished:
                print("(info) Waiting for remote data")
                buf = self.socket.recv(1024)
                fx, fy, tx, ty = map(int, buf.decode("ascii").split(" "))
                fx, fy = self.reverse(fx, fy)
                tx, ty = self.reverse(tx, ty)
                print("(info) received data: (%s, %s, %s, %s)" % (fx, fy, tx, ty))

                self.move(fx, fy, tx, ty)

                if self.finished:
                    return

                data = self.wait_for_data()
                self.socket.send(("%s %s %s %s" % data).encode("ascii"))
                print("(info) sent data: (%s, %s, %s, %s)" % data)
        finally:
            self.socket.close()

    ##################
    # Event handling #
    ##################

    def on_close(sender, event, self):
        self.finished = True
        sender.close()

    def on_mouse_move(sender, event, self):
        self.update_current_block(
            event.position.x, event.position.y
        )

    def on_mouse_click(sender, event, self):
        if self.disabled:
            return

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

                self.selected_block1.visible = True
                self.selected_block2.visible = False
                x, y = self.board_layout.get_position(i, j)
                self.selected_block1.x = x
                self.selected_block1.y = y

                self.update_candidates(i, j)
            else:
                self.move(
                    self.selected_x, self.selected_y,
                    i, j
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

        for candidate in self.candidates:
            candidate.render()

        self.current_block.render()
        self.selected_block1.render()
        self.selected_block2.render()

        if self.finished:
            self.window.draw(self.image)

        self.window.present()

    def run(self):
        while self.window.is_open():
            self.window.do_events()
            self.update()
            self.render()
