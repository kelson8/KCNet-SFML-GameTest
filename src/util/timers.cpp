#include "timers.h"
#include <iostream>

#include <fmt/core.h>

Timers::Timers()
{
	m_ElapsedTime = 0;
	m_ElapsedTimeOld = 0;

	m_TimerDisplayConsole = true;

	// Start the timer when this constructor starts up
	this->StartTimer();
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
		m_ElapsedTimeOld++;
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
			std::cout << "Elapsed time (seconds): " << m_ElapsedTime << std::endl;
		}

		// Start the countdown over.  Think of laps on a stop watch.
		timerClock.restart();
	}
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

const int Timers::GetElapsedTime() const
{
	return m_ElapsedTime;
}
