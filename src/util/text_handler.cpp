#include "text_handler.h"

#include "defines.h"

#include <fmt/core.h>

#include "player.h"
#include "game.h"

#include "timers.h"

#include <SFML/Audio.hpp>

#include "version.h"

/**
 * @brief Setup the variables for the TextHandler
 */
TextHandler::TextHandler() :
	scoreText(font),
	healthText(font),
	livesText(font),
	endScreenText(font),
	pauseMenuText(font),
	pauseMenuContinueText(font),
	pauseMenuInfoText(font)
{
	this->InitFonts();
	this->Init();
	this->InitVariables();
}

TextHandler::~TextHandler()
{

}

/**
 * @brief Helper function to setup the game texts.
 *
 * This is a cleaner way to setup texts in SFML.
 *
 * @param textHandler The sf::Text value to setup.
 * @param font The font to set to.
 * @param textPosition The position to display the text.
 * @param characterSize The character size for the text.
 * @param displayText The text to display on screen.
 */
void TextHandler::SetupText(sf::Text& textHandler, const sf::Font& font, 
	sf::Vector2f textPosition, uint32_t characterSize, const std::string& displayText)
{
	textHandler.setFont(font);
	textHandler.setPosition(textPosition);
	textHandler.setCharacterSize(characterSize);
	textHandler.setString(displayText);
}

/**
 * @brief Setup the color for the text
 * 
 * TODO Fix this to work later.
 * 
 * @param textHandler The sf::Text value to setup.
 * @param textColor The color of the text.
 */
void TextHandler::SetupColor(sf::Text& textHandler, sf::Color textColor)
{
	textHandler.setFillColor(textColor);
}

/**
 * @brief Setup the game text.
 */
void TextHandler::Init()
{

	//----
	// Main Screen
	//----
	InitGameText();

	//----
	// Pause screen
	//----
	InitPauseText();

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
	m_ScoreTextPosX = 0.0f;
	m_ScoreTextPosY = 0.0f;

	m_HealthTextPosX = 0.0f;
	m_HealthTextPosY = 30.0f;

	m_LivesTextPosX = 0.0f;
	m_LivesTextPosY = 60.0f;

	m_EndScreenTextPosX = 40.0f;
	m_EndScreenTextPosY = 40.0f;
	//

	// Pause menu
	m_PauseMenuTextPosX = 327.0f;
	m_PauseMenuTextPosY = 182.0f;

	// Pause menu, program name and version/other info display.
	m_PauseMenuInfoTextPosX = 0.0f;
	m_PauseMenuInfoTextPosY = 80.0f;
}

/**
 * @brief Setup the main screen for the game.
 * 
 * Sets up the score, lives, and other position displays.
 */
void TextHandler::InitGameText()
{
	// Score
	SetupText(scoreText, font, sf::Vector2f(0.0f, 0.0f), 24, "NONE");

	// This doesn't work for some reason.
	//SetupColor(scoreText, sf::Color::Blue);

	// Health
	// Not in use
	//SetupText(healthText, font, sf::Vector2f(0.0f, 30.0f), 24, "NONE");
	//SetupColor(scoreText, sf::Color::White);

	// Lives
	SetupText(livesText, font, sf::Vector2f(m_LivesTextPosX, m_LivesTextPosY), 24, "NONE");
	SetupColor(scoreText, sf::Color::White);


	// End screen
	// Blank by default
	SetupText(endScreenText, font, sf::Vector2f(40, 40), 48, "");
}

/**
 * @brief Setup the values for the pause menu
 */
void TextHandler::InitPauseText()
{
	SetupText(pauseMenuText, font, sf::Vector2f(m_PauseMenuTextPosX, m_PauseMenuTextPosY), 48, "Paused");

	SetupText(pauseMenuInfoText, font, sf::Vector2f(m_PauseMenuInfoTextPosX, m_PauseMenuInfoTextPosY), 32, 
		fmt::format("Welcome to {}: v{}{} ", Defines::gameName, PROJECT_VERSION_STRING, PROJECT_VERSION_SUFFIX));

	// Incomplete
	//SetupText(this->font, sf::Vector2f(40, 80), 48, "Continue?");
}



/**
 * @brief Update the game text
 * 
 * 
 * Updates the points, lives, and will do more later.
 * 
 */
void TextHandler::Update()
{
	Player& player = Player::getInstance();
	Timers& timers = Timers::getInstance();

	// This is kind of like cout, can add floats, ints and everything else to it.
	std::stringstream points_ss;
	//std::stringstream health_ss;
	std::stringstream lives_ss;

	points_ss << "Points: " << timers.GetScore();
	//points_ss << "Points: " << player.GetPoints();
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
	this->livesText.setPosition(sf::Vector2f(m_LivesTextPosX, m_LivesTextPosY));
#endif // _IMGUI_TEST
}

/**
 * @brief Pause screen for the game.
 * @param target
 */
