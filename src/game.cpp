#include "game.h"
#include "defines.h"

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
	endScreenText(font)
{
	this->initVariables();

	// Setup fonts and text
	this->initFonts();
	this->initText();

	// Only allow one instance of the window, this works now.
	if (!windowInitialized)
	{
		this->windowManager.initWindow(1920, 1080, "Game Title");
		windowInitialized = true;
	}

	//this->initEnemies();
}

Game::~Game()
{
	//delete this->window;
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

/// <summary>
/// Setup the game text.
/// </summary>
void Game::initText()
{
	// Setup the font
	this->scoreText.setFont(this->font);

	// // Set the character size, fill color and default string
	this->scoreText.setCharacterSize(24);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setString("NONE");

	// Setup the health text

	// Setup the font
	this->healthText.setFont(this->font);

	// Set the Y to be lower then the scoreText, so it doesn't overlap.
	this->healthText.setPosition(sf::Vector2f(0.0f, 30.0f));

	// Set the character size, fill color and default string
	this->healthText.setCharacterSize(24);
	this->healthText.setFillColor(sf::Color::White);
	this->healthText.setString("NONE");

	// Setup the end screen text
	this->endScreenText.setFont(this->font);
	//this->endScreenText.setPosition(40, 40);
	this->endScreenText.setPosition(sf::Vector2f(40, 40));
	this->endScreenText.setCharacterSize(48);
}

/// <summary>
/// Show the game end screen as a test.
/// This idea came from the open source Asteroids project
/// https://github.com/Anmfishe/Asteroids-SFML-CPP
/// </summary>
void Game::renderEndScreen()
{
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
	
	//MouseUtil mouseUtil = MouseUtil();
	//Enemy enemy = Enemy();

	windowManager.pollEvents(); // Poll events regularly

	// If the game hasn't ended and isn't paused, let everything update
	// I got the idea for pausing the game from here.
	// https://en.sfml-dev.org/forums/index.php?topic=28906.0

	//if (!this->endGame && !this->getPaused() && !this->getEndScreen())
	//{
	//	this->updateMousePositions();

	//	// Update the game text
	//	this->UpdateText();

	//	//this->updateEnemies();
	//}

	// Show the end screen if the health goes below 0
	//if (this->health <= 0)
	//{
	//	// This can close the window.
	//	//this->endGame = true;
	//	this->endScreen = true;
	//}



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

	//Enemy enemy = Enemy();

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

		//this->RenderEnemies(*this->window);

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

	// Draw your game
	//this->window->display(); // Tell app that window is done drawing.
	windowManager.getWindow().display();

}

#endif // GAME_TEST