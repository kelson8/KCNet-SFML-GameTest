#include "Main.h"
#include "util/defines.h"

#include "Game.h"
#include "util/MusicUtil.h"

// Enable command arguments test for this program.
#define _COMMAND_ARGS

// ImGui test from here added into game.cpp, it doesn't work yet:
// https://youtu.be/2YS5WJTeKpI



// TODO Fix this project to use pre compiled headers
// https://stackoverflow.com/questions/1552058/how-to-implement-precompiled-headers-into-your-project


// Fonts and Text
// https://www.youtube.com/watch?v=oDOgquwEf38&list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&index=10
// I got the linker and include files fixed for this in Debug and Release

#ifdef _COMMAND_ARGS
int main(int argc, const char * argv[])
#else
int main()
#endif //_COMMAND_ARGS
{
	Defines defines = Defines();
	MusicUtil musicUtil = MusicUtil();

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

	// Play the music, add a toggle in defines.h
	if (defines.musicEnabled)
	{
		sf::Music* gameMusic = musicUtil.PlayMusic(defines.musicSound);

		if (gameMusic)
		{
			gameMusic->play();
			gameMusic->setLoop(true);
			gameMusic->setVolume(defines.musicVolume);
		}
	}


	// Game loop
	// Check if game is running and is not ended.
	while (game.running() && !game.getEndGame())
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