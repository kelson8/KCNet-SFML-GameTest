#pragma once
#include <SFML/Graphics.hpp>
#include "defines.h"

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
	float scoreTextPosX;
	// Score text Position Y
	float scoreTextPosY;

	// Health text Position X
	float healthTextPosX;
	// Health text Position Y
	float healthTextPosY;

	// Lives text Position X
	float livesTextPosX;
	// Lives text Position Y
	float livesTextPosY;

	// End screen text Position X
	float endScreenTextPosX;
	// End screen text Position Y
	float endScreenTextPosY;
	//
};

