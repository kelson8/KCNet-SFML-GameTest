#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:

	//Bullet(sf::Vector2f size, sf::Vector2f position, sf::Color color);
	Bullet(float radius, sf::Vector2f position, sf::Color color);
	//~Bullet();

	void Draw(sf::RenderWindow& window);
	//void Fire();
	void SetPosition(sf::Vector2f position);

	void Move(sf::Vector2f offset);

	sf::Vector2f GetPosition() const;
	float GetRadius();

	const sf::CircleShape Get() const;

	const bool IsInBounds(sf::CircleShape entity);

private:
	

	// Bullet object
	sf::CircleShape m_Bullet;

	bool m_BulletOnScreen;
};

