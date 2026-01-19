#include "music_util.h"

#include <iostream>
#include <vector>
#include <ctime>

#include "defines.h"

/**
 * @brief Play music for the game
 * 
 * TODO Setup constructor/deconstructor for this.
 * @param filename The filename to play
 * @return The music if found, nullptr if not.
 */
sf::Music* MusicUtil::PlayMusic(const std::string& filename)
{
	Defines defines = Defines();

	sf::Music* music = new sf::Music();
	if (!music->openFromFile(filename))
	{
		std::cerr << "Error, could not find the game sound track." << std::endl;
		delete music;
		return nullptr;
	}

	return music;
}