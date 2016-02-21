#pragma once
#define ChessPicesNum 7
const int Red = 1;
const int Black = 0;
const int Empty = 2;
const int Alone = 1;
const int Together = 0;
const float ChessSizeWidth = 76.0f;
const float ChessSizeHeight = 76.0f;
const float ChessSizeWidthHalf = 38.0f;
const float ChessSizeHeightHalf = 38.0f;
const float BoxSizeWitdh = 76.0f;
const float BoxSizeHeight = 76.0f;
const float BoxSizeWidthHalf = 38.0f;
const float BoxSizeHeightHalf = 38.0f;
typedef enum {
	CHESS_KING = 0, //帅
	CHESS_ROOK = 1, //车
	CHESS_BISHOP = 2, //象
	CHESS_KNIGHT = 3, //马
	CHESS_GUARD = 4, //士
	CHESS_CANNON = 5, //炮
	CHESS_PAWN = 6 //兵
}CHESS_KIND;
typedef enum {
	GAME_STATE_RED_BEGIN = 0,
	GAME_STATE_RED_GET = 1,
	GAME_STATE_BLACK_BEGIN = 2,
	GAME_STATE_BLACK_GET
}GAME_STATE;
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
	BOOL MouseIn;
	BOOL MouseDown;
	CHESS_KIND Kind;
};
