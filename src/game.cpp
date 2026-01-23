#include "game.h"
#include "defines.h"

#include "player.h"

#include <fmt/core.h>

#include <SFML/Audio.hpp>
#include "util/music_util.h"

#include "util/button_util.h"

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
	windowInitialized(false),
	// Buttons, TODO Move these elsewhere.
	button1(ButtonUtil(sf::Vector2f(133.0f, 32.0f), sf::Vector2f(542.0f, 247.0f), sf::Color::Black)),
	button2(ButtonUtil(sf::Vector2f(200.0f, 200.0f), sf::Vector2f(200.0f, 200.0f), sf::Color::Black))
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

// 
#ifdef _IMGUI_TEST

/**
 * @brief Test for changing the button positions in ImGui
 *
 * This works for changing the button positions.
 *
 * @param button The ButtonPositions button to change position from the enum.
 * @param position The position to set the button to.
 * @param size The new size of the button.
 */
void Game::SetButtonPositions(ButtonPositions buttonPosition, sf::Vector2f position, sf::Vector2f size)
{
	switch (buttonPosition)
	{
	case ButtonPositions::PAUSE_MENU_TEST_BUTTON1_POSITION:
		button1.SetPosition(position);
		button1.SetSize(size);
		break;
	case ButtonPositions::PAUSE_MENU_TEST_BUTTON2_POSITION:
		button2.SetPosition(position);
		button2.SetSize(size);
		break;
	default:
		break;
	}
}

#endif // _IMGUI_TEST

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
	// TODO Make a config option for this
	m_StartingRound = 1;

	// If the music init has run or not.
	m_MusicSetup = false;

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
	// I accidentally put this in the loop at first lol, that was loud.
	// Play the music, add a toggle in defines.h.
	if (defines.musicEnabled && !m_MusicSetup && std::filesystem::exists(defines.musicSound))
	{
		sf::Music* gameMusic = musicUtil.PlayMusic(defines.musicSound);
		//std::unique_ptr<sf::Music> gameMusic = musicUtil.PlayMusic(defines.musicSound);

		if (gameMusic)
		{
			gameMusic->play();
			gameMusic->setLooping(true);
			gameMusic->setVolume(defines.musicVolume);
			m_MusicSetup = true;
		}
	}
	else
	{
		// TODO Fix this to only run once, it seems to always run in this loop.
		// Now this part spams the console.
		//fmt::println("Music not setup, file possibly doesn't exist.");
		// Music either disabled or not setup
		m_MusicSetup = false;
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
 * @brief Check if the game is currently being played.
 * @return If the game is not on the end screen, or if the game is paused.
 */
const bool Game::isPlaying() const
{
	if (!getEndScreen() && !getPaused())
		return true;

	return false;
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
 * @brief Restart the game
 *
 * This runs some restart functions for the buttons I will setup.
 */
void Game::Restart()
{
	// Respawn the player
	Player::getInstance().Respawn();
	// Reset the players score
	Timers::getInstance().SetScore(0);
	// Reset the round count.
	SetRound(m_StartingRound);

	// Reset the enemies
	Game::getInstance().ResetEnemies();

	// Reset the round timer
	Timers::getInstance().ResetRoundTimer();

	// Disable the pause menu if its active
	if (getPaused())
	{
		setPaused(false);
	}

	// Disable the end screen if it is active
	if (getEndScreen())
	{
		setEndScreen(false);
	}

	// The game should exit if this is set, but reset it just in case.
	if (getEndGame())
	{
		setEndGame(false);
	}
}

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
 * @brief Manage the buttons in the game
 * So far, this just has one pause button defined
 * 
 * TODO Make helper functions for these buttons
 */
void Game::ButtonHandler()
{
	MouseUtil& mouseUtil = MouseUtil::getInstance();
	Defines& defines = Defines::getInstance();
	Timers& timers = Timers::getInstance();
	MusicUtil& musicUtil = MusicUtil::getInstance();

	IniHandler iniHandler;

	//---------
	// Button handling
	//---------
	// This works for updating the button color if hovering over the button.
	//if(button1.GetGlobalBounds().contains(mouseUtil.getMousePosView()))

	// TODO Fix this to update the button text when the value changes, it isn't updating.

	// Update the button color if the music is enabled or not
	// TODO Make this update text under or beside of the button stating on/off instead of just the color.
	if (defines.musicEnabled)
	{
		button1.SetColor(sf::Color::Green);
		
		// Setup the music first.
		if (!m_MusicSetup)
		{
			//iniHandler.LoadIni();
			initMusic();
		}

		// Play the music and loop it.
		musicUtil.SetMusicInfo(true, false, true);
	}
	else
	{
		button1.SetColor(sf::Color::Red);
		// Stop the music.
		musicUtil.SetMusicInfo(false, true, false);
	}

	// This updates the button if it is clicked on
	if (button1.GetGlobalBounds().contains(mouseUtil.getMousePosView()) &&
		// Check if mouse button pressed
		sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

		//button1.SetColor(sf::Color::Blue);

		// Make sure this doesn't get spammed, add a second delay to it.
		if (timers.SecondPassed())
		{
			// Now this works for updating the music value in the INI.
			// Now to figure out how to reload the INI for these values in game.
			if (defines.musicEnabled)
			{
				iniHandler.SetBool("SoundToggles", "MusicEnabled", false, "#Enable/Disable music", true);
				defines.musicEnabled = false;
			}
			else
			{
				iniHandler.SetBool("SoundToggles", "MusicEnabled", true, "#Enable/Disable music", true);
				defines.musicEnabled = true;
			}
		}
	}
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
	Defines& defines = Defines::getInstance();
	Timers& timers = Timers::getInstance();

	IniHandler iniHandler;

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


	// Update the buttons in the game
	ButtonHandler();

	//sf::Time elapsed = clock.getElapsedTime();

	//std::cout << "Time elapsed: " << elapsed.asSeconds() << " seconds" << std::endl;
}

/**
 * @brief This renders the main game screen
 */
void Game::RenderMainScreen()
{
	Player& player = Player::getInstance();
	Enemy& enemy = Enemy::getInstance();
	WindowManager& windowManager = WindowManager::getInstance();
	TextHandler& textHandler = TextHandler::getInstance();

	// Draw the player
	player.Draw();

	// Render the texts for the main screen
	textHandler.Render(windowManager.getWindow());

	// Set the end screen if the players lives go below 0.
	if (player.GetLives() == 0)
	{
		this->setEndScreen(true);
	}

#ifdef ENEMIES_ENABLED
	enemy.Render(windowManager.getWindow());
#endif // ENEMIES_ENABLED
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

	if (!this->getEndScreen())
	{

		// Well I didn't mean to do this but it made a neat effect.
		// I accidentally placed this out here but the pause screen is now transparent if I leave it here.
		//RenderMainScreen();
		// If the game is not paused, run everything here.
		if (!this->getPaused())
		{
			RenderMainScreen();
		}
		// Show the pause screen
		else
		{
			//textHandler.RenderPauseScreen(windowManager.getWindow());
			textHandler.RenderPauseScreen(button1, button2, windowManager.getWindow());
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
