#
# Copyright 2016 HNSDFZ-OIER
#

CHESS_NONE = 0

CHESS_RED = 100
CHESS_RED_KING = 101
CHESS_RED_GUARD = 102
CHESS_RED_BISHOP = 103
CHESS_RED_KNIGHT = 104
CHESS_RED_ROOK = 105
CHESS_RED_CANNON = 106
CHESS_RED_PAWN = 107

CHESS_BLACK = 200
CHESS_BLACK_KING = 201
CHESS_BLACK_GUARD = 202
CHESS_BLACK_BISHOP = 203
CHESS_BLACK_KNIGHT = 204
CHESS_BLACK_ROOK = 205
CHESS_BLACK_CANNON = 206
CHESS_BLACK_PAWN = 207

name_map = {
    "": CHESS_NONE,

    "red_king": CHESS_RED_KING,
    "red_guard": CHESS_RED_GUARD,
    "red_bishop": CHESS_RED_BISHOP,
    "red_knight": CHESS_RED_KNIGHT,
    "red_rook": CHESS_RED_ROOK,
    "red_cannon": CHESS_RED_CANNON,
    "red_pawn": CHESS_RED_PAWN,

    "black_king": CHESS_BLACK_KING,
    "black_guard": CHESS_BLACK_GUARD,
    "black_bishop": CHESS_BLACK_BISHOP,
    "black_knight": CHESS_BLACK_KNIGHT,
    "black_rook": CHESS_BLACK_ROOK,
    "black_cannon": CHESS_BLACK_CANNON,
    "black_pawn": CHESS_BLACK_PAWN
}

reverse_name_map = {
    CHESS_NONE: "",

    CHESS_RED_KING: "red_king",
    CHESS_RED_GUARD: "red_guard",
    CHESS_RED_BISHOP: "red_bishop",
    CHESS_RED_KNIGHT: "red_knight",
    CHESS_RED_ROOK: "red_rook",
    CHESS_RED_CANNON: "red_cannon",
    CHESS_RED_PAWN: "red_pawn",

    CHESS_BLACK_KING: "black_king",
    CHESS_BLACK_GUARD: "black_guard",
    CHESS_BLACK_BISHOP: "black_bishop",
    CHESS_BLACK_KNIGHT: "black_knight",
    CHESS_BLACK_ROOK: "black_rook",
    CHESS_BLACK_CANNON: "black_cannon",
    CHESS_BLACK_PAWN: "black_pawn"
}


def to_chess(name):
    name = name.strip().lower()
    
    return name_map[name]

def to_chess_name(chess):
    return reverse_name_map[chess]

def get_chess_color(chess):
    if chess == CHESS_NONE:
        return CHESS_NONE
    elif CHESS_RED <= chess and chess <= CHESS_RED_PAWN:
        return CHESS_RED
    elif CHESS_BLACK <= chess and chess <= CHESS_BLACK_PAWN:
        return CHESS_BLACK

class PositionSearcher(object):
    """A search engine for correct chess placing"""
    def __init__(self):
        super(PositionSearcher, self).__init__()
    
    def search(self, board, x, y):
        pass

class NonePositionSearcher(PositionSearcher):
    """Search for positions where no chess placed"""
    def __init__(self):
        super(NonePositionSearcher, self).__init__()

    def search(self, board, x, y):
        if board.get_chess(x, y) == CHESS_NONE:
            return set()

        result = set()

        enemy = None
        if get_chess_color(board.get_chess(x, y)) == CHESS_RED:
            enemy = CHESS_BLACK
        else:
            enemy = CHESS_RED

        for i in range(1, 11):
            for j in range(1, 10):
                chess = board.get_chess(i, j)

                if chess == CHESS_NONE or get_chess_color(chess) == enemy:
                    result.add((i, j))

        return result

class RealSearchEngine(PositionSearcher):
    """Real position search engine"""
    def __init__(self):
        super(RealSearchEngine, self).__init__()

        self.searcher_map = {
            CHESS_RED_KING: RealSearchEngine.search_king,
            CHESS_RED_GUARD: RealSearchEngine.search_guard,
            CHESS_RED_BISHOP: RealSearchEngine.search_bishop,
            CHESS_RED_KNIGHT: RealSearchEngine.search_knight,
            CHESS_RED_ROOK: RealSearchEngine.search_rook,
            CHESS_RED_CANNON: RealSearchEngine.search_cannon,
            CHESS_RED_PAWN: RealSearchEngine.search_pawn
        }
    
    def search_king(self, board, x, y):
        return set()

    def search_guard(self, board, x, y):
        return set()

    def search_bishop(self, board, x, y):
        return set()

    def search_knight(self, board, x, y):
        return set()

    def search_rook(self, board, x, y):
        return set()

    def search_cannon(self, board, x, y):
        return set()

    def search_pawn(self, board, x, y):
        return set()

    def search(self, board, x, y):
        chess = board.get_chess(x, y)
        color = get_chess_color(chess)

        if color != board.current:
            return set()

        if color == CHESS_BLACK:
            chess -= 100

        return self.searcher_map[chess](
            self, board, x, y
        )

class Board(object):
    """Respect a board to store game data"""
    def __init__(self, chess, layout_name=CHESS_RED, searcher=PositionSearcher()):
        super(Board, self).__init__()
        self.layout_name = layout_name
        self.current = CHESS_RED
        self.data = []
        self.searcher = searcher

        if layout_name == CHESS_RED:
            layout_name = "red"
        elif layout_name == CHESS_BLACK:
            layout_name = "black"
        else:
            raise ValueError("Invalid parameter: layout_name")

        layout = {}
        for key, value in chess[layout_name].items():
            i, j = map(int, key.split(","))
            value = to_chess(value)
            layout[(i, j)] = value

        for i in range(0, 10):
            self.data.append([])
            for j in range(0, 9):
                self.data[-1].append(layout[(i + 1, j + 1)])

    def set_chess(self, x, y, chess):
        self.data[x - 1][y - 1] = chess

    def get_chess(self, x, y):
        return self.data[x - 1][y - 1]

    def move_chess(self, from_x, from_y, to_x, to_y):
        self.set_chess(to_x, to_y, self.get_chess(from_x, from_y))
        self.set_chess(from_x, from_y, CHESS_NONE)

    def switch_current(self):
        if self.current == CHESS_RED:
            self.current = CHESS_BLACK
        else:
            self.current = CHESS_RED

    def compute_placable(self, x, y):
        return self.searcher.search(self, x, y)
