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
#include "util/timers.h"

// Copied values out of KCNet-SFML-GameTest

// TODO Fix this to work, it's just a stripped down version of my game test project.
// I had to add the extra values in the constructor to get rid of the errors.

// I got this working with a window manager in window_manager.cpp/.h

// Constructors

/**
 * @brief Initialize variables, the music, and the window.
 */
Game::Game() : 
	endGame(false), 
	m_EndScreen(false),
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
	
}

/**
 * @brief Check if the window is initialized.
 * @return If the window is initialized.
 */
const bool Game::getWindowInitialized() const
{
	return windowInitialized;
}

/**
 * @brief Setup the end game status, and the end screen status
 * Sets these values to false.
 */
void Game::initVariables()
{
	Defines defines = Defines::getInstance();

	// Game logic
	// Set the endgame status
	this->endGame = false;

	// Set the endScreen status
	this->m_EndScreen = false;

	m_CurrentRound = 1;

	// Set mouse held to false
	// TODO Make into function in mouse_util.cpp/.h
	//this->mouseHeld = false;
}

/**
 * @brief Init the game window
 * Actually this is required in here, I just made a getter for the windowInitialized variable.
 */
void Game::initWindow()
{
	WindowManager& windowManager = WindowManager::getInstance();

	Defines defines = Defines::getInstance();

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
	Defines defines = Defines::getInstance();
	MusicUtil& musicUtil = MusicUtil::getInstance();

	// Play the game music
	// TODO Move this into a different function
	// OH HELL, I accidentally put this in the loop at first lol, that was loud.
	// Play the music, add a toggle in defines.h
	if (defines.musicEnabled)
	{
		sf::Music* gameMusic = musicUtil.PlayMusic(defines.musicSound);
		//std::unique_ptr<sf::Music> gameMusic = musicUtil.PlayMusic(defines.musicSound);

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

/**
 * @brief Check if the game is running
 * @return True if the window is open
 */
const bool Game::running() const
{
	WindowManager& windowManager = WindowManager::getInstance();
	//return this->window->isOpen();
	return windowManager.isOpen();
}

/**
 * @brief Check the end game status
 * @return True if the game has ended
 */
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

/**
 * @brief Get the game pause status
 * @return If the game is paused or playing.
 */
const bool Game::getPaused() const
{
	return this->isPaused;
}

/**
 * @brief Set the game pause status
 * @param paused The new pause status
 */
void Game::setPaused(bool paused)
{
	this->isPaused = paused;
}

/**
 * @brief Get the end screen status
 * @return If the end screen is shown
 */
const bool Game::getEndScreen() const
{
	return this->m_EndScreen;
}

/**
 * @brief Set the end screen status
 * @param newEndScreen New status of the end screen.
 */
void Game::setEndScreen(bool newEndScreen)
{
	m_EndScreen = newEndScreen;
}

/**
 * @brief This is unused, I may setup this later, I currently have the Player::Respawn function.
 */
//void Game::Restart()
//{
//
//}

/**
 * @brief So far this just resets the enemy positions, I may make it do more later.
 */
void Game::ResetEnemies()
{
	Enemy::getInstance().Reset();
}

/**
 * @brief Set the games current round
 * @param newRound The new round to set to
 * 
 * TODO Setup round system to change rounds every 30 seconds.
 * Make enemies faster depending on which round is set.
 */
void Game::SetRound(int newRound)
{
	m_CurrentRound = newRound;
}

/**
 * @brief Get the games current round
 * @return The current round the game is on.
 */
int Game::GetRound() const
{
	return m_CurrentRound;
}

/**
 * @brief Updates the game events
 * 
 * Update poll events, and delta time.
 * 
 * Update ImGui if enabled.
 * 
 * Update the text handler, and enemies.
 * 
 * Update the Mouse Util, which updates the mouse positions stored for debugging and use later.
 */
void Game::Update()
{
	WindowManager& windowManager = WindowManager::getInstance();
	Enemy& enemy = Enemy::getInstance();

	MouseUtil& mouseUtil = MouseUtil::getInstance();
	TextHandler& textHandler = TextHandler::getInstance();

	windowManager.pollEvents(); // Poll events regularly

	// Calculate delta time
	deltaTime = deltaClock.restart(); // Gets the time since the last call

#ifdef _IMGUI_TEST


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

/**
 * @brief Clear the old frame, render objects, display frame in window, and render game objects.
 */
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
		// Show the pause screen
		else 
		{
			textHandler.RenderPauseScreen(windowManager.getWindow());
		}

	}
	// Show the end screen
	else
	{
		textHandler.RenderEndScreen();
	}


#ifdef _IMGUI_TEST

	// Draw the ImGui menu if it is active.
	if (imGuiMenu.GetStatus())
	{
		imGuiMenu.Draw();
	}

	// Use ImGui's render function here
	ImGui::SFML::Render(windowManager.getWindow());

#endif // _IMGUI_TEST

	// Draw your game
	// Tell app that window is done drawing.
	windowManager.getWindow().display();

}

/**
 * @brief Main game run loop, this is running in main.cpp.
 */
void Game::Run()
{
	Timers& timers = Timers::getInstance();
	// Game loop
	// Check if game is running and is not ended.
	while (running() && !getEndGame())
	{
		// Update
		Update();

		// Toggle the Main timer here for keeping track of how long the game has been opened.
		// Logs total execution time to the console if enabled.
		timers.TimerLoop();

		// Update the wait timer when it is active
		//timers.TimerWaitLoop();

		// Update the timer to keep track of the score.
		// Gets reset when the player runs out of lives.
		timers.ScoreTimer();
		
		// Update the current round timer
		timers.RoundTimerLoop();

		// Render
		Render();
	}
}
