#include "Game.h"

// Enable my mouse pos define below.
// TODO Add a timer to this, delay it by like 1 second instead of letting it run super fast.
//#define _SHOW_MOUSE_POS

// Private functions
void Game::initVariables()
{
	this->window = nullptr;
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
	this->enemy.setOutlineColor(sf::Color::Yellow);
	this->enemy.setOutlineThickness(1.0f);
}

// Create the window
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

void Game::PollEvents()
{
	/*
		Get the keyboard events and other stuff.
	*/

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

void Game::Update()
{
	/*
		Updates the game events
	*/
	this->PollEvents();

	// Get the mouse positions.
	// Relative to the screen
	int mousePosX = sf::Mouse::getPosition().x;
	int mousePosY = sf::Mouse::getPosition().y;

	// Relative to the window
	int mousePosRelX = sf::Mouse::getPosition(*this->window).x;
	int mousePosRelY = sf::Mouse::getPosition(*this->window).y;

	// Clock test, to slow this down a bit, this didn't work.
	//sf::Clock clock;



	// Update mouse position

	// Relative to the screen
	//std::cout << "Mouse pos: \nX:" << mousePosX
	//	<< "\nY: " << mousePosY << std::endl;

	// Relative to the window
#ifdef _SHOW_MOUSE_POS
	std::cout << "Mouse pos: \nX:" << mousePosRelX
		<< "\nY: " << mousePosRelY << std::endl;
#endif //_SHOW_MOUSE_POS

	//sf::Time elapsed = clock.getElapsedTime();

	//std::cout << "Time elapsed: " << elapsed.asSeconds() << " seconds" << std::endl;
}



void Game::Render()
{
	/*
		@return void

		- Clear old frame
		- Render objects
		- Display frame in window

		Renders the game objects
	*/

	// 
	// Use this to generate colors:
	// https://www.rapidtables.com/web/color/RGB_Color.html
	// Light blue
	// this->window->clear(sf::Color(102, 178, 255, 255)); // Clear old frame
	// Gray
	this->window->clear(sf::Color(64, 64, 64, 255)); // Clear old frame

	this->window->draw(this->enemy);

	// Draw game objects

	// Draw your game
	this->window->display(); // Tell app that window is done drawing.
}