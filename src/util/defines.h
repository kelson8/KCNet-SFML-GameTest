#pragma once
#include <iostream>

// This is a list of all the assets and sounds used, I don't want to have to modify the main file each time for these.

class Defines {
public:
	// I updated these to their new values.
	// Sounds
	const std::string pewSound = "resources/sounds/pew.wav";
	const std::string popSound = "resources/sounds/pop.wav";
	const std::string winSound = "resources/sounds/win.wav";

	const std::string shipHitSound = "resources/sounds/hit.wav";

	// Music
	//const std::string musicSound = "resources/sounds/music/dreams.wav";
	const std::string musicSound = "resources/sounds/music/space_dungeon_bpm100.ogg";
	float musicVolume = 50.0f;

	// Sound effects
	const std::string enemyHitSound = "resources/sounds/hit.wav";

	const std::string fontFile = "fonts/font.TTF";


	// Ships
	const std::string shipImage = "resources/assets/ship.png";
	const std::string shipFireImage = "resources/assets/ship_fire.png";

	const std::string asteroidImage = "resources/assets/other/ROCK.png";



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

};