#include "Snake_Game.h"

//------------------------------- Snake_Game ----------------------------------
// 게임에 필요한 뱀, 맵에 메모리를 할당하고 값들을 초기화 해준다.
//-----------------------------------------------------------------------------
Snake_Game::Snake_Game() : gameover_(false) , item_num_(0) , speed_ (150) , kMaxItemPosHeigh(17), kMaxItemPosWidth(75)
{
	snake_ = new Snake();

	current_stage_ = STAGE_ONE;

	Map* stage_one = new Map(STAGE_ONE,"Stage1.txt");
	Map* stage_two = new Map(STAGE_TWO,"Stage2.txt");
	Map* stage_three = new Map(STAGE_THREE,"Stage3.txt");
	Map* stage_four = new Map(STAGE_FOUR,"Stage4.txt");

	MAP_MANAGER->RegisterMap(stage_one);
	MAP_MANAGER->RegisterMap(stage_two);
	MAP_MANAGER->RegisterMap(stage_three);
	MAP_MANAGER->RegisterMap(stage_four);

	this->SetGame();
    
    
    
};

//------------------------------- SetGame -------------------------------------
// 게임을 처음 시작했을때 스테이지를 고를 수 있도록 해준다.
//-----------------------------------------------------------------------------
void Snake_Game::SetGame()
{
	while(true)
	{
		this->InitGame();
		
		//UI를 위해서
		MoveCursor(Position(14,21));
		puts("N = 다음 스테이지 / P = 이전 스테이지 / S = 시작");

		int ch=getch();

		//키값을 받고, N이면 다음스테이지 P면 이전스테이지 S를 누르면 루프를빠져간다.
		if (ch == 0xE0) 
		{
			getch();
		} 
		else 
		{
			if (tolower(ch) == 'n') 
			{
				if(current_stage_ < STAGE_FOUR)
				{
					current_stage_++;
				}
			}
			if (tolower(ch) == 'p') 
			{
				if(current_stage_ > STAGE_ONE)
				{
					current_stage_--;
				}
			}
			if (tolower(ch) == 's')
			{
				break;
			}
		}
	}

	//UI를 지우기위해,/
	MoveCursor(Position(14,21));
	puts("                                                 ");
}

//------------------------------- InitGame ------------------------------------
// 게임을 초기화한다.
//-----------------------------------------------------------------------------
bool Snake_Game::InitGame()
{
	SetCursorType(NOCURSOR);

	this->LoadGame();

	srand(time(NULL));

	//남은 아이템만큼 아이템을 그려준다.
	for (int i=item_num_;i<goal_item_num_;i++)
	{
		while(true)
		{
			Position dummy(rand()%kMaxItemPosWidth,rand()%kMaxItemPosHeigh);
			if(Getchon(dummy) == ' ')
			{
				DrawObject(dummy,rand()%9+1);
				break;
			}
		}
	}

	return true;
}

//------------------------------- LoadGame ------------------------------------
// 게임에 현재 스테이지에 해당하는 맵과 값들을 불러온다.
//-----------------------------------------------------------------------------
void Snake_Game::LoadGame()
{
	system("cls");

	MAP_MANAGER->GetMapFromID(current_stage_)->LoadMap();

	switch(current_stage_)
	{
	case STAGE_ONE:
		{
			speed_ = 150;
			goal_item_num_ = 10;
			snake_->InitSnake();
		}
		break;
	case STAGE_TWO:
		{
			speed_ = 100;
			goal_item_num_ = 15;
			snake_->InitSnake();
		}
		break;
	case STAGE_THREE:
		{
			speed_ = 80;
			goal_item_num_ = 20;
			snake_->InitSnake();
		}
		break;
	case STAGE_FOUR:
		{
			speed_ = 50;
			goal_item_num_ = 25;
			snake_->InitSnake();
		}
		break;
	}

	this->DrawUI();
}

