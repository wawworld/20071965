#include "Snake_Game.h"

void main()
{
	Snake_Game* snake_game = new Snake_Game();
	
	snake_game->Run();

	snake_game->~Snake_Game();
}