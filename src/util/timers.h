#pragma once
#include <SFML/Graphics.hpp>

#include "defines.h"
#include "util/ini_handler.h"

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
	
	void RoundTimerLoop();

	void StartWait(int duration, char unit);
	void TimerWaitLoop();

	void ScoreTimer();
	const int GetScore() const;

	void TimerTest();

	const int GetElapsedTime() const;

private:
	// Constructors / Destructors
	Timers();
	~Timers();

	IniHandler iniHandler;

	// Current elapsed time.
	int m_ElapsedTime;

	// Store the previous time value.
	int m_ElapsedTimeOld;

	// Toggle the timer showing in the console.
	bool m_TimerDisplayConsole;

	// Wait timer variables
	bool m_Waiting = false;
	float m_WaitDuration = 0;
	sf::Clock waitClock;

	// Game timer/score variables
	// Is the main game timer stopped?
	bool m_GameTimerStopped = false;

	// Timer for keeping track of the score.
	sf::Clock scoreTimerClock;

	// Timer for keeping track of the round.
	sf::Clock roundTimerClock;
	// Store the round score timer
	int m_RoundScoreTimer;
	// Set the round max score time, round gets 1 added, and clock resets when this is hit.
	int m_MaxRoundScoreTime;

	// Int to keep track of the time for the score.
	int m_CurrentScoreTime = 0;

	// Store the previous score value here for the end screen.
	int m_Score;
	//

	// Clock for the game timer display.
	sf::Clock timerClock;
};

