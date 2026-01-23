#pragma once
#include <SFML/Graphics.hpp>
#include "defines.h"

#include <tuple>

#ifdef _IMGUI_TEST
enum class TextPositions
{
	SCORE_TEXT_POSITION, // Score text
	HEALTH_TEXT_POSITION, // Health text
	ROUND_TEXT_POSITION, // Round text
	LIVES_TEXT_POSITION, // Lives text
	PAUSE_TEXT_POSITION, // Pause text
	PAUSE_CONTINUE_TEXT_POSITION, // Continue text
	PAUSE_NAME_VERSION_INFO_POSITION, // Pause, program name and version/other info display.
	PAUSE_MUSIC_OPTIONS_TEXT_POSITION, // Pause, music options text.
	NONE,

};
#endif // _IMGUI_TEST

// Not in use
//enum class TextId
//{
//	SCORE_TEXT,
//	HEALTH_TEXT,
//  ROUND_TEXT,
//	LIVES_TEXT,
//	PAUSE_TEXT,
//	PAUSE_CONTINUE_TEXT,
//	PAUSE_NAME_VERSION_INFO,
//	TEXT_COUNT // Must be the last item
//};

class TextHandler
{
public:
	static TextHandler& getInstance()
	{
		static TextHandler instance; // Guaranteed to be destroyed.
		return instance;
	}

	void Update();
	void Render(sf::RenderTarget& target);
	void RenderPauseScreen(sf::RenderTarget& target);
	void RenderEndScreen();

#ifdef _IMGUI_TEST
	const float GetLivesTextPosX() const;
	const float GetLivesTextPosY() const;

	void SetLivesTextPos(float livesPosX, float livesPosY);
	void SetDisplayPositions(TextPositions textPosEnum, float posX, float posY);
	//float GetDisplayPositions(TextPositions textPosEnum);
	std::tuple<float, float> GetDisplayPositions(TextPositions textPosEnum);
#endif

private:
	// Constructors / Destructors
	TextHandler();
	~TextHandler();

	void SetupText(sf::Text& textHandler, const sf::Font& font,
		sf::Vector2f textPosition, uint32_t characterSize, const std::string& displayText);
	void SetupColor(sf::Text& textHandler, sf::Color textColor);

	void Init();
	//void InitFontVariables();
	void InitFonts();
	void InitVariables();
	void InitGameText();
	void InitPauseText();

	// Resources
	sf::Font font;

	// New for storing texts in a vector
	//std::vector<sf::Text> textObjects;

	// Text
	// Main game
	sf::Text scoreText; // Score
	sf::Text healthText; // Health
	sf::Text roundText; // Current round display
	sf::Text livesText; // Lives
	sf::Text endScreenText; // End screen

	// Pause menu
	sf::Text pauseMenuText; // Pause text
	sf::Text pauseMenuContinueText; // Pause text, continue
	sf::Text pauseMenuInfoText;
	
	sf::Text pauseMenuMusicToggleText;

	// Text position

	// Score text Position X
	float m_ScoreTextPosX;
	// Score text Position Y
	float m_ScoreTextPosY;

	// Health text Position X
	float m_HealthTextPosX;
	// Health text Position Y
	float m_HealthTextPosY;

	// Lives text Position X
	float m_LivesTextPosX;
	// Lives text Position Y
	float m_LivesTextPosY;

	// Current round text Position X
	float m_CurrentRoundPosX;
	// Current round text Position Y
	float m_CurrentRoundPosY;

	// Pause menu
	float m_PauseMenuTextPosX;
	float m_PauseMenuTextPosY;

	// Pause menu, program name and version/other info display.
	float m_PauseMenuInfoTextPosX;
	float m_PauseMenuInfoTextPosY;

	// Pause menu, toggle music option
	float m_PauseMenuToggleMusicPosX;
	float m_PauseMenuToggleMusicPosY;

	// End screen text Position X
	float m_EndScreenTextPosX;
	// End screen text Position Y
	float m_EndScreenTextPosY;
	//
};

