#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MusicUtil
{
public:

	static MusicUtil& getInstance()
	{
		static MusicUtil instance; // Guaranteed to be destroyed.
		return instance;
	}

	sf::Music* PlayMusic(const std::string& filename);

private:
	// Constructors / Destructors
	MusicUtil() {}
	//~Enemy();
};

