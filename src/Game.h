#pragma once

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "util/defines.h"

/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Game
{
private:
	// Variables

	// Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	// Private functions
	void initVariables();
	void initWindow();

public:
	// Constructors / Destructors
	Game();
	~Game();

	// Accessors
	const bool running() const;

	// Functions
	void PollEvents();
	void Update();
	void Render();
};