void TextHandler::RenderPauseScreen(sf::RenderTarget& target)
{
	Game& game = Game::getInstance();

	if (game.getPaused())
	{
		// Paused text
		target.draw(this->pauseMenuText);
		//target.draw(this->pauseMenuContinueText);
		// Info text
		target.draw(this->pauseMenuInfoText);
	}

#ifdef _IMGUI_TEST
	// This is required for changing the position of the displays.
	this->pauseMenuText.setPosition(sf::Vector2f(m_PauseMenuTextPosX, m_PauseMenuTextPosY));
	this->pauseMenuInfoText.setPosition(sf::Vector2f(m_PauseMenuInfoTextPosX, m_PauseMenuInfoTextPosY));
#endif // _IMGUI_TEST
}

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
	this->endScreenText.setString(fmt::format("Your score was {} \nPress enter to play again", Timers::getInstance().GetScore()));

	// Draw the text to the window.
	windowManager.getWindow().draw(endScreenText);
}

#ifdef _IMGUI_TEST
// Debugging for moving the text display on screen
const float TextHandler::GetLivesTextPosX() const
{
	return this->m_LivesTextPosX;
}

const float TextHandler::GetLivesTextPosY() const
{
	return this->m_LivesTextPosY;
}

void TextHandler::SetLivesTextPos(float livesPosX, float livesPosY)
{
	this->m_LivesTextPosX = livesPosX;
	this->m_LivesTextPosY = livesPosY;
}

/**
 * @brief Set the text positions for debugging.
 * 
 * Not all of these values can be set yet, for these to be able to be set and updated:
 * 
 * First, you will need to create a member variable to store the X text position and Y text position.
 * 
 * Then, initialize that with a value in the InitVariables function.
 * 
 * Lastly, You will need to place something extra in the 
 *  TextHandler::Render function, or the TextHandler::RenderPauseScreen function depending on where you want this text to update.
 * 
 * Copy one of the methods from the _IMGUI_TEST preprocessor in one of those functions
 * and change to the values you are trying to update.
 * 
 * @param textPosEnum The text position to set from my enum
 * @param posX The X position on the screen.
 * @param posY The Y position on the screen.
 */
void TextHandler::SetDisplayPositions(TextPositions textPosEnum, float posX, float posY)
{
	switch (textPosEnum)
	{
	case TextPositions::SCORE_TEXT_POSITION:
	
		this->m_ScoreTextPosX = posX;
		this->m_ScoreTextPosY = posY;
		break;
	
	case TextPositions::HEALTH_TEXT_POSITION:
		this->m_HealthTextPosX = posX;
		this->m_HealthTextPosY = posY;
		break;

	case TextPositions::LIVES_TEXT_POSITION:
		this->m_LivesTextPosX = posX;
		this->m_LivesTextPosY = posY;
		break;

	case TextPositions::PAUSE_TEXT_POSITION:
		this->m_PauseMenuTextPosX = posX;
		this->m_PauseMenuTextPosY = posY;
		break;

	case TextPositions::PAUSE_CONTINUE_TEXT_POSITION:
		break;

	case TextPositions::PAUSE_NAME_VERSION_INFO_POSITION:
		this->m_PauseMenuInfoTextPosX = posX;
		this->m_PauseMenuInfoTextPosY = posY;
		break;

	default:
		break;
	}
}

/**
 * @brief Get the text positions for debugging.
 * 
 * This is a much better implementation then what I was doing 
 *  for the GetLivesTextPosX and GetLivesTextPosY functions.
 * 
 * https://stackoverflow.com/questions/321068/returning-multiple-values-from-a-c-function
 * 
 * @param textPosEnum The text position to get from my enum
 */
//float TextHandler::GetDisplayPositions(TextPositions textPosEnum)
std::tuple<float, float> TextHandler::GetDisplayPositions(TextPositions textPosEnum)
{
	switch (textPosEnum)
	{
	case TextPositions::SCORE_TEXT_POSITION:
		return std::make_tuple(m_ScoreTextPosX, m_ScoreTextPosY);

	case TextPositions::HEALTH_TEXT_POSITION:
		return std::make_tuple(m_HealthTextPosX, m_HealthTextPosY);

	case TextPositions::LIVES_TEXT_POSITION:
		return std::make_tuple(m_LivesTextPosX, m_LivesTextPosY);

	case TextPositions::PAUSE_TEXT_POSITION:
		return std::make_tuple(m_PauseMenuTextPosX, m_PauseMenuTextPosY);

	case TextPositions::PAUSE_CONTINUE_TEXT_POSITION:
		// TODO Set this one up.
		//return std::make_tuple(pauseMenuContinueTextPosX, pauseMenuContinueTextPosX);
		break;

	default:
		break;
	}
	// TODO Add better error handling to this later, for now just default to 0, 0.
	//return std::make_tuple(0, 0);
}

#endif // _IMGUI_TEST

