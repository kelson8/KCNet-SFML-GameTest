#include "Game.h"
#include "util/MouseUtil.h"

#include "Enemy.h"

#include "WindowManager.h"

// Enable ImGui test
// TODO Fix this to work.
//#define _IMGUI_TEST

#ifdef _IMGUI_TEST
// Imgui test
#include "imgui.h"
#include "imgui-SFML.h"

#endif //_IMGUI_TEST

// Enable certain test features.






// Enable the enemy sound test, play sounds when the enemies are clicked on.
// I need to work on this some more to fix it
//#define _ENEMY_SOUNDS_TEST

// Booleans
// TODO Eventually add these to a game menu once I figure that out.
// Enable faster enemies spawning
bool fastEnemies = false;
// Make the enemies go down faster.
bool fastEnemiesFall = false;

// Show the score test, and some test text with a font.
bool renderTestItems = true;


// Enable my mouse pos define below.
// TODO Add a timer to this, delay it by like 1 second instead of letting it run super fast.
//#define _SHOW_MOUSE_POS

// Private functions


/// <summary>
/// Set all the game variables up, enemy spawn timer, max enemies, and enemy speed so far.
/// 
/// Hmm, i've never really initialized variables like this in C++.
/// Now I somewhat know how this works.
/// </summary>
void Game::initVariables()
{
	Defines defines = Defines();

#ifndef _MOVE_WINDOW_FILE
	this->window = nullptr;
#endif //_MOVE_WINDOW_FILE

	// Game logic
	// Set the endgame status
	this->endGame = false;

	// Set the endScreen status
	this->endScreen = false;

	// Set the default lives
	this->default_lives = 3;
	
	this->points = 0;
	this->lives = 0; // Not in use
	if (fastEnemies)
	{
		this->enemySpawnTimerMax = 1.0f;
	}
	else 
	{
		this->enemySpawnTimerMax = 10.0f;
	}
	
	
	// Changing this value spawns in more enemies at once.
	// TODO Make a life system, if enough enemies get through it's game over.

	//
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 20.0f;
	
	// Set the enemy speed
	if (fastEnemiesFall)
	{
		// Fast enemies
		this->enemySpeed = 25.0f;
	}
	else
	{
		// Normal speed
		this->enemySpeed = 5.0f;
	}

	// Set mouse held to false
	this->mouseHeld = false;

	// Set health
	this->health = defines.playerHealth;

}

/// <summary>
/// Init the enemies
/// </summary>
#ifndef _MOVE_ENEMY_FILE
void Game::initEnemies()
{
	Defines defines = Defines();

	// Set the position, size and scale
	this->enemy.setPosition(sf::Vector2f(10.0f, 10.0f));
	this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));

	// Set the fill color, outline color and outline thickness.
	this->enemy.setFillColor(sf::Color::Green);
	//this->enemy.setOutlineColor(sf::Color::Yellow);
	//this->enemy.setOutlineThickness(1.0f);
}
#endif //!_MOVE_ENEMY_FILE

/// <summary>
/// TODO Setup a background for this.
/// </summary>
void Game::initBackground() 
{
	Defines defines = Defines();

	// Grab background from defines file.

	// Set the background.

}

/// <summary>
/// Create the window
/// </summary>
#ifndef _MOVE_WINDOW_FILE
void Game::initWindow()
{
	Defines defines = Defines();

	this->videoMode.height = defines.screenHeight;
	this->videoMode.width = defines.screenWidth;

	//this->videoMode.getDesktopMode();

	this->window = new sf::RenderWindow(this->videoMode, defines.windowTitle, sf::Style::Titlebar | sf::Style::Close);

	// Setup ImGui window
#ifdef _IMGUI_TEST
	ImGui::SFML::Init(*this->window);
#endif //_IMGUI_TEST

	this->window->setFramerateLimit(defines.gameFramerate);
}
#endif //!_MOVE_WINDOW_FILE

/// <summary>
/// Setup the fonts.
/// </summary>
void Game::initFonts()
{
	Defines defines = Defines();

	// If the font failed to load
	if (!this->font.loadFromFile(defines.fontFile))
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
	this->endScreenText.setPosition(40, 40);
	this->endScreenText.setCharacterSize(48);
}

// Constructors

