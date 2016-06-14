#include "Define.h"

// test 어떻게 처리 될 것인지 --



//-----------------------------  SetCursorType  -------------------------------
// 커서의 타입정의
//-----------------------------------------------------------------------------
void SetCursorType(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;
// 리뷰 진행 방식 
	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize=1;
		CurInfo.bVisible=FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize=100;
		CurInfo.bVisible=TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize=20;
		CurInfo.bVisible=TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}

//------------------------------  MoveCursor  ---------------------------------
// 커서를 해당 좌표로 움직인다.
//-----------------------------------------------------------------------------
void MoveCursor(Position pos)
{
	COORD Pos = { pos.x_, pos.y_ };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//------------------------------  DrawObject  ---------------------------------
// 해당 좌표에 text를 뿌린다.
//-----------------------------------------------------------------------------
void DrawObject(Position pos, char text)
{
	MoveCursor(pos);
	printf("%s",&text);
}

//------------------------------  DrawObject  ---------------------------------
// 해당 좌표에 숫자를 뿌린다
//-----------------------------------------------------------------------------
void DrawObject(Position pos, int item)
{
	MoveCursor(pos);
	printf("%d",item);
}

//------------------------------  Getchon  ------------------------------------
// 해당 좌표의 값을 char형으로 읽어온다.
//-----------------------------------------------------------------------------
int Getchon(Position pos)
{
	COORD Cur;
	Cur.X= pos.x_;
	Cur.Y= pos.y_;
	TCHAR Char;
	DWORD dwRead;

	ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE),
		&Char,1,Cur,&dwRead);
	return Char;
}

//------------------------------  WaitAnyKey  ---------------------------------
// 하나의 키가 입력될때까지 기다린다.
//-----------------------------------------------------------------------------
void WaitAnyKey()
{
	int ch;

	ch=getch();
	if (ch==0xE0 || ch==0) {
		getch();
	}
}
