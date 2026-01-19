#include "music_util.h"

#include <iostream>
#include <vector>
#include <ctime>

#include "defines.h"

// This works
// Return with a pointer
sf::Music* MusicUtil::PlayMusic(const std::string& filename)
{
	Defines defines = Defines();

	sf::Music* music = new sf::Music();
	//if (!music->openFromFile(defines.musicSound))
	if (!music->openFromFile(filename))
	{
		//std::cout << "Error, could not find the game sound track." << std::endl;
		std::cerr << "Error, could not find the game sound track." << std::endl;
		delete music;
		return nullptr; // Handle error
	}

	return music;
}