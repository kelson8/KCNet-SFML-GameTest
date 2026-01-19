#include "game.h"
#include "defines.h"

#include "player.h"

#include <SFML/Audio.hpp>
#include "util/music_util.h"

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>
#include "menus/debug/imgui_menu.h"
#endif // _IMGUI_TEST

#include "enemy.h"

#include "util/mouse_util.h"

#include "util/text_handler.h"

// Copied values out of KCNet-SFML-GameTest

#ifdef GAME_TEST


// TODO Fix this to work, it's just a stripped down version of my game test project.
// I had to add the extra values in the constructor to get rid of the errors.

// I got this working with a window manager in window_manager.cpp/.h

// Constructors

/// <summary>
/// Initialize variables, the window, and enemies
/// </summary>
//Game::Game()
Game::Game() : 
	endGame(false), 
	endScreen(false),
	windowInitialized(false)
{
	// Init game variables, music, and the window.
	this->initVariables();
	this->initMusic();
	this->initWindow();

	//this->initEnemies();
}

Game::~Game()
{
	//delete this->window;
}

const bool Game::getWindowInitialized() const
{
	return windowInitialized;
}

/// <summary>
/// Set all the game variables up, enemy spawn timer, max enemies, and enemy speed so far.
/// 
/// Hmm, i've never really initialized variables like this in C++.
/// Now I somewhat know how this works.
/// </summary>
void Game::initVariables()
{
	Defines defines = Defines();

	//this->window = nullptr;

	// Game logic
	// Set the endgame status
	this->endGame = false;

	// Set the endScreen status
	this->endScreen = false;

	// Set the default lives
	//this->default_lives = 3;

	//this->points = 0;
	//this->lives = 0; // Not in use
	//if (fastEnemies)
	//{
	//	this->enemySpawnTimerMax = 1.0f;
	//}
	//else
	//{
	//	this->enemySpawnTimerMax = 20.0f;
	//}


	// Changing this value spawns in more enemies at once.
	// TODO Make a life system, if enough enemies get through it's game over.

	//
	//this->enemySpawnTimer = this->enemySpawnTimerMax;
	//this->maxEnemies = 10.0f;

	// Set the enemy speed
	//if (fastEnemiesFall)
	//{
	//	// Fast enemies
	//	this->enemySpeed = 25.0f;
	//}
	//else
	//{
	//	// Normal speed
	//	this->enemySpeed = 5.0f;
	//}

	//// Set mouse held to false
	//this->mouseHeld = false;

	//// Set health
	//this->health = defines.playerHealth;

}

/**
 * @brief Init the game window
 * Actually this is required in here, I just made a getter for the windowInitialized variable.
 */
void Game::initWindow()
{
	WindowManager& windowManager = WindowManager::getInstance();

	Defines defines = Defines();

	// Only allow one instance of the window, this works now.
	if (!windowInitialized)
	{
		windowManager.initWindow(defines.screenHeight, defines.screenWidth, defines.windowTitle);
		windowInitialized = true;
	}
}

/**
 * @brief Setup the music for the game.
 */
void Game::initMusic()
{
	Defines defines = Defines();
	MusicUtil& musicUtil = MusicUtil::getInstance();

	// Play the game music
	// TODO Move this into a different function
	// OH HELL, I accidentally put this in the loop at first lol, that was loud.
	// Play the music, add a toggle in defines.h
	if (defines.musicEnabled)
	{
		sf::Music* gameMusic = musicUtil.PlayMusic(defines.musicSound);

		if (gameMusic)
		{
			gameMusic->play();
			gameMusic->setLooping(true);
			gameMusic->setVolume(defines.musicVolume);
		}
	}
	//
}

// Accessors

/// <summary>
/// Check if the game is running
/// </summary>
/// <returns>True if the window is open</returns>
const bool Game::running() const
{
	WindowManager& windowManager = WindowManager::getInstance();
	//return this->window->isOpen();
	return windowManager.isOpen();
}

/// <summary>
/// Check the end game status
/// </summary>
/// <returns>True if the game has ended</returns>
const bool Game::getEndGame() const
{
	return this->endGame;
}

/**
 * @brief Set the end game status
 * @param newEndScreen New status of the end game.
 */
void Game::setEndGame(bool newEndGame)
{
	endGame = newEndGame;
}

/// <summary>
/// Get the game pause status
/// </summary>
/// <returns>If the game is paused or playing.</returns>
const bool Game::getPaused() const
{
	return this->isPaused;
}

void Game::setPaused(bool paused)
{
	this->isPaused = paused;
}

