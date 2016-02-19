#pragma once
#define ChessPicesNum 7
const int Red = 1;
const int Black = 0;
const float ChessSizeWidth = 107;
const float ChessSizeHeight = 102;
typedef enum {
	CHESS_KING = 0, //帅
	CHESS_ROOK = 1, //车
	CHESS_BISHOP = 2, //象
	CHESS_KNIGHT = 3, //马
	CHESS_GUARD = 4, //士
	CHESS_CANNON = 5, //炮
	CHESS_PAWN = 6 //兵
}CHESS_KIND;
struct Position {
	int x, y;
	static Position POS(int x, int y) {
		Position Pos;
		Pos.x = x;
		Pos.y = y;
		return Pos;
	}
};
struct Chess_State {
	BOOL Chess;
	BOOL Color;
	CHESS_KIND Kind;
};
