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

	const bool HasGodMode() const;
	void SetGodMode(bool status);

	const bool IsInBounds(sf::RectangleShape entity);

	sf::FloatRect GetGlobalBounds(sf::RectangleShape entity);
	sf::FloatRect GetLocalBounds(sf::RectangleShape entity);

	//template <typename T> 
	template <typename T> 
	sf::FloatRect GetGlobalBoundsTest(T entity);
	//T GetGlobalBoundsTest(T entity);

//private:
protected:
	// Constructors / Destructors
	Entity();
	~Entity();

	bool m_EntityHasGodMode;
};

