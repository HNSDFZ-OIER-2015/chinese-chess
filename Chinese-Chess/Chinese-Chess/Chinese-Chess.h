#pragma once

#include "resource.h"
#include<L-D-Math-Main.h>
#include<stdlib.h>
#include"Chess-Define.h"
#include<L-D-2-1.h>
#include<L-D-2-2.h>
using namespace L_D_2;
using namespace L_D_2_1;
int Width = 773;
int Height = 845;
BOOL MainView=Red;
Origin* ChessRender;
ORIGIN_BITMAP RedChessPieces[7];
ORIGIN_BITMAP BlackChessPieces[7];
ORIGIN_BITMAP ChessBoard;
float2 CHESS_POS[10][11];
Chess_State Map[10][11];
void LoadResource();
void LoadMsg();
void Init(Origin* &LD, HWND Hwnd, int Width, int Height);
void ReleaseAll();
void RenderChessBoard();
void RenderChessPices(CHESS_KIND Kind, BOOL Color, float Angle, Position Pos);
//
void SetMap(int i, int j, CHESS_KIND Kind, BOOL Color) {
	Map[i][j].Chess = TRUE;
	Map[i][j].Kind = Kind;
	Map[i][j].Color = Color;
}
void CleanMap(int i, int j) {
	Map[i][j].Chess = FALSE;
}
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
	ChessRender->LoadBitMap(&ChessBoard);
	for (int i = 0; i <= ChessPicesNum - 1; i++) {
		ChessRender->LoadBitMap(&RedChessPieces[i]);
		ChessRender->LoadBitMap(&BlackChessPieces[i]);
	}
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
	for (int i = 1; i <= 9; i++)
		for (int j = 1; j <= 10; j++) {
			Map[i][j].Chess = FALSE;
		}

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
void ReleaseAll() {
	SafeRelease(ChessRender);
	SafeRelease(&ChessBoard);
	for (int i = 0; i <= ChessPicesNum - 1; i++) {
		SafeRelease(&RedChessPieces[i]);
		SafeRelease(&BlackChessPieces[i]);
	}
}
void RenderChessBoard() {
	ChessRender->DrawBitMap(ChessBoard, Rect::_Rect(0.0f, (float)Width, 0.0f, (float)Height));
	float RedAngle;
	float BlackAngle;
	if (MainView == Red) {
		RedAngle = 0.0f;
		BlackAngle = 180.0f;
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
//
