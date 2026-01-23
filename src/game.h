#pragma once
#include <SFML/Graphics.hpp>

#include "defines.h"

#include "window_manager.h"

#include "util/button_util.h"

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

	const bool isPlaying() const;

	void setPaused(bool paused);



	const bool getWindowInitialized() const;

	// Buttons
	//const bool GetButtonPositions() const;
	//void SetButtonPositions(ButtonPositions buttonPosition, sf::Vector2f position);
	void SetButtonPositions(ButtonPositions buttonPosition, sf::Vector2f position, sf::Vector2f size);

	void setEndGame(bool newEndGame);
	void setEndScreen(bool newEndScreen);
	void Restart();
	void ResetEnemies();

	void SetRound(int newRound);
	int GetRound() const;


private:
	// Constructors / Destructors
	Game();
	~Game();

	// Private variables
	void initVariables();
	void initMusic();
	void initWindow();

	void RenderMainScreen();

	// Buttons
		//ButtonUtil button1 = ButtonUtil(sf::Vector2f(100.0f, 100.0f), sf::Vector2f(150.0f, 50.0f), sf::Color::Magenta);
	//ButtonUtil button2 = ButtonUtil(sf::Vector2f(200.0f, 200.0f), sf::Vector2f(200.0f, 200.0f), sf::Color::Magenta);
	ButtonUtil button1;
	ButtonUtil button2;

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
	bool m_EndScreen;

	// The current round for the game
	int m_CurrentRound;

	// The starting round for the game
	int m_StartingRound;
};
