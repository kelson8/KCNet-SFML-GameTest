#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>

class MusicUtil
{
public:

	static MusicUtil& getInstance()
	{
		static MusicUtil instance; // Guaranteed to be destroyed.
		return instance;
	}

	const sf::Music* GetMusicInfo();
	//const std::unique_ptr<sf::Music> GetMusicInfo();
	void SetMusicInfo(bool isLooping = true, bool isPaused = false, bool isPlaying = false, float newVolume = 50.0f);

	// TODO Figure out how to switch to a unique_ptr, that breaks the return in this function.
	sf::Music* PlayMusic(const std::string& filename);
	//std::unique_ptr<sf::Music> PlayMusic(const std::string& filename);

private:
	// Constructors / Destructors
	//MusicUtil();
	MusicUtil();
	~MusicUtil();

	MusicUtil(const MusicUtil&) = delete; // Prevent copying
	MusicUtil& operator=(const MusicUtil&) = delete; // Prevent assignment

	// The variable to store the current playing music track for the game.
	sf::Music* m_Music;
	//std::unique_ptr<sf::Music> m_Music;

	// If the music is paused
	bool m_MusicPaused;
};

