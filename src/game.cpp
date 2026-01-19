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
	windowInitialized(false),
	scoreText(font),
	healthText(font),
	livesText(font),
	endScreenText(font)
{
	this->initVariables();

	// Setup fonts and text
	this->initFonts();
	this->initText();
	this->initMusic();
	
	this->initWindow();

	//this->initEnemies();
}

Game::~Game()
{
	//delete this->window;
}

#ifdef _IMGUI_TEST
// Debugging for moving the text display on screen
const float Game::GetLivesTextPosX() const
{
	return this->livesTextPosX;
}

const float Game::GetLivesTextPosY() const
{
	return this->livesTextPosY;
}

void Game::SetLivesTextPos(float livesPosX, float livesPosY)
{
	this->livesTextPosX = livesPosX;
	this->livesTextPosY = livesPosY;
}


#endif

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

	// TODO Move into player class
	scoreTextPosX = 0.0f;
	scoreTextPosY = 0.0f;

	healthTextPosX = 0.0f;
	healthTextPosY = 30.0f;

	livesTextPosX = 0.0f;
	livesTextPosY = 60.0f;

	endScreenTextPosX = 40.0f;
	endScreenTextPosY = 40.0f;
	//

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

/// <summary>
/// Setup the fonts.
/// </summary>
void Game::initFonts()
{
	Defines defines = Defines();

	// If the font failed to load
	//if (!this->font.loadFromFile(defines.fontFile))
	if (!this->font.openFromFile(defines.fontFile))
	{
		std::cout << "Error, could not load font " << defines.fontFile << std::endl;
	}
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

/// <summary>
/// Setup the game text.
/// </summary>
void Game::initText()
{
	//----
	// Score
	//----
	// Setup the font
	this->scoreText.setFont(this->font);

	// // Set the character size, fill color and default string
	this->scoreText.setCharacterSize(24);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setString("NONE");

	//----
	// Health
	//----
	// Setup the font
	this->healthText.setFont(this->font);

	// Set the Y to be lower then the scoreText, so it doesn't overlap.
	this->healthText.setPosition(sf::Vector2f(0.0f, 30.0f));

	// Set the character size, fill color and default string
	this->healthText.setCharacterSize(24);
	this->healthText.setFillColor(sf::Color::White);
	this->healthText.setString("NONE");

	//----
	// Lives
	//----
	this->livesText.setFont(this->font);

	// Set the Y to be lower then the the other vaules, so it doesn't overlap.
	//this->livesText.setPosition(sf::Vector2f(0.0f, 35.0f));
	this->livesText.setPosition(sf::Vector2f(livesTextPosX, livesTextPosY));

	// Set the character size, fill color and default string
	this->livesText.setCharacterSize(24);
	this->livesText.setFillColor(sf::Color::White);
	this->livesText.setString("NONE");


	//----
	// End screen
	//----
	this->endScreenText.setFont(this->font);
	//this->endScreenText.setPosition(40, 40);
	this->endScreenText.setPosition(sf::Vector2f(40, 40));
	this->endScreenText.setCharacterSize(48);
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

/**
 * @brief Update the game text
 */
void Game::UpdateText()
{
	Player& player = Player::getInstance();
	// This is kind of like cout, can add floats, ints and everything else to it.
	std::stringstream points_ss;
	//std::stringstream health_ss;
	std::stringstream lives_ss;

	//points_ss << "Points: " << this->points;
	points_ss << "Points: " << player.GetPoints();
	//health_ss << "Health: " << player.getHealth();
	lives_ss << "Lives: " << player.GetLives();

	this->scoreText.setString(points_ss.str());
	//this->healthText.setString(health_ss.str());
	this->livesText.setString(lives_ss.str());
}

/**
 * @brief Render the score, health, and more in the future.
 * @param target
 */
void Game::RenderText(sf::RenderTarget& target)
{
	// Draw the score text
	target.draw(this->scoreText);

	// Draw the health text
	//target.draw(this->healthText);

	// Draw the lives text
	target.draw(this->livesText);
#ifdef _IMGUI_TEST
	// This is required for changing the position of the displays.
	this->livesText.setPosition(sf::Vector2f(livesTextPosX, livesTextPosY));
#endif
}

/// <summary>
/// Show the game end screen as a test.
/// This idea came from the open source Asteroids project
/// https://github.com/Anmfishe/Asteroids-SFML-CPP
/// </summary>
void Game::renderEndScreen()
{
	WindowManager& windowManager = WindowManager::getInstance();
	//this->endScreenText.setString("Your score was " + std::to_string(this->points)
	this->endScreenText.setString("Your score was ... \nPress enter to play again");

	// Draw the text to the window.
	windowManager.getWindow().draw(endScreenText);
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
	this->UpdateText();

	// Have the enemies display on screen
#ifdef ENEMIES_ENABLED
	enemy.Update();
#endif ENEMIES_ENABLED

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

#ifdef _IMGUI_TEST
	ImGuiMenu& imGuiMenu = ImGuiMenu::getInstance();
#endif

	//Enemy enemy = Enemy();

	//if (Game::getInstance().getWindowInitialized())
		//player.Draw();

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
		player.Draw();

		this->RenderText(windowManager.getWindow());

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
	// Show the end screen
	// This now works, I just can't press enter to start a new game.
	else {
		//window->draw(endScreenText);
		this->renderEndScreen();
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