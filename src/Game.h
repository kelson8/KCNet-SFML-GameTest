#pragma once

#include <iostream>
#include <vector>
#include <ctime>

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

	// Game logic
	int points;
	int lives;

	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	float enemySpeed; // The speed of the enemy

	// Game objects
	// TODO Switch to sprites
	//sf::Sprite
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	// Private functions
	void initVariables();
	void initBackground();
	void initWindow();
	void initEnemies();

	void renderScore();
	void renderText();
	
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

	// Functions
	void spawnEnemy();

	// Music functions, moved into MusicUtil

	void PollEvents();
	void updateMousePositions();
	void updateEnemies();

	void Update();

	void renderEnemies();
	void Render();
};

