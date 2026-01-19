#include "music_util.h"

#include <iostream>
#include <vector>
#include <ctime>

#include "defines.h"
#include <fmt/core.h>

// Info for pointers:
// https://www.codegenes.net/blog/when-do-i-have-to-delete-a-pointer/

/**
 * @brief Setup the variables for the current playing music track.
 */
MusicUtil::MusicUtil()
{
	m_Music = new sf::Music();

	m_MusicPaused = false;
}

/**
 * @brief Free up memory for variables and pointers.
 */
MusicUtil::~MusicUtil()
{
	fmt::println("Shutting down music system and freeing up memory.");
	delete m_Music;
	m_Music = nullptr;
}

/**
 * @brief Get the currently playing music track
 * @return 
 */
const sf::Music* MusicUtil::GetMusicInfo()
{
	return m_Music;
}

/**
 * @brief Set the info for the music playing.
 * @param isLooping If the music is looping.
 * @param isPaused If the music should be paused.
 * @param isPlaying If the music should be played.
 * @param newVolume The new volume for the music.
 */
void MusicUtil::SetMusicInfo(bool isLooping, bool isPaused, bool isPlaying, float newVolume)
{
	m_Music->setLooping(isLooping);
	if (isPaused && !m_MusicPaused)
	{
		m_Music->pause();
		m_MusicPaused = true;
	}

	if (isPlaying && m_MusicPaused)
	{
		m_Music->play();
		m_MusicPaused = false;
	}

	m_Music->setVolume(newVolume);
	
}

/**
 * @brief Play music for the game
 * 
 * @param filename The filename to play
 * @return The music if found, nullptr if not.
 */
sf::Music* MusicUtil::PlayMusic(const std::string& filename)
{
	Defines defines = Defines();

	if (m_Music == nullptr)
	{
		fmt::println("Error, m_Music is a null pointer! Not loading music.");
		return nullptr;
	}

	if (!m_Music->openFromFile(filename))
	{
		std::cerr << "Error, could not find the game sound track." << std::endl;
		delete m_Music;
		return nullptr;
	}

	return m_Music;
}