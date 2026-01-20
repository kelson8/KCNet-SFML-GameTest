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

	bool SecondPassed();
	void TimerTest();

private:
	// Constructors / Destructors
	Timers();
	~Timers();

	// Current elapsed time.
	int m_ElapsedTime;

	// Store the previous time value.
	int m_ElapsedTimeOld;

	// Toggle the timer showing in the console.
	bool m_TimerDisplayConsole;

	// Clock for the game timer display.
	sf::Clock timerClock;
};

