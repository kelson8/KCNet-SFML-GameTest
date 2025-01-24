#include "Game.h"

// Private functions
void Game::initVariables()
{
	this->window = nullptr;
}

// Create the window
void Game::initWindow()
{
	Defines defines = Defines();

	this->videoMode.height = defines.screenHeight;
	this->videoMode.width = defines.screenWidth;

	//this->videoMode.getDesktopMode();

	this->window = new sf::RenderWindow(this->videoMode, defines.windowTitle, sf::Style::Titlebar | sf::Style::Close);
}


// Constructors

Game::Game()
{
	this->initVariables();
	this->initWindow();
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

	// Draw game objects

	// Draw your game
	this->window->display(); // Tell app that window is done drawing.
}