/// <summary>
/// Initialize variables, the window, and enemies
/// </summary>
Game::Game()
{
	
#ifdef _MOVE_WINDOW_FILE
	WindowManager windowManager = WindowManager();
#endif //_MOVE_WINDOW_FILE

	this->initVariables();

#ifndef _MOVE_WINDOW_FILE
	this->initWindow();
#else
	windowManager.initWindow();
#endif //_MOVE_WINDOW_FILE

	// Setup fonts and text
	this->initFonts();
	this->initText();
	
	this->initEnemies();
}

Game::~Game()
{
	// Delete the window
#ifndef _MOVE_WINDOW_FILE
	delete this->window;
#endif //_MOVE_WINDOW_FILE
}

// Accessors

/// <summary>
/// Check if the game is running
/// </summary>
/// <returns>True if the window is open</returns>
#ifndef _MOVE_WINDOW_FILE
const bool Game::running() const
{
	return this->window->isOpen();
}
#endif //_MOVE_WINDOW_FILE

/// <summary>
/// Check the end game status
/// </summary>
/// <returns>True if the game has ended</returns>
const bool Game::getEndGame() const
{
	return this->endGame;
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

/// <summary>
/// Get the current window, this should allow me to use these functions in other classes.
/// </summary>
/// <returns></returns>
const sf::RenderWindow* Game::getWindow() const
{
	return this->window;
}

/// <summary>
/// Set the player health
/// </summary>
/// <param name="newHealth"></param>
void Game::setHealth(int newHealth) 
{
	this->health = newHealth;
}

/// <summary>
/// Get the players health
/// </summary>
/// <returns></returns>
const int Game::getHealth() const
{
	return this->health;
}

// Functions

/// <summary>
/// Spawn the enemies and set their colors and positions.
/// Sets a random position
/// Sets a random color
/// Adds enemy to the vector.
/// </summary>
#ifndef _MOVE_ENEMY_FILE
void Game::spawnEnemy()
{
	// Randomizing between zero and the window size for the X
	// Using static cast, safely turning the value into a float, the random function only takes an int so it has to be
	// converted to an int first then randomize it.
	this->enemy.setPosition(
		static_cast<float> (rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.0f
		//static_cast<float> (rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
	);

	this->enemy.setFillColor(sf::Color::Green);

	// Spawn the enemy
	this->enemies.push_back(this->enemy);

	// Remove enemies at the end of the screen.
}
#endif //!_MOVE_ENEMY_FILE

//void Game::playEnemySfx()

#ifdef _ENEMY_SOUNDS_TEST
sf::SoundBuffer* Game::playEnemySfx()
{
	Defines defines = Defines();

	sf::SoundBuffer* buffer = &sf::SoundBuffer();
	if (!buffer->loadFromFile(defines.enemyHitSound))
	{
		std::cerr << "Could not load the enemy sound" << std::endl;
		delete buffer;
		return nullptr; // Handle error
	}

	return buffer;

	// Play the sound
	//sf::Sound sound(buffer);
	//sound.play();
}
#endif //_ENEMY_SOUNDS_TEST



/// <summary>
///  Update the enemy spawn timer and spawns enemies.
///  When the total amount of enemies is smaller then the maximum.
///  Moves the enemies downwards.
///  Removes the enemies at the edge of the screen.
/// </summary>
#ifndef _MOVE_ENEMY_FILE
void Game::updateEnemies()
{

	// TODO Fix this
#ifdef _ENEMY_SOUNDS_TEST
	// Play sound effect
	sf::Sound enemySfx(*this->playEnemySfx());
	enemySfx.play();
#endif //_ENEMY_SOUNDS_TEST

	Defines defines = Defines();
	MouseUtil mouseUtil = MouseUtil();
	Enemy enemy = Enemy();

	// Updating the timer.
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			// Spawn the enemy and reset the timer.
			// TODO Move this into Enemy.cpp, it flickers the screen too.
#ifndef _MOVE_ENEMY_FILE
			this->spawnEnemy();
#else

			enemy.spawnEnemy();
#endif //!_MOVE_ENEMY_FILE
			this->enemySpawnTimer = 0.0f;
		}
		else
		{
			this->enemySpawnTimer += 1.0f;
		}
	}

	// Moving and updating the enemies, check if they are below the screen
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		// Change the speed by changing the offsetY
		this->enemies[i].move(0.0f, enemySpeed);

		// Delete the enemy if they are past the bottom of the screen.
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << std::endl;
		}
	}

	// Remove the enemies
	// Check if clicked upon

	// Moving this into here should make it to where I can delay the mouse clicks.
	// Changing to this should optimize the code a bit
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

		// Check if the mouse is not held
		// This doesn't work, the mouse stays held in even with this.
		// TODO Fix this.
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;

			// If !deleted
			//for (size_t i = 0; i < this->enemies.size() && !deleted; i++)
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				// Only run if the mouse is clicked
#ifdef _MOVE_MOUSE_UTIL
				if (this->enemies[i].getGlobalBounds().contains(mouseUtil.getMousePosView()))
