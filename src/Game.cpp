#include "Game.h"


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
// TODO Fix this
bool renderTestItems = false;


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
	this->window = nullptr;

	// Game logic
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

	this->window->setFramerateLimit(defines.gameFramerate);
}

// Constructors

/// <summary>
/// Initialize variables, the window, and enemies
/// </summary>
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

Game::~Game()
{
	// Delete the window
	delete this->window;
}

// Accessors
const bool Game::running() const
{
	return this->window->isOpen();
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
///  Removes the enemies at the edge of the screen. //TODO
/// </summary>
void Game::updateEnemies()
{
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

	// Moving and updating the enemies.
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		// Change the speed by changing the offsetY
		this->enemies[i].move(0.0f, enemySpeed);


		// Remove the enemies
		// Check if clicked upon
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// Only run if the mouse is clicked
			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
			{
				deleted = true;

				// Gain points
				this->points += 10.0f;
			
#ifdef _ENEMY_SOUNDS_TEST
				// Play sound effect
				sf::Sound enemySfx(*this->playEnemySfx());
				enemySfx.play();
#endif //_ENEMY_SOUNDS_TEST
			}
		}

		// Delete the enemy if they are past the bottom of the screen.
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			deleted = true;
		}

		// Final delete
		if (deleted)
		{
			this->enemies.erase(this->enemies.begin() + i);
		}
	}

	

}

/// <summary>
/// Render the enemies
/// </summary>
void Game::renderEnemies()
{
	// Draw the enemies
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

/// <summary>
/// Test for displaying a score
/// </summary>
void Game::renderScore()
{

}

/// <summary>
/// Test for showing text on the screen.
/// TODO Fix this to work.
/// </summary>
void Game::renderText()
{
	Defines defines = Defines();

	// https://www.sfml-dev.org/documentation/2.6.1/
	sf::Font gameFont;
	if (!gameFont.loadFromFile(defines.fontFile))
	{
		std::cout << "Error: the Game Fonts could not be loaded!" << std::endl;
	}

	sf::Text text("Hello SFML", gameFont, 50);
	//text.setPosition(sf::Vector2f(40.0f, 40.0f));


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
			// Close the window using escape.
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
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
/// Updates the game events
/// </summary>
void Game::Update()
{
	this->PollEvents();

	this->updateMousePositions();

	this->updateEnemies();

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
	this->renderEnemies();


	// Only run this for now if it is enabled
	if (renderTestItems)
	{
		// Render the score test.
		this->renderScore();

		// Show test text on screen.
		this->renderText();
	}


	// Draw game objects



	// Draw your game
	this->window->display(); // Tell app that window is done drawing.
}