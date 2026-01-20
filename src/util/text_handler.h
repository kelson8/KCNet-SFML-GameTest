#pragma once
#include <SFML/Graphics.hpp>
#include "defines.h"

#include <tuple>

#ifdef _IMGUI_TEST
enum class TextPositions
{
	SCORE_TEXT_POSITION,
	HEALTH_TEXT_POSITION,
	LIVES_TEXT_POSITION,
	PAUSE_TEXT_POSITION,
	PAUSE_CONTINUE_TEXT_POSITION,

};
#endif // _IMGUI_TEST

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

	void Init();
	void InitFonts();
	void InitVariables();
	void InitPauseMenu();

	// Resources
	sf::Font font;

	// Text
	sf::Text scoreText;
	sf::Text healthText;
	sf::Text livesText;
	sf::Text endScreenText;

	sf::Text pauseMenuText;
	sf::Text pauseMenuContinueText;

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

	// Pause menu
	float m_PauseMenuTextPosX;
	float m_PauseMenuTextPosY;

	// End screen text Position X
	float m_EndScreenTextPosX;
	// End screen text Position Y
	float m_EndScreenTextPosY;
	//
};