#else
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
#endif //_MOVE_MOUSE_UTIL
				{
					// Delete the enemy
					// Settings deleted to true cancels the loop.
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					// Gain points
					this->points += 1;
					std::cout << "Points: " << this->points << std::endl;
				}
			}
		} 
		// Set mouseHeld back to false.
		else 
		{ 
			this->mouseHeld = false;
		}
	}
}
#endif //!_MOVE_ENEMY_FILE

/// <summary>
/// Render the text
/// </summary>
void Game::RenderText(sf::RenderTarget& target)
{
	// Draw the text
	// Draw the score text
	target.draw(this->scoreText);

	target.draw(this->healthText);
}


/// <summary>
/// Render the enemies
/// </summary>
#ifndef _MOVE_ENEMY_FILE
void Game::RenderEnemies(sf::RenderTarget& target)
{
	// Draw the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}
#endif //_MOVE_ENEMY_FILE

/// <summary>
/// Test for displaying a score
/// </summary>
void Game::renderScore()
{

}

/// <summary>
/// Reset the game state to default
/// </summary>
void Game::resetGame()
{
	Defines defines = Defines();
	this->lives = this->default_lives;
	this->points = 0;
	this->endScreen = false;
	this->endGame = false;
	
	// TODO Move these into Enemy.cpp
	if (fastEnemies)
	{
		this->enemySpawnTimerMax = 1.0f;
	}
	else 
	{
		this->enemySpawnTimerMax = 10.0f;
	}

	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 20.0f;

	// Set the enemy speed
	if (fastEnemiesFall)
	{
		// Fast enemies
		this->enemySpeed = 25.0f;
	}
	else
	{
		// Normal speed
		this->enemySpeed = 5.0f;
	}
	//

	// Set mouse held to false
	this->mouseHeld = false;

	// Set health
	this->health = defines.playerHealth;
}

/// <summary>
/// Get the keyboard events and other stuff.
/// </summary>
void Game::PollEvents()
{
#ifdef _MOVE_WINDOW_FILE
	WindowManager windowManager = WindowManager();
#endif //_MOVE_WINDOW_FILE

	// Event polling
	// While we are getting events from the window, save them in here
#ifdef _MOVE_WINDOW_FILE
	// TODO Fix this
	while (windowManager.getWindow().pollEvent(this->event))
#else
	while (this->window->pollEvent(this->event))
#endif //_MOVE_WINDOW_FILE
	{
		switch (this->event.type)
		{

			// Close the window
		case sf::Event::Closed:
			this->window->close();
			break;

			// Keys pressed
		case sf::Event::KeyPressed:
			

			// Make this into a switch statement, this is cleaner then the method I was using.
			switch (this->event.key.code) {
			case sf::Keyboard::Escape:
				// TODO Make this show a pause menu.
				
				// Original:
				// Close the window using escape.
				//this->window->close();

				// This works!!
				// Add a basic pause function, this just freezes the game until it's unpaused.
				this->isPaused = !this->isPaused;
				break;

			case sf::Keyboard::F1:
				// TODO Make this show and hide ImGui once I set it up.
				// I'm going to use ImGui for making debug menus once I progress further into making games.
				break;

			case sf::Keyboard::F4:
				// Close the window with F4, changed from escape for now.
				this->window->close();
				break;

			
			case sf::Keyboard::F11:
				// TODO Make this put the game into fullscreen
				break;
				
			case sf::Keyboard::Return:
				// This resets the score, lives and everything back to default.
				// I finally got this working to where it resets the game.
				if (this->getEndScreen()) {
					this->endScreen = false;
					this->endGame = false; // Test
					//this->window->clear();
					this->resetGame();

					
					//window->draw()
				}
				break;
			}
			
			break;
		}
	}
}

/// <summary>
/// Updates the mouse positions:
///  Mouse position relative to window (Vector2i)
/// </summary>
/// 
#ifndef _MOVE_MOUSE_UTIL
void Game::updateMousePositions()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	// This takes a pixel from the window, making it a float.
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

	//int mousePosX = sf::Mouse::getPosition().x;
//int mousePosY = sf::Mouse::getPosition().y;

//// Relative to the window
//int mousePosRelX = sf::Mouse::getPosition(*this->window).x;
//int mousePosRelY = sf::Mouse::getPosition(*this->window).y;

	// Update mouse position

// Relative to the screen
//std::cout << "Mouse pos: \nX:" << mousePosX
//	<< "\nY: " << mousePosY << std::endl;

	// Relative to the window
#ifdef _SHOW_MOUSE_POS
	std::cout << "Mouse pos: \nX:" << mousePosRelX
		<< "\nY: " << mousePosRelY << std::endl;
#endif //_SHOW_MOUSE_POS
}
#endif //_MOVE_MOUSE_UTIL

