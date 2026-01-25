#pragma once
#pragma once
#include <iostream>

// This is a list of all the assets and sounds used, I don't want to have to modify the main file each time for these.

// I added toggles for the music and sound effects in here.

// I have also added the player default health in here.
// TODO Move that somewhere else sometime

// Toggle the ImGui test
// This now works.
// TODO Test moving this into CMake

// This should only disable it if NDEBUG is set, which is mostly set for release.
#ifndef NDEBUG
#define _IMGUI_TEST

// Enable extra logging, for now this is just the fmt logger that I have setup to log to console.
#define ENABLE_LOGGING
#endif

// Toggle the enemies rendering and updating here
#define ENEMIES_ENABLED

// Toggle the random enemy spawns here, this toggles if this is set the enemies spawn in random places.
// This is buggy so I have it disabled.
// If this is disabled, the enemies fall from the top to the bottom.
//#define ENEMY_RANDOM_SPAWNS

// If this is enabled, the player can take damage from the falling enemies.
// Can be toggled off for debugging
#define ENEMY_DAMAGE_PLAYER

// Toggle the Alpha/Beta mode for the text display and possibly other options in the future.
// So far this just changes the text that is displayed on the pause menu to either have an A or B in the version.
// Or just display without the suffix, such as 0.0.1 instead of 0.0.1a
#define KC_ALPHA_BETA

// Toggle the slider testing here, this isn't currently working.
// #define KC_SLIDER_TEST

class Defines {
public:
	static Defines& getInstance()
	{
		static Defines instance; // Guaranteed to be destroyed.
		return instance;
	}


	//Defines();

	// Player
	int playerHealth = 10;
	const static int defaultLives = 3;


	// Sound effects
	// TODO Implement the sound effects.

	// I updated these to their new values.
	// Sounds
	const char* pewSound;
	const char* popSound;
	const char* winSound;

	const char* shipHitSound;

	// Enable/disable sound effects
	bool soundEffectsEnabled;
	const char* enemyHitSound;

	// Music
	// Turn the music on/off
	bool musicEnabled;
	const char* musicSound;
	// TODO Move into Ini
	float musicVolume = 50.0f;


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

	const static std::string gameName;

	// Logger info
	const static std::string loggerPrefix;
	const static std::string logFileName;

	// Config
	static const char* iniFile;

	// Test
	// Hmm, I didn't know I could make these inline.
	//inline const static std::string testString = "";
	//

	// The frame rate can be changed here if needed.
	unsigned int gameFramerate = 60;
	bool vsyncEnabled = true;

	// Screen size
	// SFML3 requires unsigned int
	//const int screenWidth = 800;
	//const int screenHeight = 800;
	const unsigned int screenWidth = 800u;
	const unsigned int screenHeight = 800u;
	
private:
	// Constructors / Destructors
	Defines();
	//~Defines();
};