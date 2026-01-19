#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
	static Entity& getInstance()
	{
		static Entity instance; // Guaranteed to be destroyed.
		return instance;
	}

	const bool IsInBounds(sf::RectangleShape entity);

private:
	// Constructors / Destructors
	Entity();
	~Entity();
};

