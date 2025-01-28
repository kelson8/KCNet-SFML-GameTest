#include "Game.h"


// Enable ImGui test
// TODO Fix this to work.
//#define _IMGUI_TEST

#ifdef _IMGUI_TEST
// Imgui test
#include "imgui.h"
#include "imgui-SFML.h"

#endif //_IMGUI_TEST


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

	this->window = nullptr;

	// Game logic
	// Set the endgame status
	this->endGame = false;
	
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

	// Set the position
	//this->uiText.setPosition();
}

// Constructors

/// <summary>
/// Initialize variables, the window, and enemies
/// </summary>
Game::Game()
{
	this->initVariables();
	this->initWindow();

	// Setup fonts and text
	this->initFonts();
	this->initText();
	
	this->initEnemies();
}

Game::~Game()
{
	// Delete the window
	delete this->window;
}

// Accessors

/// <summary>
/// Check if the game is running
/// </summary>
/// <returns>True if the window is open</returns>
const bool Game::running() const
{
	return this->window->isOpen();
}

/// <summary>
/// Check the end game status
/// </summary>
/// <returns>True if the game has ended</returns>
const bool Game::getEndGame() const
{
	return this->endGame;
}

// Functions

/// <summary>
/// Spawn the enemies and set their colors and positions.
/// Sets a random position
/// Sets a random color
/// Adds enemy to the vector.
/// </summary>
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
void Game::updateEnemies()
{

	// TODO Fix this
#ifdef _ENEMY_SOUNDS_TEST
	// Play sound effect
	sf::Sound enemySfx(*this->playEnemySfx());
	enemySfx.play();
#endif //_ENEMY_SOUNDS_TEST

	Defines defines = Defines();

	// Updating the timer.
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			// Spawn the enemy and reset the timer.
			this->spawnEnemy();
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
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
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
void Game::RenderEnemies(sf::RenderTarget& target)
{
	// Draw the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

/// <summary>
/// Test for displaying a score
/// </summary>
void Game::renderScore()
{

}

/// <summary>
/// Get the keyboard events and other stuff.
/// </summary>
void Game::PollEvents()
{
	// Event polling
	// While we are getting events from the window, save them in here
	while (this->window->pollEvent(this->event))
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
				// TODO Make this show a pause menu, or just freeze the game for now.
				// Close the window using escape.
				this->window->close();
				break;

			case sf::Keyboard::F1:
				// TODO Make this show and hide ImGui once I set it up.
				// I'm going to use ImGui for making debug menus once I progress further into making games.
				break;

			
			case sf::Keyboard::F11:
				// TODO Make this put the game into fullscreen
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
/// Updates the game events
/// </summary>
void Game::Update()
{
	this->PollEvents();

	// If the game hasn't ended, let everything update.
	if (!this->endGame)
	{
		this->updateMousePositions();

		// Update the game text
		this->UpdateText();

		this->updateEnemies();
	}

	// End game if health goes below 0
	if (this->health <= 0)
	{
		this->endGame = true;
	}



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
	// 
	// Use this to generate colors:
	// https://www.rapidtables.com/web/color/RGB_Color.html
	// Light blue
	// this->window->clear(sf::Color(102, 178, 255, 255)); // Clear old frame
	// Gray
	this->window->clear(sf::Color(64, 64, 64, 255)); // Clear old frame

	// TODO Put a background in front of everything else, on the top of the screen.

	//this->window->draw(this->enemy);
	this->RenderEnemies(*this->window);


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



	// Draw your game
	this->window->display(); // Tell app that window is done drawing.
}