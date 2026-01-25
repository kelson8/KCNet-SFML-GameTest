#include "bullet.h"

#include "window_manager.h"

// Basic class for a bullet, I plan on letting the player shoot the falling enemies with something.
// So far this won't work at all yet, I have to figure out how to implement it for the player.

Bullet::Bullet(float radius, sf::Vector2f position, sf::Color color)
{
	m_Bullet.setRadius(radius);
	m_Bullet.setPosition(position);
	m_Bullet.setFillColor(color);

	m_BulletOnScreen = false;
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(m_Bullet);
}

/**
 * @brief Fire the bullet
 * 
 * TODO Make this check if the bullet is on the screen, if it is no longer on the screen or hits an enemy remove it.
 */
//void Bullet::Fire()
//{
//	// I don't think this is right
//	while (IsInBounds)
//	{
//		Move(sf::Vector2f(1.0f, 1.0f));
//	}
//}

void Bullet::SetPosition(sf::Vector2f position)
{
	m_Bullet.setPosition(position);
}

void Bullet::Move(sf::Vector2f offset)
{
	m_Bullet.move(offset);
}

sf::Vector2f Bullet::GetPosition() const
{
	return m_Bullet.getPosition();
}

float Bullet::GetRadius()
{
	return m_Bullet.getRadius();
}

const sf::CircleShape Bullet::Get() const
{
	return m_Bullet;
}

const bool Bullet::IsInBounds(sf::CircleShape entity)
{
	WindowManager& windowManager = WindowManager::getInstance();

	//float playerPosX = GetPosition().x;
	float entityPosX = entity.getPosition().x;
	float entityPosY = entity.getPosition().y;
	//float playerPosY = GetPosition().y;

	float screenSizeX = windowManager.getWindow().getSize().x;
	float screenSizeY = windowManager.getWindow().getSize().y;

	// This is the amount of space above the screen for the X and Y, otherwise it won't count as being out of bounds until
	//  the player leaves the map a bit.
	int maxBounds = 50;

	if (
		entityPosX > screenSizeX - maxBounds ||
		entityPosY > screenSizeY - maxBounds ||
		entityPosX < -5 ||
		entityPosY < -5)
	{
		return false;
	}

	return true;
}
