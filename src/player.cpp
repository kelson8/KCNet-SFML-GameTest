#include "player.h"

#include <iostream>

/**
 * @brief Setup the player
 */
Player::Player()
{
	//windowManager = WindowManager::getInstance();
	//windowManager = new WindowManager();
	//windowManager = WindowManager();

	// Run the setup for the player
	Setup();

	playerHealth = 100;
	playerLives = 3;

	//moveSpeed = 10.0f;
	moveSpeed = 30.0f;

	playerJumpStatus = false;
	
}

/**
 * @brief Unset the variables and stuff for the player
 */
Player::~Player()
{

}

/**
 * @brief Setup the player
 */
void Player::Setup()
{
	WindowManager& windowManager = WindowManager::getInstance();

	// Set the size and color of the player.
	this->player.setSize(sf::Vector2f(50.f, 50.f));
	this->player.setFillColor(sf::Color::Green);

	// Get the size of the player shape
	sf::Vector2f playerSize = this->player.getSize();
	sf::Vector2u windowSize = windowManager.getWindow().getSize();

	// Calculate the center position
	float centerX = (windowSize.x - playerSize.x) / 2;
	float centerY = (windowSize.y - playerSize.y) / 2;

	// Set the default starting position.
	this->player.setPosition(sf::Vector2f(centerX, centerY));

	//std::cout << "Player position X: " << centerX << " Y: " << centerY << std::endl;
}

/**
 * @brief Draw the player to the screen
 */
void Player::Draw()
{
	WindowManager& windowManager = WindowManager::getInstance();
	windowManager.getWindow().draw(this->player);
}

/**
 * @brief Get the players X and Y position
 * @return The players X and Y as a sf::Vector2f
 */
sf::Vector2f Player::GetPosition()
{
	return this->player.getPosition();
}

/**
 * @brief Set the player X and Y
 * @param x New X Position
 * @param y New Y Position
 */
void Player::SetPosition(float x, float y)
{
	this->player.setPosition(sf::Vector2f(x, y));
	
}

/**
 * @brief Move the player
 * @param x The X pos to move towards.
 * @param y The Y pos to move towards.
 * 
 * TODO Make this to where it doesn't always place the player back
 *  in the center of the screen.
 */
void Player::Move(float x, float y)
{

	// TODO Move elsewhere
	WindowManager& windowManager = WindowManager::getInstance();

	// Get the size of the player shape
	sf::Vector2f playerSize = this->player.getSize();
	sf::Vector2u windowSize = windowManager.getWindow().getSize();

	// Calculate the center position
	float centerX = (windowSize.x - playerSize.x) / 2;
	float centerY = (windowSize.y - playerSize.y) / 2;

	//


	// This works for bounds checking!!
	// I had to change this to set the position, not the X and Y values.
	if (!this->IsInBounds())
	{
		this->SetPosition(centerX, centerY);
	}

	this->player.move(sf::Vector2f(x, y));
}

/**
 * @brief Get the players move speed
 * @return The current move speed of the player
 */
const float Player::GetMoveSpeed() const
{
	return this->moveSpeed;
}

/**
 * @brief Set the current move speed of the player
 * @param speed The new move speed of the player.
 */
void Player::SetMoveSpeed(float speed)
{
	this->moveSpeed = speed;
}

/**
 * @brief Check if the player is in the bounds of the map
 * 
 * TODO Re-use this for the enemies also, possibly make into shared code somewhere if possible.
 * @return If the player is in the map bounds.
 */
const bool Player::IsInBounds()
{
	WindowManager& windowManager = WindowManager::getInstance();

	float playerPosX = GetPosition().x;
	float playerPosY = GetPosition().y;

	float screenSizeX = windowManager.getWindow().getSize().x;
	float screenSizeY = windowManager.getWindow().getSize().y;

	// This is the amount of space above the screen for the X and Y, otherwise it won't count as being out of bounds until
	//  the player leaves the map a bit.
	int maxBounds = 50;

	if (
		playerPosX > screenSizeX - maxBounds ||
		playerPosY > screenSizeY - maxBounds ||
		playerPosX < -5 ||
		playerPosY < -5)
	{
		return false;
	}

	return true;
}