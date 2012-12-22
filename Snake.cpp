#include "Snake.h"

//------------------------------- InitSnake -----------------------------------
// 뱀의 길이/위치/방향을 초기화해준다.
//-----------------------------------------------------------------------------
void Snake::InitSnake()
{
	//현재 뱀의 좌표값을 비운다.
	snake_trace_.clear();

	//초기뱀의 좌표를 넣어준다.
	//좌표는 항상 몸의길이 + 1만큼이 있어야한다.
	//그래야만 뱀이 마지막으로 지나간곳을 Snake_Game에서 지워줄 수 있다.
	snake_trace_.push_back(Position(7,5));
	snake_trace_.push_back(Position(6,5));
	snake_trace_.push_back(Position(5,5));
	snake_trace_.push_back(Position(4,5));

	current_position_ = Position(7,5);
	direction_ = RIGHT;
	length_ = 2;
	grow_goal_ = 0;
}

//-------------------------------- Update -------------------------------------
// 뱀의 방향대로 움직이고, 좌표를 흔적리스트에 넣어준다.
//-----------------------------------------------------------------------------
void Snake::Update()
{
	switch (direction_) 
	{

	case LEFT:
		current_position_.x_ --;
		break;

	case RIGHT:
		current_position_.x_ ++;
		break;

	case UP:
		current_position_.y_ --;
		break;

	case DOWN:
		current_position_.y_ ++;
		break;
	}

	//좌표를 기억한다.
	snake_trace_.push_front(current_position_);

	//뱀이 자라고 있는중이면 좌표를 빼지않는다.
	if(this->IsGrowing() == false)
	{
		snake_trace_.pop_back();
	}
}

int Snake::IsCollide()
{
	//현재 위치의 값을 dummy에 집어넣는다.
	int dummy = Getchon(current_position_);

	//만약 더미의 위치가 비어있지 않다면,
	if(dummy != ' ')
	{
		//더미값을 확인한다.
		//벽이나 자신의 몸이라면
		//COLLIDE값을 반환한다.
		if(dummy == 'M' || dummy == '#')
		{
			return COLLIDE;
		}
		//아니라면 아이템을 먹은것이다.
		else
		{
			//dummy는 char형이기 떄문에
			//int로 바꾸기위해 49를 빼준다.
			grow_goal_ = dummy-49;

			return EAT_ITEM;
		}
	}

	return NOT_COLLIDE;
}

//------------------------------- IsGrowing -----------------------------------
// 뱀이 현재 커지고 있는지 확인한다.
//-----------------------------------------------------------------------------
bool Snake::IsGrowing()
{
	//grow_goal이 0보다 작다면 크고있지 않다는것이다.
	//만약 크고있다면 1프레임당 몸을 1씩 늘리고,
	//grow_goal을 1 감소 시킨다.
	if(grow_goal_ < 0)
	{
		return false;
	}
	else
	{
		grow_goal_--;
		length_++;
	}

	return true;
}