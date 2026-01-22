#pragma once
#include <SFML/Graphics.hpp>

#include "defines.h"

#include "window_manager.h"

class Game
{
public:

	static Game& getInstance()
	{
		static Game instance; // Guaranteed to be destroyed.
		return instance;
	}

	void Run();
	void Render();
	void Update();

	// Accessors
	const bool running() const;
	const bool getEndGame() const;
	const bool getPaused() const;
	const bool getEndScreen() const;

	void setPaused(bool paused);

	const bool getWindowInitialized() const;

	void setEndGame(bool newEndGame);
	void setEndScreen(bool newEndScreen);
	//void Restart();
	void ResetEnemies();


private:
	// Constructors / Destructors
	Game();
	~Game();

	// Private variables
	void initVariables();
	void initMusic();
	void initWindow();

	// Couldn't get this working in SFML3
	//sf::VideoMode videoMode;
	//sf::Event event;

	// Mouse positions

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	sf::Font font;

	// Delta clock for keeping track of time, required for ImGui.
	sf::Clock deltaClock;
	sf::Time deltaTime;

	// Clock for the game timer display.
	sf::Clock timerClock;

	// Game logic

	// Check if the window has been initialized
	bool windowInitialized;

	// Check if the game is paused
	bool isPaused;

	// Check if the game has ended
	bool endGame;

	// Check if the end screen is being shown
	bool endScreen;

	//void PollEvents();
	//void updateMousePositions();

	//void RenderEnemies(sf::RenderTarget& target);

	// Reset the enemy positions, used for when I reset the game.
	//void resetEnemies();
};
