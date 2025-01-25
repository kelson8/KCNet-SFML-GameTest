#include "Main.h"
#include "util/defines.h"

#include "Game.h"

// Enemy & Mouse positions
// https://www.youtube.com/watch?v=Y4fbvFjtVig&list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&index=7
// I got the linker and include files fixed for this in Debug and Release

int main()
{
	Defines defines = Defines();

	// About in console
	std::cout << "Welcome to: " << defines.windowTitle << std::endl;
	std::cout << "Version: " << defines.programVersion << std::endl;
	std::cout << "Author: " << defines.programAuthor << std::endl;
	std::cout << "License: " << defines.programLicense << std::endl;

	// Init Game engine
	Game game;

	// Timer test
	//sf::Clock timer;

	// Game loop
	while (game.running())
	{
		// Update
		game.Update();

		// Timer test
		// TODO Figure this out.
		//sf::Time passed = timer.restart();

		//std::cout << "Seconds: " << passed.asSeconds() << std::endl;

		// Render
		game.Render();
	}

	// End of application


}