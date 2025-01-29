#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

// Moved sfml into pch.h

#include "pch.h"

// TMX Parser
// TODO Fix this for sprites to be loaded in, such as maps created with the Tiled map editor.
// I should be able to do this eventually once I get the hang of this.
//#include "tmxparser/include/TmxColor.h"

// SFML TMX Loader
// https://github.com/fallahn/sfml-tmxloader
// TODO Fix these
// Re-include in project under include/sfml-tmxloader/include and include/sfml-tmxloader/src
//#include <tmx/MapLoader.hpp>
//#include <tmx/MapLayer.hpp>

// TMX Lite
// https://github.com/fallahn/tmxlite
//#include <tmxlite/TileLayer.hpp>

/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Game
{
private:
	// Variables

	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	//sf::Font gameFont;
	//sf::Text text;

	// Mouse positions

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	sf::Font font;

	// Text
	//sf::Text uiText;
	sf::Text scoreText;
	sf::Text healthText;
	sf::Text endScreenText;

	// Game logic

	// Check if the game is paused
	bool isPaused;
	
	// Check if the game has ended
	bool endGame;

	// Check if the end screen is being shown
	bool endScreen;

	// Player
	// Positive values only
	unsigned points;
	int lives;
	int health;
	int default_lives;

	// Enemy
#ifndef _MOVE_ENEMY_FILE
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	float enemySpeed; // The speed of the enemy
#endif //!_MOVE_ENEMY_FILE

	bool mouseHeld; // Check if the mouse is held down.

	// Game objects
	// TODO Switch to sprites
	//sf::Sprite
#ifndef _MOVE_ENEMY_FILE
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
#endif //!_MOVE_ENEMY_FILE

	// Private functions
	void initVariables();
	void initBackground();
	void initWindow();

#ifndef _MOVE_ENEMY_FILE
	void initEnemies();
#endif //!_MOVE_ENEMY_FILE

	// TODO Move into TextFunctions.cpp
	void initFonts();
	void initText();

	void renderScore();
	// Show the end screen.
	void renderEndScreen();
	//void renderText();

	void resetGame();
	
	//void playEnemySfx();
#ifdef _ENEMY_SOUNDS_TEST
	sf::SoundBuffer* playEnemySfx();
#endif //_ENEMY_SOUNDS_TEST

public:
	// Constructors / Destructors
	Game();
	~Game();

	// Accessors
	const bool running() const;
	const bool getEndGame() const;
	const bool getPaused() const;
	const bool getEndScreen() const;

	// TODO Figure out if I got this right.
	const sf::RenderWindow* getWindow() const;

	// Functions
#ifndef _MOVE_ENEMY_FILE
	void spawnEnemy();
#endif //!_MOVE_ENEMY_FILE

	// Music functions, moved into MusicUtil

	void PollEvents();
	void updateMousePositions();

#ifndef _MOVE_ENEMY_FILE
	void updateEnemies();
#endif //!_MOVE_ENEMY_FILE

	void Update();

	// TODO Move into TextFunctions.cpp
	void UpdateText();

	// Don't always have to render to the main window.
	void RenderText(sf::RenderTarget& target);

#ifndef _MOVE_ENEMY_FILE
	void RenderEnemies(sf::RenderTarget& target);

	// Reset the enemy positions, used for when I reset the game.
	void resetEnemies();
#endif //!_MOVE_ENEMY_FILE

	void Render();

	// Health test
	void setHealth(int newHealth);
	const int getHealth() const;
};

