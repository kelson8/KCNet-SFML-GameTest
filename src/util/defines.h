#pragma once
#include <iostream>

// This is a list of all the assets and sounds used, I don't want to have to modify the main file each time for these.

// Enable lives test in GameLogic
// I have it updating in the console output, it just doesn't display the end screen, or update the text at the bottom
// I'm getting close on figuring out how to move the lives into GameLogic with getters and setters.
//#define _TEST2

class Defines {
public:
	// Sounds
	const std::string pewSound = "src/resources/sounds/pew.wav";
	const std::string popSound = "src/resources/sounds/pop.wav";
	const std::string winSound = "src/resources/sounds/win.wav";

	const std::string shipHitSound = "src/resources/sounds/hit.wav";

	// Music
	const std::string musicSound = "src/resources/sounds/music/dreams.wav";

	const std::string fontFile = "src/fonts/font.TTF";


	// Ships
	const std::string shipImage = "src/resources/assets/ship.png";
	const std::string shipFireImage = "src/resources/assets/ship_fire.png";

	const std::string asteroidImage = "src/resources/assets/other/ROCK.png";



	// Game info
	const char* windowTitle = "KCNet-SFML-GameTest";
	// Version alpha 1.0.0
	// TODO Possibly place this elsewhere.
	const std::string programVersion = "a1.0.0";
	const std::string programAuthor = "kelson8";
	const std::string programLicense = "Licensed under the MIT License (c) kelson8 - KCNet";

	// The frame rate can be changed here if needed.
	unsigned int gameFramerate = 60;



	// Screen size
	const int screenWidth = 800;
	const int screenHeight = 800;

	

	//int lives;


};