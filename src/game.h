#pragma once
#include <SFML/Graphics.hpp>

#include "defines.h"

#include "window_manager.h"

#ifdef GAME_TEST

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

	const bool getWindowInitialized() const;

	//const sf::RenderWindow* getWindow() const;

	void setEndGame(bool newEndGame);
	void setEndScreen(bool newEndScreen);

#ifdef _IMGUI_TEST
	const float GetLivesTextPosX() const;
	const float GetLivesTextPosY() const;

	void SetLivesTextPos(float livesPosX, float livesPosY);
#endif

private:
	// Constructors / Destructors
	Game();
	~Game();

	// Private variables
	void initFonts();
	void initVariables();
	void initText();
	void initMusic();
	void initWindow();

	void RenderText(sf::RenderTarget& target);
	void UpdateText();
	void renderEndScreen();

	// Couldn't get this working in SFML3
	//sf::VideoMode videoMode;
	//sf::Event event;

	// Mouse positions

	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// Resources
	sf::Font font;

	// Text
	sf::Text scoreText;
	sf::Text healthText;
	sf::Text livesText;
	sf::Text endScreenText;

	// New variables
	sf::Clock deltaClock;

	float scoreTextPosX;
	float scoreTextPosY;

	float healthTextPosX;
	float healthTextPosY;

	float livesTextPosX;
	float livesTextPosY;

	float endScreenTextPosX;
	float endScreenTextPosY;
	//

	// Game logic

	// Check if the window has been initialized
	bool windowInitialized;

	// Check if the game is paused
	bool isPaused;

	// Check if the game has ended
	bool endGame;

	// Check if the end screen is being shown
	bool endScreen;

	//void spawnEnemy();


	//void PollEvents();
	//void updateMousePositions();

	//void updateEnemies();

	// TODO Move into TextFunctions.cpp
	//void UpdateText();

	//void RenderText(sf::RenderTarget& target);

	//void RenderEnemies(sf::RenderTarget& target);

	// Reset the enemy positions, used for when I reset the game.
	//void resetEnemies();
};

#endif // GAME_TEST