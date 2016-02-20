#pragma once

#include "resource.h"
#include<L-D-Math-Main.h>
#include<stdlib.h>
#include"Chess-Define.h"
#include<L-D-2-1.h>
#include<L-D-2-2.h>
using namespace L_D_2;
using namespace L_D_2_1;
const float4 BoxColor = float4::_float4(1.0f, 0.0f, 0.0f, 0.0f);
const float4 BoxFillColor = float4::_float4(182.0f, 192.0f, 165.0f, 0.4f);
int Width = 773;
int Height = 845;
BOOL MainView=Red;
Origin* ChessRender;
ORIGIN_BITMAP RedChessPieces[7];
ORIGIN_BITMAP BlackChessPieces[7];
ORIGIN_BITMAP ChessBoard;
ORIGIN_SOLID_BRUSH BoxBrush;
ORIGIN_SOLID_BRUSH BoxFillBrush;
float2 CHESS_POS[10][11];
Chess_State Map[10][11];
GAME_STATE State;
Position LastMousePos;
void LoadResource();
void LoadMsg();
void Init(Origin* &LD, HWND Hwnd, int Width, int Height);
void ReleaseAll();
void RenderChessBoard();
void RenderChessPices(CHESS_KIND Kind, BOOL Color, float Angle, Position Pos);
void RenderBox(int x, int y);
void SetMap(int x, int y, CHESS_KIND Kind, BOOL Color);
void CleanMap(int x, int y);
Chess_State GetMapState(int x, int y);
//Init And Load
void LoadResource() {
	//Load ChessBoard
	ChessBoard._Name = L"ChessBoard.jpg";
	//Load RedChessPices
	RedChessPieces[0]._Name = L"RedKing.png";
	RedChessPieces[1]._Name = L"RedRook.png";
	RedChessPieces[2]._Name = L"RedBishop.png";
	RedChessPieces[3]._Name = L"RedKnight.png";
	RedChessPieces[4]._Name = L"RedGuard.png";
	RedChessPieces[5]._Name = L"RedCannon.png";
	RedChessPieces[6]._Name = L"RedPawn.png";
	
	//Load BlackChessPices
	BlackChessPieces[0]._Name = L"BlackKing.png";
	BlackChessPieces[1]._Name = L"BlackRook.png";
	BlackChessPieces[2]._Name = L"BlackBishop.png";
	BlackChessPieces[3]._Name = L"BlackKnight.png";
	BlackChessPieces[4]._Name = L"BlackGuard.png";
	BlackChessPieces[5]._Name = L"BlackCannon.png";
	BlackChessPieces[6]._Name = L"BlackPawn.png";
	//
	BoxBrush._Color = BoxColor;
	BoxFillBrush._Color = BoxFillColor;
	//
	ChessRender->LoadBitMap(&ChessBoard);
	for (int i = 0; i <= ChessPicesNum - 1; i++) {
		ChessRender->LoadBitMap(&RedChessPieces[i]);
		ChessRender->LoadBitMap(&BlackChessPieces[i]);
	}
	ChessRender->CreateSolidBrush(&BoxBrush);
	ChessRender->CreateSolidBrush(&BoxFillBrush);
}
void LoadMsg() {

	SetMap(1, 1, CHESS_ROOK, Black);
	SetMap(2, 1, CHESS_KNIGHT, Black);
	SetMap(3, 1, CHESS_BISHOP, Black);
	SetMap(4, 1, CHESS_GUARD, Black);
	SetMap(5, 1, CHESS_KING, Black);
	SetMap(6, 1, CHESS_GUARD, Black);
	SetMap(7, 1, CHESS_BISHOP, Black);
	SetMap(8, 1, CHESS_KNIGHT, Black);
	SetMap(9, 1, CHESS_ROOK, Black);
	SetMap(2, 3, CHESS_CANNON, Black);
	SetMap(8, 3, CHESS_CANNON, Black);
	SetMap(1, 4, CHESS_PAWN, Black);
	SetMap(3, 4, CHESS_PAWN, Black);
	SetMap(5, 4, CHESS_PAWN, Black);
	SetMap(7, 4, CHESS_PAWN, Black);
	SetMap(9, 4, CHESS_PAWN, Black);
	//
	SetMap(1, 10, CHESS_ROOK, Red);
	SetMap(2, 10, CHESS_KNIGHT, Red);
	SetMap(3, 10, CHESS_BISHOP, Red);
	SetMap(4, 10, CHESS_GUARD, Red);
	SetMap(5, 10, CHESS_KING, Red);
	SetMap(6, 10, CHESS_GUARD, Red);
	SetMap(7, 10, CHESS_BISHOP, Red);
	SetMap(8, 10, CHESS_KNIGHT, Red);
	SetMap(9, 10, CHESS_ROOK, Red);
	SetMap(2, 8, CHESS_CANNON, Red);
	SetMap(8, 8, CHESS_CANNON, Red);
	SetMap(1, 7, CHESS_PAWN, Red);
	SetMap(3, 7, CHESS_PAWN, Red);
	SetMap(5, 7, CHESS_PAWN, Red);
	SetMap(7, 7, CHESS_PAWN, Red);
	SetMap(9, 7, CHESS_PAWN, Red);
	//
	if (MainView == Red)
		State = GAME_STATE_RED_BEGIN;
	else
		State = GAME_STATE_BLACK_BEGIN;
}
void Init(Origin* &LD,HWND Hwnd,int Width,int Height) {
	ORIGIN_MSG Msg;
	Msg._FullScreen = FALSE;
	Msg._Hwnd = Hwnd;
	Msg._Mode = ORIGIN_MODE_2D;
	Msg._Width = Width;
	Msg._Height = Height;
	Origin::CreateOrigin(LD, Msg);
	LoadResource();
	LoadMsg();
}
//Release 
void ReleaseAll() {
	SafeRelease(ChessRender);
	SafeRelease(&ChessBoard);
	for (int i = 0; i <= ChessPicesNum - 1; i++) {
		SafeRelease(&RedChessPieces[i]);
		SafeRelease(&BlackChessPieces[i]);
	}
	SafeRelease(&BoxBrush);
	SafeRelease(&BoxFillBrush);
}
//Render
void RenderChessBoard() {
	ChessRender->DrawBitMap(ChessBoard, Rect::_Rect(0.0f, (float)Width, 0.0f, (float)Height));
	float RedAngle;
	float BlackAngle;
	if (MainView == Red) {
		RedAngle = 0.0f;
		BlackAngle = 180.0f;
	}
	else {
		RedAngle = 180.0f;
		BlackAngle = 0.0f;
	}
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 10; j++) {
			if (Map[i][j].Chess == TRUE)
			if (Map[i][j].Color == Red) {
				RenderChessPices(Map[i][j].Kind, Red, RedAngle, Position::POS(i, j));
			}
			else {
				RenderChessPices(Map[i][j].Kind, Black, BlackAngle, Position::POS(i, j));
			}
			if (Map[i][j].MouseIn == TRUE || Map[i][j].MouseDown==TRUE)
				RenderBox(i, j);
		}
}
void RenderChessPices(CHESS_KIND Kind, BOOL Color, float Angle, Position Pos) {
	if (Color == Red) {
		MATRIX3x2 Matrix;
		float Left, Top;
		Left = CHESS_POS[Pos.x][Pos.y]._f1 - ChessSizeWidth / 2.0f;	
		Top = CHESS_POS[Pos.x][Pos.y]._f2 - ChessSizeHeight / 2.0f;
		Matrix.SetRotation(Angle, float2::_float2(ChessSizeWidth / 2.0f, ChessSizeHeight / 2.0f));
		Matrix.SetTranslation(float2::_float2(Left, Top));
		ChessRender->SetTransForm(Matrix);
		ChessRender->DrawBitMap(RedChessPieces[(int)Kind]);
		ChessRender->EndTransForm();
	}
	else {
		MATRIX3x2 Matrix;
		float Left, Top;
		Left = CHESS_POS[Pos.x][Pos.y]._f1 - ChessSizeWidth / 2.0f;
		Top = CHESS_POS[Pos.x][Pos.y]._f2 - ChessSizeHeight / 2.0f;
		Matrix.SetRotation(Angle, float2::_float2(ChessSizeWidth / 2.0f, ChessSizeHeight / 2.0f));
		Matrix.SetTranslation(float2::_float2(Left, Top));
		ChessRender->SetTransForm(Matrix);
		ChessRender->DrawBitMap(BlackChessPieces[(int)Kind]);
		ChessRender->EndTransForm();
	}
}
void RenderBox(int x, int y) {
	ORIGIN_RECTANGLE RectAngle;
	MATRIX3x2 Matrix;
	RectAngle._Rect = Rect::_Rect(0.0f, 75.0f, 0.0f, 75.0f);
	RectAngle._Filled = TRUE;
	RectAngle._StrokeWidth = 1.0f;
	RectAngle._Brush = BoxBrush._Brush;
	if (y <= 5) {
		Matrix.SetTranslation(float2::_float2(CHESS_POS[x][y]._f1 - ChessSizeWidthHalf + 17.0f,
			CHESS_POS[x][y]._f2 - ChessSizeHeightHalf + 20.0f));
	}
	else {
		Matrix.SetTranslation(float2::_float2(CHESS_POS[x][y]._f1 - ChessSizeWidthHalf + 15.0f,
			CHESS_POS[x][y]._f2 - ChessSizeHeightHalf + 6.0f));
	}
	ChessRender->SetTransForm(Matrix);
	ChessRender->DrawRectAngle(RectAngle,BoxFillBrush._Brush);
	ChessRender->EndTransForm();
}
//
void GetNextState() {
	if (State == GAME_STATE_RED_BEGIN) {
		State = GAME_STATE_RED_GET;
		return;
	}
	if (State == GAME_STATE_RED_GET) {
		State = GAME_STATE_BLACK_BEGIN; 
		return;
	}
	if (State == GAME_STATE_BLACK_BEGIN) {
		State = GAME_STATE_BLACK_GET;
		return;
	}
	if (State == GAME_STATE_BLACK_GET) {
		State = GAME_STATE_RED_BEGIN;
		return;
	}
}
void GetLastState() {
	if (State == GAME_STATE_RED_BEGIN) {
		State = GAME_STATE_BLACK_GET;
		return;
	}
	if (State == GAME_STATE_RED_GET) {
		State = GAME_STATE_RED_BEGIN;
		return;
	}
	if (State == GAME_STATE_BLACK_BEGIN) {
		State = GAME_STATE_RED_GET;
		return;
	}
	if (State == GAME_STATE_BLACK_GET) {
		State = GAME_STATE_BLACK_BEGIN;
		return;
	}
}
//Deal Mouse Event
void DealMouseMove(int PosX,int PosY){
	BOOL First = TRUE;
	if (PosX < CHESS_POS[1][1]._f1 - BoxSizeWidthHalf) {
		return;
	}
	if (PosY < CHESS_POS[1][1]._f2 - BoxSizeHeightHalf) {
		return;
	}
	if (PosX > CHESS_POS[9][10]._f1 + BoxSizeWidthHalf) {
		return;
	}
	if (PosY > CHESS_POS[9][10]._f2 + BoxSizeHeightHalf) {
		return;
	}
	//.....
}
void DealMouseDown(int PosX, int PosY) {
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 10; j++) {
			if (Map[i][j].MouseIn==TRUE) {
				if (MainView == Red){
					if (State == GAME_STATE_RED_BEGIN) {
						if (Map[i][j].Chess == TRUE && Map[i][j].Color == Red) {
							GetNextState();
							Map[i][j].MouseDown = TRUE;
							LastMousePos.x = i;
							LastMousePos.y = j;
						}
					}
					if (State == GAME_STATE_RED_GET) {
						if (Map[i][j].Chess == TRUE && Map[i][j].Color == Red) {
							if (Map[i][j].MouseDown == TRUE) {
							}
							else {
								Map[LastMousePos.x][LastMousePos.y].MouseDown = FALSE;
								Map[i][j].MouseDown = TRUE;
								LastMousePos.x = i;
								LastMousePos.y = j;
							}
						}
						//Eat Other ChessPices
						//Go Other Pos
					}
				}
				if (MainView == Black) {
					if (State == GAME_STATE_BLACK_BEGIN) {
						if (Map[i][j].Chess == TRUE && Map[i][j].Color == Black) {
							GetNextState();
							Map[i][j].MouseDown = TRUE;
							LastMousePos.x = i;
							LastMousePos.y = j;
						}
					}
					if (State == GAME_STATE_BLACK_GET) {
						if (Map[i][j].Chess == TRUE && Map[i][j].Color == Black) {
							if (Map[i][j].MouseDown == TRUE) {
							}
							else {
								Map[LastMousePos.x][LastMousePos.y].MouseDown = FALSE;
								Map[i][j].MouseDown = TRUE;
								LastMousePos.x = i;
								LastMousePos.y = j;
							}
						}
						//Eat Other ChessPices
						//Go Other Pos
					}
				}
				break;
			}
		}
}

//233
void SetMap(int x, int y, CHESS_KIND Kind, BOOL Color) {
	Map[x][y].Chess = TRUE;
	Map[x][y].Kind = Kind;
	Map[x][y].Color = Color;
}
void CleanMap(int x, int y) {
	Map[x][y].Chess = FALSE;
}
Chess_State GetMapState(int x, int y) {
	return Map[x][y];
}
