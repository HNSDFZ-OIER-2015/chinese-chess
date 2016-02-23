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
    
    def is_out_of_range(self, x, y):
        return x < 1 or x > 10 or y < 1 or y > 9

    def search_king(self, board, x, y):
        result = set()
        color = get_chess_color(board.get_chess(x, y))

        up_points = [(1, 4), (1, 5), (1, 6), (2, 4), (2, 5), (2, 6), (3, 4), (3, 5), (3, 6)]
        down_points = [(8, 4), (8, 5), (8, 6), (9, 4), (9, 5), (9, 6), (10, 4), (10, 5), (10, 6)]
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        points = None
        if board.layout_name == CHESS_RED:
            if color == CHESS_RED:
                points = down_points
            else:
                points = up_points
        else:
            if color == CHESS_RED:
                points = up_points
            else:
                points = down_points

        for direction in directions:
            dx, dy = direction
            p = (x + dx, y + dy)

            if p in points:
                result.add(p)

        return result

    def search_guard(self, board, x, y):
        result = set()
        color = get_chess_color(board.get_chess(x, y))

        up_points = [(1, 4), (1, 6), (2, 5), (3, 4), (3, 6)]
        down_points = [(10, 4), (10, 6), (9, 5), (8, 4), (8, 6)]
        directions = [(-1, -1), (1, -1), (-1, 1), (1, 1)]
        points = None
        if board.layout_name == CHESS_RED:
            if color == CHESS_RED:
                points = down_points
            else:
                points = up_points
        else:
            if color == CHESS_RED:
                points = up_points
            else:
                points = down_points

        for direction in directions:
            dx, dy = direction
            p = (x + dx, y + dy)

            if p in points:
                result.add(p)

        return result

    def search_bishop(self, board, x, y):
        result = set()
        color = get_chess_color(board.get_chess(x, y))

        up_points = [(1, 3), (1, 7), (3, 1), (3, 5), (3, 9), (5, 3), (5, 7)]
        down_points = [(6, 3), (6, 7), (8, 1), (8, 5), (8, 9), (10, 3), (10, 7)]
        directions = [(-2, -2, -1, -1), (2, -2, 1, -1), (-2, 2, -1, 1), (2, 2, 1, 1)]
        points = None
        if board.layout_name == CHESS_RED:
            if color == CHESS_RED:
                points = down_points
            else:
                points = up_points
        else:
            if color == CHESS_RED:
                points = up_points
            else:
                points = down_points

        for direction in directions:
            dx, dy, ix, iy = direction
            cx, cy = x + ix, y + iy

            if not self.is_out_of_range(cx, cy) and board.get_chess(cx, cy) != CHESS_NONE:
                continue

            p = (x + dx, y + dy)
            if p in points:
                result.add(p)

        return result

    def search_knight(self, board, x, y):
        result = set()
        color = get_chess_color(board.get_chess(x, y))

        directions = [
            (-1, -2, 0, -1), (1, -2, 0, -1),
            (-2, -1, -1, 0), (-2, 1, -1, 0),
            (-1, 2, 0, 1), (1, 2, 0, 1),
            (2, -1, 1, 0), (2, 1, 1, 0)
        ]

        for direction in directions:
            dx, dy, ix, iy = direction
            cx, cy = x + ix, y + iy

            if not self.is_out_of_range(cx, cy) and board.get_chess(cx, cy) != CHESS_NONE:
                continue

            tx, ty = x + dx, y + dy
            if not self.is_out_of_range(tx, ty):
                result.add((tx, ty))

        return result

    def search_rook(self, board, x, y):
        result = set()
        color = get_chess_color(board.get_chess(x, y))

        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        for direction in directions:
            dx, dy = direction

            cx, cy = x + dx, y + dy
            while not self.is_out_of_range(cx, cy) and board.get_chess(cx, cy) == CHESS_NONE:
                result.add((cx, cy))
                cx += dx
                cy += dy

            if not self.is_out_of_range(cx, cy):
                result.add((cx, cy))

        return result

    def search_cannon(self, board, x, y):
        result = set()
        color = get_chess_color(board.get_chess(x, y))

        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
        for direction in directions:
            dx, dy = direction

            cx, cy = x + dx, y + dy
            while not self.is_out_of_range(cx, cy) and board.get_chess(cx, cy) == CHESS_NONE:
                result.add((cx, cy))
                cx += dx
                cy += dy

            cx += dx
            cy += dy

            while not self.is_out_of_range(cx, cy) and board.get_chess(cx, cy) == CHESS_NONE:
                cx += dx
                cy += dy

            if not self.is_out_of_range(cx, cy):
                result.add((cx, cy))

        return result

    def search_pawn(self, board, x, y):
        result = set()
        color = get_chess_color(board.get_chess(x, y))

        up_predirections = [(1, 0)]
        up_directions = [(1, 0), (0, -1), (0, 1)]
        up_line = 5
        down_predirections = [(-1, 0)]
        down_directions = [(-1, 0), (0, -1), (0, 1)]
        down_line = 6

        directions = None
        if board.layout_name == CHESS_RED:
            if color == CHESS_RED:
                if x < down_line:
                    directions = down_directions
                else:
                    directions = down_predirections
            else:
                if x > up_line:
                    directions = up_directions
                else:
                    directions = up_predirections
        else:
            if color == CHESS_RED:
                if x > up_line:
                    directions = up_directions
                else:
                    directions = up_predirections
            else:
                if x < down_line:
                    directions = down_directions
                else:
                    directions = down_predirections

        for direction in directions:
            dx, dy = direction
            cx, cy = x + dx, y + dy

            if not self.is_out_of_range(cx, cy):
                result.add((cx, cy))

        return result

    def search(self, board, x, y):
        chess = board.get_chess(x, y)
        color = get_chess_color(chess)

        if color != board.current:
            return set()

        if color == CHESS_BLACK:
            chess -= 100

        temporary = self.searcher_map[chess](
            self, board, x, y
        )

        result = set()
        for p in temporary:
            i, j = p
            if get_chess_color(board.get_chess(i, j)) != color:
                result.add(p)

        return result

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

    def is_dangerous(self, x, y):
        chess = self.get_chess(x, y)
        color = get_chess_color(chess)

        enemy = CHESS_NONE
        if color == CHESS_RED:
            enemy = CHESS_BLACK
        else:
            enemy = CHESS_RED

        placable = set()

        self.current = enemy
        for i in range(1, 11):
            for j in range(1, 10):
                current = self.get_chess(i, j)
                current_color = get_chess_color(current)

                if current != CHESS_NONE and current_color != color:
                    placable = placable | self.compute_placable(i, j)
        self.current = color

        if chess == CHESS_RED_KING or chess == CHESS_BLACK_KING:
            target = CHESS_NONE
            dx = 0
            dy = 0

            if chess == CHESS_RED_KING:
                target = CHESS_BLACK_KING

                if self.layout_name == CHESS_RED:
                    dx = -1
                else:
                    dx = 1
            else:
                target = CHESS_RED_KING

                if self.layout_name == CHESS_RED:
                    dx = 1
                else:
                    dx = -1

            cx, cy = x + dx, y + dy
            while 1 <= cx and cx <= 10 and 1 <=  cy and cy <= 9 and self.get_chess(cx, cy) == CHESS_NONE:
                cx += dx
                cy += dy

            if 1 <= cx and cx <= 10 and 1 <=  cy and cy <= 9 and self.get_chess(cx, cy) == target:
                return True

        return (x, y) in placable
