#pragma once
#include <SFML/Graphics.hpp>

class Timers
{
public:
	static Timers& getInstance()
	{
		static Timers instance; // Guaranteed to be destroyed.
		return instance;
	}

	void TimerTest();

private:
	// Constructors / Destructors
	Timers();
	~Timers();

	int elapsedTime;

	// Clock for the game timer display.
	sf::Clock timerClock;
};

