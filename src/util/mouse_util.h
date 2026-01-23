#pragma once
#include <SFML/Graphics.hpp>

class MouseUtil
{
public:

	static MouseUtil& getInstance()
	{
		static MouseUtil instance; // Guaranteed to be destroyed.
		return instance;
	}

	//void updateMousePositions();
	void updateMousePositions(sf::RenderWindow& window);
	sf::Vector2i getMousePosWindow() const;
	sf::Vector2f getMousePosView() const;

	bool IsHoveringOverButton(float x1, float y1, float x2, float y2) const;
	
private:
	// Constructors / Destructors
	MouseUtil() {}
	//~Enemy();

	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
};

