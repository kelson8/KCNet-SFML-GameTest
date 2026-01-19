#pragma once
#pragma once
#include <iostream>

// This is a list of all the assets and sounds used, I don't want to have to modify the main file each time for these.

// I added toggles for the music and sound effects in here.

// I have also added the player default health in here.
// TODO Move that somewhere else sometime

// Toggle the ImGui test
// This now works.
#define _IMGUI_TEST

// Toggle the enemies rendering and updating here
#define ENEMIES_ENABLED

class Defines {
public:

	// Player
	int playerHealth = 10;
	const static int defaultLives = 3;

	// I updated these to their new values.
	// Sounds
	const std::string pewSound = "resources/sounds/pew.wav";
	const std::string popSound = "resources/sounds/pop.wav";
	const std::string winSound = "resources/sounds/win.wav";

	const std::string shipHitSound = "resources/sounds/hit.wav";

	// Music
	//const std::string musicSound = "resources/sounds/music/dreams.wav";
	// Turn the music on/off
	bool musicEnabled = true;
	const std::string musicSound = "resources/sounds/music/space_dungeon_bpm100.ogg";
	float musicVolume = 50.0f;

	// Sound effects
	// TODO Implement the sound effects.
	// Enable/disable sound effects
	bool soundEffectsEnabled = false;
	const std::string enemyHitSound = "resources/sounds/hit.wav";


	// TODO Setup fonts
	const std::string fontFile = "fonts/font.TTF";

	// TODO Setup assets
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
	bool vsyncEnabled = true;

	// Screen size
	// SFML3 requires unsigned int
	//const int screenWidth = 800;
	//const int screenHeight = 800;
	const unsigned int screenWidth = 800u;
	const unsigned int screenHeight = 800u;
	

};