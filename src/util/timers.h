#pragma once
#include <SFML/Graphics.hpp>

#include "defines.h"

class Timers
{
public:
	static Timers& getInstance()
	{
		static Timers instance; // Guaranteed to be destroyed.
		return instance;
	}

	bool SecondPassed();
	
	void StartTimer();
	void StopTimer();

	void TimerLoop();

	void TimerTest();

	const int GetElapsedTime() const;

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

