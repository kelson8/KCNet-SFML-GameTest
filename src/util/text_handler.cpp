#include "text_handler.h"

#include "defines.h"

#include "player.h"

#include <SFML/Audio.hpp>

/**
 * @brief Setup the variables for the TextHandler
 */
TextHandler::TextHandler() :
	scoreText(font),
	healthText(font),
	livesText(font),
	endScreenText(font)
{
	this->InitFonts();
	this->Init();
	this->InitVariables();
}

TextHandler::~TextHandler()
{

}

/**
 * @brief Setup the game text.
 */
void TextHandler::Init()
{
	//----
	// Score
	//----
	// Setup the font
	this->scoreText.setFont(this->font);

	// // Set the character size, fill color and default string
	this->scoreText.setCharacterSize(24);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setString("NONE");

	//----
	// Health
	//----
	// Setup the font
	this->healthText.setFont(this->font);

	// Set the Y to be lower then the scoreText, so it doesn't overlap.
	this->healthText.setPosition(sf::Vector2f(0.0f, 30.0f));

	// Set the character size, fill color and default string
	this->healthText.setCharacterSize(24);
	this->healthText.setFillColor(sf::Color::White);
	this->healthText.setString("NONE");

	//----
	// Lives
	//----
	this->livesText.setFont(this->font);

	// Set the Y to be lower then the the other vaules, so it doesn't overlap.
	//this->livesText.setPosition(sf::Vector2f(0.0f, 35.0f));
	this->livesText.setPosition(sf::Vector2f(livesTextPosX, livesTextPosY));

	// Set the character size, fill color and default string
	this->livesText.setCharacterSize(24);
	this->livesText.setFillColor(sf::Color::White);
	this->livesText.setString("NONE");


	//----
	// End screen
	//----
	this->endScreenText.setFont(this->font);
	//this->endScreenText.setPosition(40, 40);
	this->endScreenText.setPosition(sf::Vector2f(40, 40));
	this->endScreenText.setCharacterSize(48);
}

/**
 * @brief Setup the fonts for the game.
 */
void TextHandler::InitFonts()
{
	Defines defines = Defines();

	// If the font failed to load
	//if (!this->font.loadFromFile(defines.fontFile))
	if (!this->font.openFromFile(defines.fontFile))
	{
		std::cout << "Error, could not load font " << defines.fontFile << std::endl;
	}
}

/**
 * @brief Setup the TextHandler variables.
 */
void TextHandler::InitVariables()
{
	// Score text position values.
	scoreTextPosX = 0.0f;
	scoreTextPosY = 0.0f;

	healthTextPosX = 0.0f;
	healthTextPosY = 30.0f;

	livesTextPosX = 0.0f;
	livesTextPosY = 60.0f;

	endScreenTextPosX = 40.0f;
	endScreenTextPosY = 40.0f;
	//
}

/**
 * @brief Update the game text
 */
void TextHandler::Update()
{
	Player& player = Player::getInstance();
	// This is kind of like cout, can add floats, ints and everything else to it.
	std::stringstream points_ss;
	//std::stringstream health_ss;
	std::stringstream lives_ss;

	//points_ss << "Points: " << this->points;
	points_ss << "Points: " << player.GetPoints();
	//health_ss << "Health: " << player.getHealth();
	lives_ss << "Lives: " << player.GetLives();

	this->scoreText.setString(points_ss.str());
	//this->healthText.setString(health_ss.str());
	this->livesText.setString(lives_ss.str());
}

/**
 * @brief Render the score, health, and more in the future.
 * @param target
 */
void TextHandler::Render(sf::RenderTarget& target)
{
	// Draw the score text
	target.draw(this->scoreText);

	// Draw the health text
	//target.draw(this->healthText);

	// Draw the lives text
	target.draw(this->livesText);
#ifdef _IMGUI_TEST
	// This is required for changing the position of the displays.
	this->livesText.setPosition(sf::Vector2f(livesTextPosX, livesTextPosY));
#endif // _IMGUI_TEST

}

/// <summary>
/// Show the game end screen as a test.
/// This idea came from the open source Asteroids project
/// https://github.com/Anmfishe/Asteroids-SFML-CPP
/// </summary>
/// 

/**
 * @brief Show the game end screen
 * This idea came from the open source Asteroids project
 * 
 * https://github.com/Anmfishe/Asteroids-SFML-CPP
 * 
 */
void TextHandler::RenderEndScreen()
{
	WindowManager& windowManager = WindowManager::getInstance();
	//this->endScreenText.setString("Your score was " + std::to_string(this->points)
	this->endScreenText.setString("Your score was ... \nPress enter to play again");

	// Draw the text to the window.
	windowManager.getWindow().draw(endScreenText);
}

#ifdef _IMGUI_TEST
// Debugging for moving the text display on screen
const float TextHandler::GetLivesTextPosX() const
{
	return this->livesTextPosX;
}

const float TextHandler::GetLivesTextPosY() const
{
	return this->livesTextPosY;
}

void TextHandler::SetLivesTextPos(float livesPosX, float livesPosY)
{
	this->livesTextPosX = livesPosX;
	this->livesTextPosY = livesPosY;
}


#endif // _IMGUI_TEST

