#pragma once
#include "../pch.h"

class MouseUtil
{
private:
	// Mouse positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

public:
	//void updateMousePositions();
	void updateMousePositions(sf::RenderWindow& window);
	sf::Vector2i getMousePosWindow() const;
	sf::Vector2f getMousePosView() const;
};

