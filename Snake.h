#ifndef SNAKE_H_
#define SNAKE_H_

//------------------------------------------------------------------------
//
//  [11/18/2012 KimSiHoon]
//
//  Name:   Snake.h
//
//  Desc:   Snake 정의 
//
//  Author: 김시훈 (bongnam_go@naver.com) 
//
//------------------------------------------------------------------------

#include "Define.h"
#include <list>
#include <iostream>

class Snake
{

public:

	//뱀의 움직임을 기억할 좌표 리스트
	std::list<Position> typedef SNAKE_TRACE;

	//뱀의 충동체크를 위한 Enumlator
	//COLLIDE = 벽이나 꼬리에 충돌, NOT_COLLIDE = 충돌안함 ,EAT_ITEM = 아이템먹음
	typedef enum { COLLIDE, NOT_COLLIDE, EAT_ITEM } SNAKE_COLLIDE;

	//뱀의 진행 방향
	typedef enum{ LEFT=75, RIGHT=77 ,UP=72, DOWN=80 } DIRECTION;

public:

	Snake() : direction_(RIGHT),current_position_(7,5),life_(5),grow_goal_(0)
	{
		this->InitSnake();
	}

	~Snake()
	{
	}

	//뱀을 초기화
	void InitSnake();
	void Update();

	//충돌체크
	int IsCollide();

	//뱀의 몸이 자라고 있는지 체크
	bool IsGrowing();

	int GetLife() const { return life_; }
	SNAKE_TRACE GetTrace() const { return snake_trace_; } 
	DIRECTION GetDirection() const { return direction_; }
	Position GetPosition() const { return current_position_; }
	int GetLength() const { return length_; }

	void SetDirection(DIRECTION direction) { direction_ = direction; }

	void DecreLife() 
	{
		if(life_ >= 0)
		{
			life_ --; 
		}
	}

private:

	//뱀의 좌표 리스트
	SNAKE_TRACE snake_trace_;

	//현재 뱀의 방향
	DIRECTION direction_;

	//현재 머리의 위치
	Position current_position_;

	//목숨
	int life_;

	//몸의 길이
	int length_;

	//자라야할 몸의 길이 목표치
	int grow_goal_;

};
#endif