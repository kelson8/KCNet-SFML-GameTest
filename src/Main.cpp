#include "Main.h"
#include "util/defines.h"

#include "Game.h"

// Killing enemies
// https://www.youtube.com/watch?v=Sil75qOxCW0&list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&index=8
// I got the linker and include files fixed for this in Debug and Release


#define _COMMAND_ARGS
#ifdef _COMMAND_ARGS
int main(int argc, const char * argv[])
#else
int main()
#endif //_COMMAND_ARGS
{
	Defines defines = Defines();

#ifdef _COMMAND_ARGS
	// Hmm I don't think these work in SFML.
	// TODO Figure out command line arguments for this.

	//switch (*argv[1])
	//{
	//	case "test":
	//	break;
	//}

	if (argv[1] == "test")
	{
		std::cout << "Running test mode.";
	}

	if (argv[1] == "chaos-mode")
	{
		std::cout << "Chaos mode activated... Now the enemy speeds are randomized using a random number generator.";
	}

#endif // _COMMAND_ARGS

	// About in console
	std::cout << "Welcome to: " << defines.windowTitle << std::endl;
	std::cout << "Version: " << defines.programVersion << std::endl;
	std::cout << "Author: " << defines.programAuthor << std::endl;
	std::cout << "License: " << defines.programLicense << std::endl;


	// Init srand for random.
	std::srand(static_cast<unsigned>(time(NULL)));

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