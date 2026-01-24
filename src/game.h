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

	void ButtonHandler();

	// Buttons
	ButtonUtil m_MusicToggleButton;

	// Unused button, I will set this up later.
	ButtonUtil m_QuitButton;

	// Couldn't get this working in SFML3
	//sf::VideoMode videoMode;
	//sf::Event event;

	// Delta clock for keeping track of time, required for ImGui.
	sf::Clock m_DeltaClock;
	sf::Time m_DeltaTime;

	// Game logic

	// Check if the window has been initialized
	bool m_WindowInitialized;

	// Check if the game is paused
	bool m_IsPaused;

	// Check if the game has ended
	bool m_EndGame;

	// Check if the end screen is being shown
	bool m_EndScreen;

	// The current round for the game
	int m_CurrentRound;

	// The starting round for the game
	int m_StartingRound;

	bool m_MusicSetup;
};
