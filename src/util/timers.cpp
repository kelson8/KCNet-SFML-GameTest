#include "timers.h"
#include <iostream>

#include <fmt/core.h>
#include "game.h"

// TODO Try to figure out how to consolidate some 
// of these timers into one function later, make helper functions for them.

Timers::Timers()
{
	m_ElapsedTime = 0;
	m_ElapsedTimeOld = 0;

	m_RoundScoreTimer = 0;
	// This sets this to a default value if this isn't found in the ini.
	m_MaxRoundScoreTime = iniHandler.GetInt("RoundTimes", "MaxRoundTime") 
		? iniHandler.GetInt("RoundTimes", "MaxRoundTime") : 30;

	m_TimerDisplayConsole = iniHandler.GetBool("Debug", "TimerDisplayConsole") ?
		iniHandler.GetBool("Debug", "TimerDisplayConsole") : false;

	// Start the timers when this constructor starts up
	this->StartTimer();

	scoreTimerClock.start();
}

Timers::~Timers()
{
	// This should work for stopping the clock when this ends, although not sure if this is needed.
	this->StopTimer();
}

/**
 * @brief Check if a second has passed.
 * @return If a second has passed in the game
 */
bool Timers::SecondPassed()
{
	if (m_ElapsedTime > m_ElapsedTimeOld)
	{
		//m_ElapsedTimeOld++;
		// Update old time to current time
		// This seems to fix the enemy hitting the player without 
		m_ElapsedTimeOld = m_ElapsedTime; 
		return true;
	}

	return false;
}

/**
 * @brief Start the main game timer
 */
void Timers::StartTimer()
{
	if (timerClock.isRunning())
		return;

	// Is this needed?
	timerClock.start();
	fmt::println("Main game timer has been started.");
}

/**
 * @brief Stop the main game timer
 */
void Timers::StopTimer()
{
	if (!timerClock.isRunning())
		return;

	timerClock.stop();
	fmt::println("Main game timer has been stopped.");
}

/**
 * @brief This is a timer that updates every second.
 * 
 * If enabled, this outputs the elapsed time to the console.
 */
void Timers::TimerLoop()
{
	// https://gamefromscratch.com/sfml-with-c-tutorial-series-windows-game-loops-and-timers/
	// I got this working!!
	// I had to move the timerClock.restart() into the if statement.
	// This only restarts if the timer seconds is now greater then one.
	if (timerClock.getElapsedTime().asSeconds() > 1)
	{
		m_ElapsedTime++;

		// TODO Make this a variable to be accessed in ImGui
		if (m_TimerDisplayConsole)
		{
			fmt::println("Elapsed time (seconds): {}", m_ElapsedTime);
		}

		// Start the countdown over.  Think of laps on a stop watch.
		timerClock.restart();
	}
}

/**
 * @brief Run the loop for the round timer.
 * 
 * This updates the games round after a set amount of time.
 */
void Timers::RoundTimerLoop()
{
	if (roundTimerClock.getElapsedTime().asSeconds() > 1)
	{
		m_RoundScoreTimer++;

		// After the max time, this resets back to 0 and increases the round to the game.
		if (m_RoundScoreTimer == m_MaxRoundScoreTime)
		{
			Game::getInstance().SetRound(Game::getInstance().GetRound() + 1);
			m_RoundScoreTimer = 0;
		}

		// Start the countdown over.
		roundTimerClock.restart();
	}
}

/**
 * @brief Setup a wait timer
 * @param duration The time in milliseconds, seconds, or minutes.
 * @param unit The unit, 'm' (milliseconds), 's' (seconds), 'M' (minutes)
 */
void Timers::StartWait(int duration, char unit)
{
	m_Waiting = true;

	switch (unit)
	{
		case 'm': // Milliseconds
			m_WaitDuration = duration / 1000.0f;
			break;
		case 's': // Seconds
			m_WaitDuration = duration;
			break;
		case 'M': // Minutes
			m_WaitDuration = duration;
			break;
		default:
			fmt::println("Invalid unit");
			m_Waiting = false;
			break;
	}

	// Start the wait clock
	waitClock.restart();
}

/**
 * @brief Loop for the timer with a custom time, separate from the main timer.
 */
void Timers::TimerWaitLoop()
{
	if (m_Waiting && waitClock.getElapsedTime().asSeconds() > m_WaitDuration)
	{
		m_Waiting = false;
	}
}

/**
 * @brief Setup the new timer that handles the score, increment the score once a second and reset it on death
 * 
 * I got this to work, I setup the m_CurrentScoreTime and m_Score variables to be incremented every second.
 * These values also get reset when the game ends.
 */
void Timers::ScoreTimer()
{
	if (!Game::getInstance().getPaused() &&
		!Game::getInstance().getEndScreen() &&
		!m_GameTimerStopped 
		&& scoreTimerClock.getElapsedTime().asSeconds() > 1)
	{
		m_CurrentScoreTime++;
		m_Score++;
		scoreTimerClock.restart();
	}

	if (!Game::getInstance().getEndScreen() && m_GameTimerStopped)
	{
		m_GameTimerStopped = false;
		scoreTimerClock.start();
		// Reset the score
		m_Score = 0;
	}

	if (Game::getInstance().getEndScreen() && !m_GameTimerStopped)
	{
		scoreTimerClock.stop();
		// Reset the score timer value.
		m_CurrentScoreTime = 0;
		m_GameTimerStopped = true;

		fmt::println("Timer has been stopped and reset, new value: {}", m_CurrentScoreTime);
	}
}

/**
 * @brief Get the current score value from the timer
 * @return The current time in seconds which is the players score.
 */
const int Timers::GetScore() const
{
	//return m_CurrentScoreTime;
	return m_Score;
}

/**
 * @brief Get the current time, this is how long the game has been open.
 * @return
 */
const int Timers::GetElapsedTime() const
{
	return m_ElapsedTime;
}


/**
 * @brief This some testing code for the timer system.
 */
void Timers::TimerTest()
{
	// Old Timer test

	// 
	// A microsecond is 1/1,000,000th of a second, 1000 microseconds == 1 millisecond
	//std::cout << "Elapsed time since previous frame(microseconds): " << timerClock.getElapsedTime().asMicroseconds() << std::endl;
	//std::cout << "Elapsed time since previous frame(seconds): " << timerClock.getElapsedTime().asSeconds() << std::endl;
	// Start the countdown over.  Think of laps on a stop watch.
	//timerClock.restart();

	//TimerTest();
	//std::cout << "Elapsed time since previous frame(seconds): " << m_ElapsedTime << std::endl;

	// Well this almost works as a timer, it goes too fast though..
	// https://en.sfml-dev.org/forums/index.php?topic=3547.0
	//if (deltaTime.asSeconds())
	//{
	//	//currentGameSeconds = deltaTime.asSeconds();
	//	//secondsToPass--;
	//	secondsToPass -= deltaTime.asSeconds();
	//}
	//std::cout << "Seconds: " << secondsToPass << std::endl;
	//std::cout << "Seconds: " << currentGameSeconds << std::endl;
}
