#pragma once
#include "pch.h"

class WindowManager
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	//sf::Event event;

public:

	// Constructors / Destructors
	WindowManager();
	~WindowManager();

	// Accessors
	const bool running() const;

	void initWindow();

	const sf::RenderWindow* getWindow() const;

};

