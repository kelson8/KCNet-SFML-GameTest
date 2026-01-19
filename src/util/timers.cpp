#include "timers.h"
#include <iostream>


Timers::Timers()
{
	elapsedTime = 0;
}

Timers::~Timers()
{
	// This should work for stopping the clock when this ends, although not sure if this is needed.
	timerClock.stop();
}

/**
 * @brief This is a timer that updates every second.
 * There is some extra code in here from when I was messing around with this function.
 * This outputs the elaspedTime each second.
 */
void Timers::TimerTest()
{
	// https://gamefromscratch.com/sfml-with-c-tutorial-series-windows-game-loops-and-timers/
	// I got this working!!
	// I had to move the timerClock.restart() into the if statement.
	// This only restarts if the timer seconds is now greater then one.
	if (timerClock.getElapsedTime().asSeconds() > 1)
	{
		elapsedTime++;

		std::cout << "Elapsed time (seconds): " << elapsedTime << std::endl;

		// Start the countdown over.  Think of laps on a stop watch.
		timerClock.restart();
	}

	// Old Timer test

	// 
	// A microsecond is 1/1,000,000th of a second, 1000 microseconds == 1 millisecond
	//std::cout << "Elapsed time since previous frame(microseconds): " << timerClock.getElapsedTime().asMicroseconds() << std::endl;
	//std::cout << "Elapsed time since previous frame(seconds): " << timerClock.getElapsedTime().asSeconds() << std::endl;
	// Start the countdown over.  Think of laps on a stop watch.
	//timerClock.restart();

	//TimerTest();
	//std::cout << "Elapsed time since previous frame(seconds): " << elapsedTime << std::endl;

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