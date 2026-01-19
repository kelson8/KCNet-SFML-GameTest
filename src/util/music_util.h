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

	const sf::Music* GetMusicInfo();
	//void SetMusicInfo(bool isLooping = true, bool isPaused = false, bool isPlaying = false, float newVolume = 50.0f);
	void SetMusicInfo(bool isLooping = true, bool isPaused = false, bool isPlaying = false, float newVolume = 50.0f);

	sf::Music* PlayMusic(const std::string& filename);

private:
	// Constructors / Destructors
	//MusicUtil();
	MusicUtil();
	~MusicUtil();

	// The variable to store the current playing music track for the game.
	sf::Music* m_Music;

	// If the music is paused
	bool m_MusicPaused;
};

