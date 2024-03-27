#include "Game/includes/Game.h" // TODO: raplace it

#include <iostream>

class Rectangle;

int main()
{
	 try
	 {
		Game game({1280, 720}, "Lost In A Maze");
		game.setup();
		game.start();
	}
	catch (const std::runtime_error& error)
	{
		std::cout << "------------------------" << std::endl;
		std::cout << error.what() << std::endl;
		std::cout << "------------------------" << std::endl;
	}

	return 0;
};