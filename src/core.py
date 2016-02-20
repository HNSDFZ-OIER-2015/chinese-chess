#
# Copyright 2016 HNSDFZ-OIER
#

CHESS_NONE = 0

CHESS_RED = -1
CHESS_RED_KING = 1
CHESS_RED_GUARD = 2
CHESS_RED_BISHOP = 3
CHESS_RED_KNIGHT = 4
CHESS_RED_ROOK = 5
CHESS_RED_CANNON = 6
CHESS_RED_PAWN = 7

CHESS_BLACK = -2
CHESS_BLACK_KING = 8
CHESS_BLACK_GUARD = 9
CHESS_BLACK_BISHOP = 10
CHESS_BLACK_KNIGHT = 11
CHESS_BLACK_ROOK = 12
CHESS_BLACK_CANNON = 13
CHESS_BLACK_PAWN = 14

class PositionSearcher(object):
    """A search engine for correct chess placing"""
    def __init__(self):
        super(PositionSearcher, self).__init__()
    
    def search(self, board, x, y):
        pass

class Board(object):
    """Respect a board to store game data"""
    def __init__(self, current=CHESS_RED):
        super(Board, self).__init__()
        self.current = current
        self.data = []
        self.searcher = PositionSearcher()

        for i in range(0, 10):
            self.data.append([])
            for j in range(0, 9):
                self.data[-1].append(CHESS_NONE)

    def set_chess(self, x, y, chess):
        self.data[x - 1][y - 1] = chess

    def get_chess(self, x, y):
        return self.data[x - 1][y - 1]

    def move_chess(self, from_x, from_y, to_x, to_y):
        set_chess(to_x, to_y, get_chess(from_x, from_y))
        set_chess(from_x, from_y, CHESS_NONE)

    def compute_placable(self, x, y):
        return self.searcher.search(self, x, y)
