#ifndef SNAKE_GAME_H_
#define SNAKE_GAME_H_

//------------------------------------------------------------------------
//
//  [11/18/2012 KimSiHoon]
//
//  Name:   Snake_Game.h
//
//  Desc:   허브클래스, 이곳에 게임로직이 들어간다. 
//
//  Author: 김시훈 (bongnam_go@naver.com) 
//
//------------------------------------------------------------------------

#include <iostream>
#include <time.h>
#include "Map.h"
#include "Define.h"
#include "MapManager.h"
#include "Snake.h"

using namespace std;

class Snake_Game
{

public:

	Snake_Game();

	~Snake_Game();

	void Run();
	void SetGameOver(bool gameover){ gameover_ = gameover; }

private:

	typedef enum { STAGE_ONE, STAGE_TWO, STAGE_THREE, STAGE_FOUR } STAGE;

	const int kMaxItemPosWidth;
	const int kMaxItemPosHeigh;
	unsigned int current_stage_;

	int item_num_;
	int speed_;
	int goal_item_num_;

	Snake *snake_;

	bool gameover_;

private:

	void SetGame();
	void LoadGame();
	bool InitGame();
	void Input();
	void Update();
	void Render();

	void DrawUI();
	bool IsGameOver()
	{
		return gameover_;
	}

};

#endif

