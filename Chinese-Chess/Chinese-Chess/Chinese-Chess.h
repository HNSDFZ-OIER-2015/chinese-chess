#pragma once

#include "resource.h"
#include<L-D-Math-Main.h>
#include<stdlib.h>
#include<iostream>
#include"Chess-Define.h"
#include<L-D-2-1.h>
#include<L-D-2-2.h>
using namespace std;
using namespace L_D_2;
using namespace L_D_2_1;
const float4 BoxColor = float4::_float4(1.0f, 0.0f, 0.0f, 0.0f);
const float4 BoxRedColor = float4::_float4(1.0f, 0.0f, 0.0f, 1.0f);
const float4 BoxGreenColor = float4::_float4(0.0f, 1.0f, 0.0f, 1.0f);
const float4 BoxFillColor = float4::_float4(182.0f, 192.0f, 165.0f, 0.4f);
int Width = 773;
int Height = 845;
BOOL MainView=Red;
BOOL Player = Red;
BOOL Mode = Alone;
Origin* ChessRender;
StrokeStyle ChessStyle;
ORIGIN_BITMAP RedChessPieces[7];
ORIGIN_BITMAP BlackChessPieces[7];
ORIGIN_BITMAP ChessBoard;
ORIGIN_SOLID_BRUSH BoxRedBrush;
ORIGIN_SOLID_BRUSH BoxGreenBrush;
ORIGIN_SOLID_BRUSH BoxBrush;
ORIGIN_SOLID_BRUSH BoxFillBrush;
float2 CHESS_POS[10][11];
Chess_State Map[10][11];
GAME_STATE State;
Position LastMousePos;
Position LastMouseDownPos;
vector<Position> LastRoad;
void LoadResource();
void LoadMsg();
void Init(Origin* &LD, HWND Hwnd, int Width, int Height);
void ReleaseAll();
void RenderChessBoard();
void RenderChessPices(CHESS_KIND Kind, BOOL Color, float Angle, Position Pos);
void RenderBox(int x, int y);
void GetNextState();
void GetLastState();
void MoveChessPices(int From_X,int From_Y,int To_X,int To_Y);
void DealMouseMove(int PosX, int PosY);
void DealMouseDown(int PosX, int PosY);
void GetChessPicesRoad(CHESS_KIND Kind, int PosX, int PosY, BOOL Color, vector<Position> &Road);
void RotationMainView();
void RotationMainViewAlone();
Position MousePosToChessPos(Position Pos);
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
	BoxRedBrush._Color = BoxRedColor;
	BoxGreenBrush._Color = BoxGreenColor;
	BoxFillBrush._Color = BoxFillColor;
	//
	ChessStyle._Start_Cap = ORIGIN_STROKE_CAP_STYLE_ROUND;
	ChessStyle._End_Cap = ORIGIN_STROKE_CAP_STYLE_ROUND;
	ChessStyle._Dash_Cap = ORIGIN_STROKE_CAP_STYLE_ROUND;
	ChessStyle._Dash_Style = ORIGIN_STROKE_DASH_STYLE_DASH;
	ChessStyle._Line_Join = ORIGIN_STROKE_LINE_JOIN_ROUND;
	//
	ChessRender->LoadBitMap(&ChessBoard);
	for (int i = 0; i <= ChessPicesNum - 1; i++) {
		ChessRender->LoadBitMap(&RedChessPieces[i]);
		ChessRender->LoadBitMap(&BlackChessPieces[i]);
	}
	ChessRender->CreateSolidBrush(&BoxBrush);
	ChessRender->CreateSolidBrush(&BoxRedBrush);
	ChessRender->CreateSolidBrush(&BoxGreenBrush);
	ChessRender->CreateSolidBrush(&BoxFillBrush);
	ChessRender->CreateStrokeStyle(&ChessStyle);
}
void LoadMsg() {
	for (int i = 1; i <= 10; i++)
		 CHESS_POS[1][i]._f1 = 66.0f;
	for (int i = 1; i <= 9; i++)
		 CHESS_POS[i][1]._f2 = 66.0f;
	for (int i = 2; i <= 9; i++)
		 CHESS_POS[i][1]._f1 = CHESS_POS[i - 1][1]._f1 + 80.0f;
	for (int i = 2; i <= 10; i++)
		 CHESS_POS[1][i]._f2 = CHESS_POS[1][i - 1]._f2 + 80.0f;
	for (int i = 2; i <= 9; i++) {
		for (int j = 2; j <= 5; j++) {
			CHESS_POS[i][j]._f2 = CHESS_POS[i][j - 1]._f2 + 80.0f;
			CHESS_POS[i][j]._f1 = CHESS_POS[i - 1][j]._f1 + 80.0f;
		}
	}
	for (int i = 1; i <= 9; i++)
		 CHESS_POS[i][6]._f2 = CHESS_POS[i][5]._f2 + 75.0f;
    for (int i = 2; i <= 9; i++)
		 CHESS_POS[i][6]._f1 = CHESS_POS[i - 1][6]._f1 + 80.0f;
	for (int i = 7; i <= 10; i++)
		 CHESS_POS[1][i]._f2 = CHESS_POS[1][i - 1]._f2 + 80.0f;
	for (int i = 2; i <= 9; i++) {
		for (int j = 7; j <= 10; j++) {
			CHESS_POS[i][j]._f2 = CHESS_POS[i][j - 1]._f2 + 80.0f;
			CHESS_POS[i][j]._f1 = CHESS_POS[i - 1][j]._f1 + 80.0f;
			}
	}
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
	State = GAME_STATE_RED_BEGIN;
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
void CleanGame() {
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 10; j++) {
			Map[i][j].Chess = FALSE;
			Map[i][j].MouseIn = FALSE;
			Map[i][j].MouseDown = FALSE;
		}
	LoadMsg();
}
void ReleaseAll() {
	SafeRelease(ChessRender);
	SafeRelease(&ChessBoard);
	for (int i = 0; i <= ChessPicesNum - 1; i++) {
		SafeRelease(&RedChessPieces[i]);
		SafeRelease(&BlackChessPieces[i]);
	}
	SafeRelease(&BoxBrush);
	SafeRelease(&BoxRedBrush);
	SafeRelease(&BoxGreenBrush);
	SafeRelease(&BoxFillBrush);
	SafeRelease(&ChessStyle);
}
//Render
void RenderChessBoard() {
	float RedAngle;
	float BlackAngle;
	float BoardAngle;
	if (MainView == Red) {
		RedAngle = 0.0f;
		BlackAngle = 180.0f;
		BoardAngle = 0.0f;
	}
	else {
		RedAngle = 180.0f;
		BlackAngle = 0.0f;
		BoardAngle = 180.0f;
	}
	MATRIX3x2 Matrix;
	Matrix.SetRotation(BoardAngle, float2::_float2(Width / 2.0f, Height / 2.0f));
	ChessRender->SetTransForm(Matrix);
	ChessRender->DrawBitMap(ChessBoard, Rect::_Rect(0.0f, (float)Width, 0.0f, (float)Height));
	ChessRender->EndTransForm();
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
	RectAngle._Rect = Rect::_Rect(0.0f, 76.0f, 0.0f, 76.0f);
	RectAngle._Filled = TRUE;
	RectAngle._StrokeWidth = 2.0f;
	if (Map[x][y].Chess == FALSE)
		RectAngle._Brush = BoxGreenBrush._Brush;
	else {
		if (Map[x][y].Color != Player)
			RectAngle._Brush = BoxRedBrush._Brush;
		else 
		RectAngle._Brush = BoxBrush._Brush;
	}
	Matrix.SetTranslation(float2::_float2(CHESS_POS[x][y]._f1 - ChessSizeWidthHalf,
		CHESS_POS[x][y]._f2 - ChessSizeHeightHalf));
	ChessRender->SetTransForm(Matrix);
	ChessRender->DrawRectAngle(RectAngle,ChessStyle,BoxFillBrush._Brush);
	ChessRender->EndTransForm();
}
//
void GetNextState() {
	if (State == GAME_STATE_RED_BEGIN) {
		if (Mode == Alone)
			Player = Red;
		State = GAME_STATE_RED_GET;
		return;
	}
	if (State == GAME_STATE_RED_GET) {
		if (Mode == Alone)
			Player = Black;
		State = GAME_STATE_BLACK_BEGIN; 
		return;
	}
	if (State == GAME_STATE_BLACK_BEGIN) {
		if (Mode == Alone)
			Player = Black;
		State = GAME_STATE_BLACK_GET;
		return;
	}
	if (State == GAME_STATE_BLACK_GET) {
		if (Mode == Alone)
			Player = Red;
		State = GAME_STATE_RED_BEGIN;
		return;
	}
}
void GetLastState() {
	if (State == GAME_STATE_RED_BEGIN) {
		if (Mode == Alone)
			Player = Black;
		State = GAME_STATE_BLACK_GET;
		return;
	}
	if (State == GAME_STATE_RED_GET) {
		if (Mode == Alone)
			Player = Red;
		State = GAME_STATE_RED_BEGIN;
		return;
	}
	if (State == GAME_STATE_BLACK_BEGIN) {
		if (Mode == Alone)
			Player = Red;
		State = GAME_STATE_RED_GET;
		return;
	}
	if (State == GAME_STATE_BLACK_GET) {
		if (Mode == Alone)
			Player = Black;
		State = GAME_STATE_BLACK_BEGIN;
		return;
	}
}
void GetRotationState() {
	if (State == GAME_STATE_RED_BEGIN) {
		if (Mode == Alone)
			Player = Black;
		State = GAME_STATE_BLACK_BEGIN;
		return;
	}
	if (State == GAME_STATE_RED_GET) {
		if (Mode == Alone)
			Player = Black;
		State = GAME_STATE_BLACK_GET;
		return;
	}
	if (State == GAME_STATE_BLACK_BEGIN) {
		if (Mode == Alone)
			Player = Red;
		State = GAME_STATE_RED_BEGIN;
		return;
	}
	if (State == GAME_STATE_BLACK_GET) {
		if (Mode == Alone)
			Player = Red;
		State = GAME_STATE_RED_GET;
		return;
	}
}
//
void MoveChessPices(int From_X, int From_Y, int To_X, int To_Y) {
	if (Map[To_X][To_Y].Chess == TRUE && Map[To_X][To_Y].Kind == CHESS_KING) {
		if (Map[To_X][To_Y].Color == Red)
			MessageBox(NULL, L"The Winer is Black", L"GameOver", 0);
		else 
			MessageBox(NULL, L"The Winer is Red", L"GameOver", 0);
		CleanGame();
		return;
	}
	Map[To_X][To_Y] = Map[From_X][From_Y];
	Map[From_X][From_Y].Chess = FALSE;
	Map[From_X][From_Y].MouseDown = FALSE;
	Map[From_X][From_Y].MouseIn = FALSE;
}
//Deal Mouse Event
void DealMouseMove(int PosX,int PosY){
	if (PosX < CHESS_POS[1][1]._f1 - BoxSizeWidthHalf) {
		Map[LastMousePos.x][LastMousePos.y].MouseIn = FALSE;
		return;
	}
	if (PosY < CHESS_POS[1][1]._f2 - BoxSizeHeightHalf) {
		Map[LastMousePos.x][LastMousePos.y].MouseIn = FALSE;
		return;
	}
	if (PosX > CHESS_POS[9][10]._f1 + BoxSizeWidthHalf) {
		Map[LastMousePos.x][LastMousePos.y].MouseIn = FALSE;
		return;
	}
	if (PosY > CHESS_POS[9][10]._f2 + BoxSizeHeightHalf) {
		Map[LastMousePos.x][LastMousePos.y].MouseIn = FALSE;
		return;
	}
	//.....
	Position Pos = MousePosToChessPos(Position::POS(PosX, PosY));
	if (Pos.x == 0 || Pos.y == 0) return;
	Map[LastMousePos.x][LastMousePos.y].MouseIn = FALSE;
	Map[Pos.x][Pos.y].MouseIn = TRUE;
	LastMousePos = Pos;
}
void DealMouseDown(int PosX, int PosY) {
	Position Pos = MousePosToChessPos(Position::POS(PosX, PosY));
	if (Pos.x == 0 || Pos.y == 0) return;
	if (Player == Red) {
		if (State == GAME_STATE_RED_BEGIN) {
			if (Map[Pos.x][Pos.y].Chess == TRUE && Map[Pos.x][Pos.y].Color == Red) {
				GetNextState();
				Map[Pos.x][Pos.y].MouseDown = TRUE;
				LastMouseDownPos = Pos;
			}
		}
		if (State == GAME_STATE_RED_GET) {
			BOOL CanGet = FALSE;
			int LastRoadSize = LastRoad.size();
			for (int i = 0; i <= LastRoadSize - 1; i++) {
				Map[LastRoad[i].x][LastRoad[i].y].MouseDown = FALSE;
				if (Pos.x == LastRoad[i].x && Pos.y == LastRoad[i].y) {
					CanGet = TRUE;
				}
			}
			if (Map[Pos.x][Pos.y].Chess == TRUE && Map[Pos.x][Pos.y].Color == Red) {
				vector<Position> Road;
				int RoadSize;
				GetChessPicesRoad(Map[Pos.x][Pos.y].Kind, Pos.x, Pos.y, Red, Road);
				RoadSize = Road.size();
				for (int i = 0; i <= RoadSize - 1; i++) {
					Map[Road[i].x][Road[i].y].MouseDown = TRUE;
				}
				Map[LastMouseDownPos.x][LastMouseDownPos.y].MouseDown = FALSE;
				Map[Pos.x][Pos.y].MouseDown = TRUE;
				LastMouseDownPos = Pos;
				LastRoad = Road;
				return;
			}
			if (CanGet == FALSE) {
				Map[LastMouseDownPos.x][LastMouseDownPos.y].MouseDown = FALSE;
				LastMouseDownPos = Pos;
				GetLastState();
				return;
			}
			if (CanGet == TRUE) {
				Map[LastMouseDownPos.x][LastMouseDownPos.y].MouseDown = FALSE;
				MoveChessPices(LastMouseDownPos.x, LastMouseDownPos.y, Pos.x, Pos.y);
				LastMouseDownPos = Pos;
				GetNextState();
				//RotationMainView();
				return;
			}
		}
	}
	if (Player == Black) {
		if (State == GAME_STATE_BLACK_BEGIN) {
			if (Map[Pos.x][Pos.y].Chess == TRUE && Map[Pos.x][Pos.y].Color == Black) {
				GetNextState();
				Map[Pos.x][Pos.y].MouseDown = TRUE;
				LastMouseDownPos = Pos;
			}
		}
		if (State == GAME_STATE_BLACK_GET) {
			BOOL CanGet = FALSE;
			int LastRoadSize = LastRoad.size();
			for (int i = 0; i <= LastRoadSize - 1; i++) {
				Map[LastRoad[i].x][LastRoad[i].y].MouseDown = FALSE;
				if (Pos.x == LastRoad[i].x && Pos.y == LastRoad[i].y) {
					CanGet = TRUE;
				}
			}
			if (Map[Pos.x][Pos.y].Chess == TRUE && Map[Pos.x][Pos.y].Color == Black) {
				vector<Position> Road;
				int RoadSize;
				GetChessPicesRoad(Map[Pos.x][Pos.y].Kind, Pos.x, Pos.y, Black, Road);
				RoadSize = Road.size();
				for (int i = 0; i <= RoadSize - 1; i++) {
					Map[Road[i].x][Road[i].y].MouseDown = TRUE;
				}
				Map[LastMouseDownPos.x][LastMouseDownPos.y].MouseDown = FALSE;
				Map[Pos.x][Pos.y].MouseDown = TRUE;
				LastMouseDownPos = Pos;
				LastRoad = Road;
				return;
			}
			if (CanGet == FALSE) {
				Map[LastMouseDownPos.x][LastMouseDownPos.y].MouseDown = FALSE;
				LastMouseDownPos = Pos;
				GetLastState();
				return;
			}
			if (CanGet == TRUE) {
				Map[LastMouseDownPos.x][LastMouseDownPos.y].MouseDown = FALSE;
				MoveChessPices(LastMouseDownPos.x, LastMouseDownPos.y, Pos.x, Pos.y);
				LastMouseDownPos = Pos;
				GetNextState();
			//	RotationMainView();
				return;
			}
		}
	}
}
//Get Pos We Can Get
void GetKingRoad(int PosX,int PosY, BOOL Color, vector<Position> &Road){
	Road.resize(4);
	if (Color == MainView) {
		if (PosY != 10) {
			if ((Map[PosX][PosY + 1].Chess == TRUE && Map[PosX][PosY + 1].Color != Color) ||
				(Map[PosX][PosY + 1].Chess == FALSE))
				Road.push_back(Position::POS(PosX, PosY + 1));
		}
		if (PosY != 8) {
			if ((Map[PosX][PosY - 1].Chess == TRUE && Map[PosX][PosY - 1].Color != Color) ||
				(Map[PosX][PosY - 1].Chess == FALSE))
				Road.push_back(Position::POS(PosX, PosY - 1));
		}
		if (PosX != 4) {
			if ((Map[PosX - 1][PosY].Chess == TRUE && Map[PosX - 1][PosY].Color != Color) ||
				(Map[PosX - 1][PosY].Chess == FALSE))
				Road.push_back(Position::POS(PosX - 1, PosY));
		}
		if (PosY != 6) {
			if ((Map[PosX + 1][PosY].Chess == TRUE && Map[PosX + 1][PosY].Color != Color) ||
				(Map[PosX + 1][PosY].Chess == FALSE))
				Road.push_back(Position::POS(PosX + 1, PosY));
		}
	}
	if (Color != MainView) {
		if (PosY != 1) {
			if ((Map[PosX][PosY - 1].Chess == TRUE && Map[PosX][PosY - 1].Color != Color) ||
				(Map[PosX][PosY - 1].Chess == FALSE))
				Road.push_back(Position::POS(PosX, PosY - 1));
		}
		if (PosY != 3) {
			if ((Map[PosX][PosY + 1].Chess == TRUE && Map[PosX][PosY + 1].Color != Color) ||
				(Map[PosX][PosY + 1].Chess == FALSE))
				Road.push_back(Position::POS(PosX, PosY + 1));
		}
		if (PosX != 4) {
			if ((Map[PosX - 1][PosY].Chess == TRUE && Map[PosX - 1][PosY].Color != Color) ||
				(Map[PosX - 1][PosY].Chess == FALSE))
				Road.push_back(Position::POS(PosX - 1, PosY));
		}
		if (PosY != 6) {
			if ((Map[PosX + 1][PosY].Chess == TRUE && Map[PosX + 1][PosY].Color != Color) ||
				(Map[PosX + 1][PosY].Chess == FALSE))
				Road.push_back(Position::POS(PosX + 1, PosY));
		}
	}
}
void GetGuardRoad(int PosX, int PosY, BOOL Color, vector<Position> &Road) {
	Road.resize(4);
	Position Offset[4];
	int Left, Right, Top, Bottom;
	Offset[0] = Position::POS(1, 1);
	Offset[1] = Position::POS(1, -1);
	Offset[2] = Position::POS(-1, 1);
	Offset[3] = Position::POS(-1, -1);
	if (Color == MainView) {
		Left = 4;
		Right = 6;
		Top = 8;
		Bottom = 10;
	}
	if (Color != MainView) {
		Left = 4;
		Right = 6;
		Top = 1;
		Bottom = 3;
	}
	for (int i = 0; i <= 3; i++) {
		int X = PosX + Offset[i].x;
		int Y = PosY + Offset[i].y;
		if (X >= Left && X <= Right && Y >= Top && Y <= Bottom) {
			if ((Map[X][Y].Chess == TRUE && Map[X][Y].Color != Color) || (Map[X][Y].Chess == FALSE))
				Road.push_back(Position::POS(X, Y));
		}
	}
}
void GetBishopRoad(int PosX, int PosY, BOOL Color, vector<Position> &Road) {
	Road.resize(4);
	Position Offset[4];
	Position OffsetCan[4];
	int Left, Right, Top, Bottom;
	Offset[0] = Position::POS(2, 2);
	Offset[1] = Position::POS(2, -2);
	Offset[2] = Position::POS(-2, 2);
	Offset[3] = Position::POS(-2, -2);
	OffsetCan[0] = Position::POS(1, 1);
	OffsetCan[1] = Position::POS(1, -1);
	OffsetCan[2] = Position::POS(-1, 1);
	OffsetCan[3] = Position::POS(-1, -1);
	if (Color == MainView) {
		Left = 1;
		Right = 9;
		Top = 6;
		Bottom = 10;
	}
	if (Color != MainView) {
		Left = 1;
		Right = 9;
		Top = 1;
		Bottom = 5;
	}
	for (int i = 0; i <= 3; i++) {
		int X = PosX + Offset[i].x;
		int Y = PosY + Offset[i].y;
		if (Map[PosX + OffsetCan[i].x][PosY + OffsetCan[i].y].Chess == FALSE)
			if (X >= Left && X <= Right && Y >= Top && Y <= Bottom) {
				if ((Map[X][Y].Chess == TRUE && Map[X][Y].Color != Color) || (Map[X][Y].Chess == FALSE))
					Road.push_back(Position::POS(X, Y));
			}
	}
}
void GetKnightRoad(int PosX, int PosY, BOOL Color, vector<Position> &Road) {
	Position Offset[8];
	Position OffsetCan[4];
	Road.resize(8);
	Offset[0] = Position::POS(1, 2);
	Offset[1] = Position::POS(-1, 2);

	Offset[2] = Position::POS(2, 1);
	Offset[3] = Position::POS(2, -1);

	Offset[4] = Position::POS(1, -2);
	Offset[5] = Position::POS(-1, -2);

	Offset[6] = Position::POS(-2, -1);
	Offset[7] = Position::POS(-2, 1);

	OffsetCan[0] = Position::POS(0,1);
	OffsetCan[1] = Position::POS(1,0);
	OffsetCan[2] = Position::POS(0,-1);
	OffsetCan[3] = Position::POS(-1,0);
	for (int i = 0; i <= 7; i++) {
		int X = PosX + Offset[i].x;
		int Y = PosY + Offset[i].y;
		int CanX = PosX + OffsetCan[i / 2].x;
		int CanY = PosY + OffsetCan[i / 2].y;
		if (X >= 1 && X <= 9 && Y >= 1 && Y <= 10) {
			if ((Map[X][Y].Chess == TRUE && Map[X][Y].Color != Color) || Map[X][Y].Chess == FALSE) {
				if (Map[CanX][CanY].Chess == FALSE) {
					Road.push_back(Position::POS(X, Y));
				}
			}
		}
	}
}
void GetRookRoad(int PosX, int PosY, BOOL Color, vector<Position> &Road) {
	Road.resize(20);
	for (int i = PosX - 1; i >= 1; i--) {
		if (Map[i][PosY].Chess == TRUE) {
			if (Map[i][PosY].Color != Color) {
				Road.push_back(Position::POS(i, PosY));
			}
			break;
		}
		Road.push_back(Position::POS(i, PosY));
	}
	for (int i = PosX + 1; i <= 9; i++) {
		if (Map[i][PosY].Chess == TRUE) {
			if (Map[i][PosY].Color != Color) {
				Road.push_back(Position::POS(i, PosY));
			}
			break;
		}
		Road.push_back(Position::POS(i, PosY));
	}
	for (int i = PosY - 1; i >= 1; i--) {
		if (Map[PosX][i].Chess == TRUE) {
			if (Map[PosX][i].Color != Color) {
				Road.push_back(Position::POS(PosX, i));
			}
			break;
		}
		Road.push_back(Position::POS(PosX, i));
	}
	for (int i = PosY + 1; i <= 10; i++) {
		if (Map[PosX][i].Chess == TRUE) {
			if (Map[PosX][i].Color != Color) {
				Road.push_back(Position::POS(PosX, i));
			}
			break;
		}
		Road.push_back(Position::POS(PosX, i));
	}
}
void GetCannonRoad(int PosX, int PosY, BOOL Color, vector<Position> &Road) {
	int Stop1=0, Stop2=0, Stop3=0, Stop4=0;
	Road.resize(20);
	for (int i = PosX - 1; i >= 1; i--) {
		if (Map[i][PosY].Chess == TRUE) {
			Stop1 = i;
			break;
		}
		Road.push_back(Position::POS(i, PosY));
	}
	for (int i = PosX + 1; i <= 9; i++) {
		if (Map[i][PosY].Chess == TRUE) {
			Stop2 = i;
			break;
		}
		Road.push_back(Position::POS(i, PosY));
	}
	for (int i = PosY - 1; i >= 1; i--) {
		if (Map[PosX][i].Chess == TRUE) {
			Stop3 = i;
			break;
		}
		Road.push_back(Position::POS(PosX, i));
	}
	for (int i = PosY + 1; i <= 10; i++) {
		if (Map[PosX][i].Chess == TRUE) {
			Stop4 = i;
			break;
		}
		Road.push_back(Position::POS(PosX, i));
	}
    //
	if (Stop1 != 0)
	for (int i = Stop1 - 1; i >= 1; i--) {
		if (Map[i][PosY].Chess == TRUE) {
			if (Map[i][PosY].Color == Color)
				break;
			Road.push_back(Position::POS(i, PosY));
			break;
		}
	}
	if (Stop2 != 0)
	for (int i = Stop2 + 1; i <= 9; i++) {
		if (Map[i][PosY].Chess == TRUE) {
			if (Map[i][PosY].Color == Color)
				break;
			Road.push_back(Position::POS(i, PosY));
			break;
		}
	}
	if (Stop3 != 0)
	for (int i = Stop3 - 1; i >= 1; i--) {
		if (Map[PosX][i].Chess == TRUE) {
			if (Map[PosX][i].Color == Color)
				break;
			Road.push_back(Position::POS(PosX, i));
			break;
		}
	}
	if (Stop4 != 0)
	for (int i = Stop4 + 1; i <= 10; i++) {
		if (Map[PosX][i].Chess == TRUE) {
			if (Map[PosX][i].Color == Color)
				break;
			Road.push_back(Position::POS(PosX, i));
			break;
		}
	}
}
void GetPawnRoad(int PosX, int PosY, BOOL Color, vector<Position> &Road) {
	Position Offset[3];
	int Size=0;
	Road.resize(3);
	if (Color == MainView) {
		Offset[0] = Position::POS(0, -1);
		if (PosY <= 5) {
			Offset[1] = Position::POS(1, 0);
			Offset[2] = Position::POS(-1, 0);
			Size = 2;
		}
	}
	if (Color != MainView) {
		Offset[0] = Position::POS(0, 1);
		if (PosY >= 6) {
			Offset[1] = Position::POS(1, 0);
			Offset[2] = Position::POS(-1, 0);
			Size = 2;
		}
	}
	for (int i = 0; i <= Size; i++) {
		int X = PosX + Offset[i].x;
		int Y = PosY + Offset[i].y;
		if ((Map[X][Y].Chess == TRUE && Map[X][Y].Color != Color) || (Map[X][Y].Chess == FALSE))
			Road.push_back(Position::POS(X, Y));
	}
}
void GetChessPicesRoad(CHESS_KIND Kind, int PosX, int PosY, BOOL Color, vector<Position> &Road) {
	if (Kind == CHESS_KING) {
		GetKingRoad(PosX, PosY, Color, Road);
	}
	if (Kind == CHESS_GUARD) {
		GetGuardRoad(PosX, PosY, Color, Road);
	}
	if (Kind == CHESS_BISHOP) {
		GetBishopRoad(PosX, PosY, Color, Road);
	}
	if (Kind == CHESS_KNIGHT) {
		GetKnightRoad(PosX, PosY, Color, Road);
	}
	if (Kind == CHESS_ROOK) {
		GetRookRoad(PosX, PosY, Color, Road);
	}
	if (Kind == CHESS_CANNON) {
		GetCannonRoad(PosX, PosY, Color, Road);
	}
	if (Kind == CHESS_PAWN) {
		GetPawnRoad(PosX, PosY, Color, Road);
	}
	int KingNum = 0;
	int ChessPiceNum = 0;
	for (int i = 1; i <= 10; i++) {
		if (Map[PosX][i].Chess == TRUE) {
			ChessPiceNum++;
			if (Map[PosX][i].Kind == CHESS_KING)
				KingNum++;
		}
	}
	if (KingNum == 2 && ChessPiceNum == 3) {
		Road.clear();
	}
	if (Kind == CHESS_KING) {
		vector<Position> NewRoad;
		BOOL Meetking = FALSE;
		BOOL CanGet = TRUE;
		int Size = Road.size();
		int NewSize = 0;
		NewRoad.resize(Size);
		for (int i = 0; i <= Size - 1; i++) {
			CanGet = TRUE;
			if (MainView == Color) {	
				for (int j = Road[i].y; j >= 1; j--) {
					if (Map[Road[i].x][j].Chess == TRUE) {
						if (Map[Road[i].x][j].Kind == CHESS_KING)
							CanGet = FALSE;
						break;
					}
				}
			}
			if (MainView != Color) {
				for (int j = Road[i].y; j <= 10; j++) {
					if (Map[Road[i].x][j].Chess == TRUE) {
						if (Map[Road[i].x][j].Kind == CHESS_KING)
							CanGet = FALSE;
						break;
					}
				}
			}
			if (CanGet == TRUE || PosX==Road[i].x) {
				NewRoad.push_back(Road[i]);
			}
		}
		Road.clear();
		NewSize = NewRoad.size();
		for (int i = 0; i <= NewSize - 1; i++) {
			Road.push_back(NewRoad[i]);
		}
	}
}
//Rotation MainView
void RotationMainView() {
	Chess_State MAP[10][11];
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 10; j++) {
			MAP[i][j].Chess = FALSE;
		}
	if (MainView == Red) {
		MainView = Black;
	}
	else {
		MainView = Red;
	}
	
	int X = 5;
	int Y1 = 5;
	int Y2 = 6;
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 5; j++) {
			if (Map[i][j].Chess == TRUE) {
				MAP[X - (i - X)][Y2 - (j - Y1)] = Map[i][j];
			
			}
		}
	for (int i = 1; i <= 9; i++)
		for (int j = 6; j <= 10; j++) {
			if (Map[i][j].Chess == TRUE) {
				MAP[X - (i - X)][Y1 - (j - Y2)] = Map[i][j];
			
			}
		}
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 10; j++) {
			Map[i][j] = MAP[i][j];
		}
}
void RotationMainViewAlone() {
	if (MainView == Red) {
		MainView = Black;
	}
	else {
		MainView = Red;
	}
}
//233
Position MousePosToChessPos(Position Pos) {
	if (Pos.y >= CHESS_POS[1][6]._f2) {
		Pos.x += 12;
		Pos.y += 24;
	}
	else {
		Pos.x += 12;
		Pos.y += 14;
	}
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 10; j++) {
			float Left = CHESS_POS[i][j]._f1 - ChessSizeWidthHalf;
			float Right = Left + ChessSizeWidth;
			float Top = CHESS_POS[i][j]._f2 - ChessSizeHeightHalf;
			float Bottom = Top + ChessSizeHeight;
			if (Pos.x >= Left && Pos.x <= Right && Pos.y >= Top && Pos.y <= Bottom) {
				Position Result;
				Result.x = i;
				Result.y = j;
				return Result;
			}
		}
	return Position::POS(0, 0);
}
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