/// <summary>
/// Get the end screen status
/// </summary>
/// <returns>If the end screen is shown</returns>
const bool Game::getEndScreen() const
{
	return this->endScreen;
}

/**
 * @brief Set the end screen status
 * @param newEndScreen New status of the end screen.
 */
void Game::setEndScreen(bool newEndScreen)
{
	endScreen = newEndScreen;
}

/// <summary>
/// Updates the game events
/// TODO Fix in here, need to add PollEvents, updateMousePositions, and UpdateText functions.
/// </summary>
void Game::Update()
{
	WindowManager& windowManager = WindowManager::getInstance();
	Enemy& enemy = Enemy::getInstance();

	MouseUtil& mouseUtil = MouseUtil::getInstance();
	TextHandler& textHandler = TextHandler::getInstance();

	windowManager.pollEvents(); // Poll events regularly

#ifdef _IMGUI_TEST
	// Calculate delta time
	sf::Time deltaTime = deltaClock.restart(); // Gets the time since the last call

	ImGui::SFML::Update(windowManager.getWindow(), deltaTime);

#endif // _IMGUI_TEST

	// If the game hasn't ended and isn't paused, let everything update
	// I got the idea for pausing the game from here.
	// https://en.sfml-dev.org/forums/index.php?topic=28906.0

	// Update the texts on screen
	textHandler.Update();

	// Have the enemies display on screen
#ifdef ENEMIES_ENABLED
	if (!this->getPaused())
	{
		enemy.Update();
	}
	
#endif ENEMIES_ENABLED

	// Update the mouse positions
	mouseUtil.updateMousePositions(windowManager.getWindow());

	//sf::Time elapsed = clock.getElapsedTime();

	//std::cout << "Time elapsed: " << elapsed.asSeconds() << " seconds" << std::endl;
}

/// <summary>
/// 
// Clear old frame
// Render objects
// Display frame in window
// Renders the game objects
/// </summary>
void Game::Render()
{
	Player& player = Player::getInstance();
	Enemy& enemy = Enemy::getInstance();
	WindowManager& windowManager = WindowManager::getInstance();
	TextHandler& textHandler = TextHandler::getInstance();

#ifdef _IMGUI_TEST
	ImGuiMenu& imGuiMenu = ImGuiMenu::getInstance();
#endif

	// 
	// Use this to generate colors:
	// https://www.rapidtables.com/web/color/RGB_Color.html
	// Light blue
	// this->window->clear(sf::Color(102, 178, 255, 255)); // Clear old frame
	// Gray
	//this->window->clear(sf::Color(64, 64, 64, 255)); // Clear old frame
	windowManager.getWindow().clear(sf::Color(64, 64, 64, 255)); // Clear old frame

	// TODO Put a background in front of everything else, on the top of the screen.

	if (!this->getEndScreen()) {

		// If the game is not paused, run everything here.
		if (!this->getPaused())
		{
			player.Draw();

			textHandler.Render(windowManager.getWindow());

			// Set the end screen if the players lives go below 0.
			if (player.GetLives() == 0)
			{
				this->setEndScreen(true);
			}

			//this->RenderEnemies(*this->window);

#ifdef ENEMIES_ENABLED
			enemy.Render(windowManager.getWindow());
#endif // ENEMIES_ENABLED

			// Only run this for now if it is enabled
			// If i use this again, I moved the functions into the TextHandler class
			//if (renderTestItems)
			//{
			//	// Render the score test.
			//	this->renderScore();

			//	// Show test text on screen.
			//	this->RenderText(windowManager.getWindow());
			//	this->RenderText(*this->window);
			//}


			// Draw game objects
		}

	}
	// Show the end screen
	// This now works, I just can't press enter to start a new game.
	else
	{
		textHandler.RenderEndScreen();
	}


#ifdef _IMGUI_TEST

	if (imGuiMenu.GetStatus())
	{
		imGuiMenu.Draw();
	}

	// Use ImGui's render function here
	ImGui::SFML::Render(windowManager.getWindow());

#endif // _IMGUI_TEST

	// Draw your game
	//this->window->display(); // Tell app that window is done drawing.
	windowManager.getWindow().display();

}

void Game::Run()
{
	// Game loop
	// Check if game is running and is not ended.
	//while (game.running() && !game.getEndGame())
	while (running() && !getEndGame())
	{
		// Update
		Update();

		// Timer test
		// TODO Figure this out.
		//sf::Time passed = timer.restart();

		//std::cout << "Seconds: " << passed.asSeconds() << std::endl;

		// Render
		Render();
	}
}

#endif // GAME_TEST