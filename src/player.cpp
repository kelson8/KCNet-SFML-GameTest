#include "player.h"

#include "entity.h"

#include <iostream>

#include "game.h"
#include "defines.h"

// Useful link for collisions:
// https://www.sfml-dev.org/tutorials/3.0/graphics/transform/#custom-transforms

// Currently, I have the player score being set in the Timers class.
// This is because I update the score every second the player is alive.
// I may decide to change this in the future.

/**
 * @brief Setup the player
 */
Player::Player()
{
	//windowManager = WindowManager::getInstance();
	//windowManager = new WindowManager();
	//windowManager = WindowManager();

	// Set the player size and color
	m_PlayerSize = 50.0f;
	m_PlayerColor = sf::Color::Green;

	// Player health, lives, and points
	m_PlayerHealth = 100;
	m_PlayerLives = Defines::defaultLives;
	m_PlayerPoints = 0;

	// Speed
	//m_MoveSpeed = 10.0f;
	m_MoveSpeed = 30.0f;

	// This is an unused option, not really for this game style.
	m_PlayerJumpStatus = false;

	// Run the setup for the player
	Setup();
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
	m_Player.setSize(sf::Vector2f(m_PlayerSize, m_PlayerSize));
	m_Player.setFillColor(m_PlayerColor);

	// Get the size of the player shape
	sf::Vector2f playerSize = m_Player.getSize();
	sf::Vector2u windowSize = windowManager.getWindow().getSize();

	// Calculate the center position
	float centerX = (windowSize.x - playerSize.x) / 2;
	float centerY = (windowSize.y - playerSize.y) / 2;

	// Set the default starting position.
	m_Player.setPosition(sf::Vector2f(centerX, centerY));

	//std::cout << "Player position X: " << centerX << " Y: " << centerY << std::endl;
}

/**
 * @brief Draw the player to the screen
 */
void Player::Draw()
{
	WindowManager& windowManager = WindowManager::getInstance();
	windowManager.getWindow().draw(m_Player);
}

/**
 * @brief Respawn the player
 *
 * Set the players lives back to default.
 */
void Player::Respawn()
{
	// Reset the players lives.
	ResetLives();
}

/**
 * @brief Get the player object
 * @return The sf::RectangleShape for the player.
 */
const sf::RectangleShape Player::GetPlayer() const
{
	return m_Player;
}

/**
 * @brief Get the players X and Y position
 * @return The players X and Y as a sf::Vector2f
 */
sf::Vector2f Player::GetPosition()
{
	return m_Player.getPosition();
}

/**
 * @brief Set the player X and Y
 * @param x New X Position
 * @param y New Y Position
 */
void Player::SetPosition(float x, float y)
{
	m_Player.setPosition(sf::Vector2f(x, y));
	
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
	Entity& entity = Entity::getInstance();

	// Get the size of the player shape
	sf::Vector2f playerSize = m_Player.getSize();
	sf::Vector2u windowSize = windowManager.getWindow().getSize();

	// Calculate the center position
	float centerX = (windowSize.x - playerSize.x) / 2;
	float centerY = (windowSize.y - playerSize.y) / 2;

	//


	// This works for bounds checking!!
	// I had to change this to set the position, not the X and Y values.

	// New for checking entities.
	if (!entity.IsInBounds(m_Player))
	{
		SetPosition(centerX, centerY);

		// Only remove lives if the player doesn't have god mode enabled.
		if (!HasGodMode())
		{
			m_PlayerLives = m_PlayerLives - 1;
		}
	}

	// Move the player
	m_Player.move(sf::Vector2f(x, y));
}

/**
 * @brief Get the players move speed
 * @return The current move speed of the player
 */
const float Player::GetMoveSpeed() const
{
	return m_MoveSpeed;
}

/**
 * @brief Set the current move speed of the player
 * @param speed The new move speed of the player.
 */
void Player::SetMoveSpeed(float speed)
{
	m_MoveSpeed = speed;
}

/**
 * @brief Get the players current lives
 * @return The current lives from the player.
 */
const int Player::GetLives() const
{
	return m_PlayerLives;
}

/**
 * @brief Basic function to check if the player has any lives.
 * @return If the player lives are less than or equal to 0.
 */
const bool Player::HasLives() const
{
	if (m_PlayerLives <= 0)
	{
		return false;
	}

	return true;
}

/**
 * @brief Set the player lives
 * @param points The lives to set to
 */
void Player::SetLives(int lives)
{
	m_PlayerLives = lives;
}

/**
 * @brief Reset the players lives back to the default value.
 */
void Player::ResetLives()
{
	SetLives(Defines::defaultLives);
}

/**
 * @brief Get the players current points
 * @return The current points from the player.
 */
const int Player::GetPoints() const
{
	return m_PlayerPoints;
}

/**
 * @brief Set the player points
 * @param points The points to set to
 */
void Player::SetPoints(int points)
{
	m_PlayerPoints = points;
}
