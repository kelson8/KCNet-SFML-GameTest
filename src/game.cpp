#include "game.h"
#include "defines.h"

#include "bullet.h"

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
	m_EndGame(false),
	m_EndScreen(false),
	m_WindowInitialized(false),
	// Buttons, TODO Move these elsewhere.
	m_MusicToggleButton(ButtonUtil(sf::Vector2f(133.0f, 32.0f), sf::Vector2f(542.0f, 247.0f), sf::Color::Black)),
	// TODO Make this into a quit button.
	m_QuitButton(ButtonUtil(sf::Vector2f(200.0f, 200.0f), sf::Vector2f(200.0f, 200.0f), sf::Color::Black))
{
	// Init game variables, music, and the window.
	initVariables();
	initMusic();
	initWindow();
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
	return m_WindowInitialized;
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
		m_MusicToggleButton.SetPosition(position);
		m_MusicToggleButton.SetSize(size);
		break;
	case ButtonPositions::PAUSE_MENU_TEST_BUTTON2_POSITION:
		m_QuitButton.SetPosition(position);
		m_QuitButton.SetSize(size);
		break;
	default:
		break;
	}
}

#endif // _IMGUI_TEST

/**
 * @brief Handle the game sprites
 * 
 * TODO Move this into a different file.
 * 
 * @param window
 * @param textureFile
 */ 
//void Game::SpriteHandler(sf::RenderWindow& window, std::string textureFile)
//sf::Sprite Game::SpriteHandler(sf::RenderWindow& window, std::string textureFile)
//{
//	//sf::Texture sprite(spriteFile);
//
//	sf::Texture texture;
//	// TODO Figure out what IntRect is
//	if (!texture.loadFromFile(textureFile, false, sf::IntRect({ 10, 10 }, { 32, 32 })))
//	{
//		fmt::println("An error occurred, texture couldn't be loaded!");
//		return;
//	}
//
//
//	//texture.setSmooth(true);
//	//texture.setRepeated(true);
//
//	sf::Sprite sprite(texture);
//	return sprite;
//
//	// Draw the sprite to the screen
//	//window.draw(sprite);
//}

/**
 * @brief Setup the end game status, and the end screen status
 * Sets these values to false.
 */
void Game::initVariables()
{
	Defines defines = Defines::getInstance();

	// Game logic
	// Set the endgame status
	m_EndGame = false;

	// Set the endScreen status
	m_EndScreen = false;

	m_CurrentRound = 1;
	// TODO Make a config option for this
	m_StartingRound = 1;

	// If the music init has run or not.
	m_MusicSetup = false;

	// Set mouse held to false
	// TODO Make into function in mouse_util.cpp/.h
	//mouseHeld = false;
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
	if (!m_WindowInitialized)
	{
		windowManager.initWindow(defines.screenHeight, defines.screenWidth, defines.windowTitle);
		m_WindowInitialized = true;
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
	return windowManager.isOpen();
}

/**
 * @brief Check the end game status
 * @return True if the game has ended
 */
const bool Game::getEndGame() const
{
	return m_EndGame;
}

/**
 * @brief Set the end game status
 * @param newEndScreen New status of the end game.
 */
void Game::setEndGame(bool newEndGame)
{
	m_EndGame = newEndGame;
}

/**
 * @brief Get the game pause status
 * @return If the game is paused or playing.
 */
const bool Game::getPaused() const
{
	return m_IsPaused;
}

/**
 * @brief Set the game pause status
 * @param paused The new pause status
 */
void Game::setPaused(bool paused)
{
	m_IsPaused = paused;
}

/**
 * @brief Get the end screen status
 * @return If the end screen is shown
 */
const bool Game::getEndScreen() const
{
	return m_EndScreen;
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
		m_MusicToggleButton.SetColor(sf::Color::Green);
		
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
		m_MusicToggleButton.SetColor(sf::Color::Red);
		// Stop the music.
		musicUtil.SetMusicInfo(false, true, false);
	}

	// This updates the button if it is clicked on
	if (m_MusicToggleButton.GetGlobalBounds().contains(mouseUtil.getMousePosView()) &&
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
	m_DeltaTime = m_DeltaClock.restart(); // Gets the time since the last call

#ifdef _IMGUI_TEST


	ImGui::SFML::Update(windowManager.getWindow(), m_DeltaTime);

#endif // _IMGUI_TEST

	// If the game hasn't ended and isn't paused, let everything update
	// I got the idea for pausing the game from here.
	// https://en.sfml-dev.org/forums/index.php?topic=28906.0

	// Update the texts on screen

	// In game
	textHandler.UpdatePlayingText();

	// Paused
	textHandler.UpdatePauseText();

	// Have the enemies display on screen
#ifdef ENEMIES_ENABLED
	if (!getPaused())
	{
		enemy.Update();
	}

#endif // ENEMIES_ENABLED

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
		setEndScreen(true);
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

	// TODO Make this into a variable elsewhere, I forgot about the window color being set here.
	// Use this to generate colors:
	// https://www.rapidtables.com/web/color/RGB_Color.html
	// Light blue
	// window->clear(sf::Color(102, 178, 255, 255)); // Clear old frame
	// Gray
	windowManager.getWindow().clear(sf::Color(64, 64, 64, 255)); // Clear old frame

	// TODO Put a background in front of everything else, on the top of the screen.

	if (!getEndScreen())
	{

		// Well I didn't mean to do this but it made a neat effect.
		// I accidentally placed this out here but the pause screen is now transparent if I leave it here.
		//RenderMainScreen();
		// If the game is not paused, run everything here.
		if (!getPaused())
		{
			RenderMainScreen();
		}
		// Show the pause screen
		else
		{
			//textHandler.RenderPauseScreen(windowManager.getWindow());
			textHandler.RenderPauseScreen(m_MusicToggleButton, m_QuitButton, windowManager.getWindow());
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