//-------------------------------- Input --------------------------------------
// 사용자의 입력값을 처리해주는 함수
//-----------------------------------------------------------------------------
void Snake_Game::Input()
{
	int ch;

	if (!kbhit()) {
		return;
	}

	ch=getch();

	//뱀은 현재 진행방향의 반대방향으로는 움직이지 못한다.
	//스페이스를 누르면 멈출수 있다.
	if (ch == 0xE0 || ch == 0) 
	{
		ch=getch();
		switch (ch) 
		{
		case Snake::LEFT:
			if (snake_->GetDirection() != Snake::RIGHT) snake_->SetDirection(Snake::LEFT);
			break;
		case Snake::RIGHT:
			if (snake_->GetDirection() != Snake::LEFT) snake_->SetDirection(Snake::RIGHT);
			break;
		case Snake::UP:
			if (snake_->GetDirection() != Snake::DOWN) snake_->SetDirection(Snake::UP);
			break;
		case Snake::DOWN:
			if (snake_->GetDirection() != Snake::UP) snake_->SetDirection(Snake::DOWN);
			break;
		}
	}
	else
	{
		switch (tolower(ch))
		{
		case 27:
			SetCursorType(NORMALCURSOR);
			exit(0);
		case ' ':
			WaitAnyKey();
			break;
		}
	}
}

//-------------------------------- Update -------------------------------------
// 로직
//-----------------------------------------------------------------------------
void Snake_Game::Update()
{
	//사용자의 입력을 받는다.
	this->Input();

	//뱀의 움직임을 업데이트한다.
	snake_->Update();

	//뱀의 현재 충돌했는가?
	switch(snake_->IsCollide())
	{
	case Snake::COLLIDE :
		{
			//벽이나 몸에 충돌했다면,
			//라이프를 하나 감소시킨다.
			//만약 목숨이 0보다 작아진다면 게임은 끝난다.
			//그렇지 않다면 화면을 지워주고, 0.5초의 딜레이후 게임을 다시시작한다.
			snake_->DecreLife();

			if(snake_->GetLife() < 0)
			{
				this->SetGameOver(true);
				MoveCursor(Position(12,20));
				puts("게임이 끝났습니다. 그만 놀고 열심히 공부하세요.");
			}
			else
			{
				this->InitGame();
				this->DrawUI();
				Sleep(500);
			}
		}
		break;

	case Snake::EAT_ITEM :
		{
			//아이템을 먹었다면,
			//현재 아이템값을 증가시켜준다.
			//만약 목표치만큼 아이템을 먹었다면
			//스테이지 클리어 이벤트를 발생시키고 키를 입력받아 다음스테이지로 간다.
			item_num_++;
			if (item_num_ == goal_item_num_) 
			{
				MoveCursor(Position(12,20));
				puts("축하합니다. 아무 키나 누르시면 다음 스테이지로 갑니다.");
				WaitAnyKey();
				current_stage_++;
				item_num_ = 0;
				this->InitGame();
				Sleep(500);
			}
		}

		break;
	}
	Sleep(this->speed_);
}

//-------------------------------- Render -------------------------------------
// 렌더함수
//-----------------------------------------------------------------------------
void Snake_Game::Render()
{
	//UI를 그린다.
	this->DrawUI();

	//뱀의 흔적을 받아온다.
	Snake::SNAKE_TRACE dummy = snake_->GetTrace();

	//흔적대로 뱀을 그린다.
	for(Snake::SNAKE_TRACE::iterator it = dummy.begin(); it != dummy.end(); it++)
	{
		DrawObject((*it),'#');
	}

	//맨뒤는 ' '로 지워준다.
	//이작업을 안한다면 흔적에는 없으나 화면에는 계속 뱀의 흔적이 보인다.
	//만약 전체 화면을 지우고 다시 그리는 작업을 하면
	//화면이 깜빡이는 현상이 일어난다.
	DrawObject(dummy.back(),' ');

	//현재위치에는 뱀의 머리를 그려준다.
	DrawObject(snake_->GetPosition(),'S');
}

//--------------------------------- Run ---------------------------------------
// 루프
//-----------------------------------------------------------------------------
void Snake_Game::Run()
{
	while(!this->IsGameOver())
	{
		Update();
		Render();
	}
}

//--------------------------------- DrawUI ------------------------------------
// UI를 그린다.
//-----------------------------------------------------------------------------
void Snake_Game::DrawUI()
{
	MoveCursor(Position(0,23));printf("스테이지 : %d",current_stage_+1);
	MoveCursor(Position(20,23));printf("남은 뱀 : %d",snake_->GetLife());
	MoveCursor(Position(40,23));printf("              ");
	MoveCursor(Position(40,23));printf("남은 먹이 : %d",goal_item_num_ - item_num_);
	MoveCursor(Position(60,23));printf("꼬리 길이 : %d",snake_->GetLength());
}

//--------------------------------- ~Snake_Game -------------------------------
// 소멸자
//-----------------------------------------------------------------------------
Snake_Game::~Snake_Game()
{
	MAP_MANAGER->Destory();
	delete snake_;
}