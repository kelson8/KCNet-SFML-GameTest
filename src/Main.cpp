#include "Main.h"
#include "util/defines.h"

#include "Game.h"

// Enemy & Mouse positions
// https://www.youtube.com/watch?v=LnMO84T7myM&list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&index=6
// I got the linker and include files fixed for this in Debug and Release

int main()
{
	Defines defines = Defines();

	// About in console
	std::cout << "Welcome to: " << defines.windowTitle << std::endl;
	std::cout << "Version: " << defines.programVersion << std::endl;

	// Init Game engine
	Game game;

	// Game loop
	while (game.running())
	{
		// Update
		game.Update();

		// Render
		game.Render();
	}

	// End of application


}