/// <summary>
/// Update the game text
/// </summary>
void Game::UpdateText()
{
	// This is kind of like cout, can add floats, ints and everything else to it.
	std::stringstream points_ss;
	std::stringstream health_ss;

	points_ss << "Points: " << this->points;
	health_ss << "Health: " << this->health;

	this->scoreText.setString(points_ss.str());
	this->healthText.setString(health_ss.str());
}

/// <summary>
/// Show the game end screen as a test.
/// This idea came from the open source Asteroids project
/// https://github.com/Anmfishe/Asteroids-SFML-CPP
/// </summary>
void Game::renderEndScreen() 
{
	this->endScreenText.setString("Your score was " + std::to_string(this->points) 
		+ "\nPress enter to play again");

	// Draw the text to the window.
	window->draw(endScreenText);
	
}

/// <summary>
/// Updates the game events
/// </summary>
void Game::Update()
{
	MouseUtil mouseUtil = MouseUtil();
	Enemy enemy = Enemy();

	this->PollEvents();

	// If the game hasn't ended and isn't paused, let everything update
	// I got the idea for pausing the game from here.
	// https://en.sfml-dev.org/forums/index.php?topic=28906.0

	if (!this->endGame && !this->getPaused() && !this->getEndScreen())
	{
#ifdef _MOVE_MOUSE_UTIL
		mouseUtil.updateMousePositions(*this->window);
#else
		this->updateMousePositions();
#endif //_MOVE_MOUSE_UTIL
		// Update the game text
		this->UpdateText();

#ifndef _MOVE_ENEMY_FILE
		this->updateEnemies();
#else
		enemy.updateEnemies();
		
#endif //!_MOVE_ENEMY_FILE
	}
	
	// Show the end screen if the health goes below 0
	if (this->health <= 0)
	{
		// This can close the window.
		//this->endGame = true;
		this->endScreen = true;
	}



	//sf::Time elapsed = clock.getElapsedTime();

	//std::cout << "Time elapsed: " << elapsed.asSeconds() << " seconds" << std::endl;
}


#undef _MOVE_MOUSE_UTIL





/// <summary>
/// 
// Clear old frame
// Render objects
// Display frame in window
// Renders the game objects
/// </summary>
void Game::Render()
{

	Enemy enemy = Enemy();
	// 
	// Use this to generate colors:
	// https://www.rapidtables.com/web/color/RGB_Color.html
	// Light blue
	// this->window->clear(sf::Color(102, 178, 255, 255)); // Clear old frame
	// Gray
	this->window->clear(sf::Color(64, 64, 64, 255)); // Clear old frame

	// TODO Put a background in front of everything else, on the top of the screen.

	if (!this->getEndScreen()) {


		//this->window->draw(this->enemy);
#ifdef _MOVE_ENEMY_FILE
		//enemy.
#else
		this->RenderEnemies(*this->window);
#endif

		// Only run this for now if it is enabled
		if (renderTestItems)
		{
			// Render the score test.
			this->renderScore();

			// Show test text on screen.
			//this->renderText();
			this->RenderText(*this->window);
		}


		// Draw game objects

	}
	// Show the end screen
	// This now works, I just can't press enter to start a new game.
	else {
		//window->draw(endScreenText);
		this->renderEndScreen();
	}

	// Draw your game
	this->window->display(); // Tell app that window is done drawing.


}