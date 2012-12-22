#ifndef DEFINE_H_
#define DEFINE_H_

//------------------------------------------------------------------------
//
//  [11/18/2012 KimSiHoon]
//
//  Name:   Define.h
//
//  Desc:   전역적으로 사용될 변수 및 타입 , 함수들을 정의한다.    
//
//  Author: 김시훈 (bongnam_go@naver.com) 
//
//------------------------------------------------------------------------

//------------------------------  Include  ------------------------------------
// System Include 
//-----------------------------------------------------------------------------
#include <conio.h>
#include <stdio.h>
#include <Windows.h>

//-----------------------------  CURSOR_TYPE  ---------------------------------
// 커서의 타입정의
//-----------------------------------------------------------------------------
typedef enum 
{ 
	NOCURSOR, 
	SOLIDCURSOR,
	NORMALCURSOR 

} CURSOR_TYPE;

//-------------------------------  Position  ----------------------------------
// 좌표 클래스
//-----------------------------------------------------------------------------
class Position
{

public: 

	Position(int x,int y): x_(x),y_(y)
	{}
	~Position(){}
	int x_;
	int y_;

};

//----------------------------  Grobal Funtion  -------------------------------
// 콘솔용 유틸리티 함수
//-----------------------------------------------------------------------------
void SetCursorType(CURSOR_TYPE c);
void MoveCursor(Position pos);
int Getchon(Position pos);
void DrawObject(Position pos, char text);
void DrawObject(Position pos, int item);
void WaitAnyKey();

#endif