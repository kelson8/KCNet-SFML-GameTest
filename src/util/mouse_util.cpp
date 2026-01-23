#include "mouse_util.h"
#include <fmt/core.h>

#include "window_manager.h"

/*
 * @brief Updates the mouse positions:
 * @param window The sf::RenderWindow to update the mouse positions for.
 */
void MouseUtil::updateMousePositions(sf::RenderWindow &window)
{

	WindowManager& windowManager = WindowManager::getInstance();

	this->mousePosWindow = sf::Mouse::getPosition(window);

	// This takes a pixel from the window, making it a float.
	this->mousePosView = window.mapPixelToCoords(this->mousePosWindow);

	int mousePosX = sf::Mouse::getPosition().x;
	int mousePosY = sf::Mouse::getPosition().y;

	// Relative to the window
	
	int mousePosRelX = sf::Mouse::getPosition(windowManager.getWindow()).x;
	int mousePosRelY = sf::Mouse::getPosition(windowManager.getWindow()).y;

}

/**
 * @brief Get the mouse position relative to window (sf::Vector2i)
 * @return The mouse position relative to window
 */
sf::Vector2i MouseUtil::getMousePosWindow() const
{
	return this->mousePosWindow;
}

/**
 * @brief Get the mouse position relative to the view (sf::Vector2i)
 * @return The mouse position relative to the view
 */
sf::Vector2f MouseUtil::getMousePosView() const
{
	return this->mousePosView;
}



/**
 * @brief Check if the mouse is hovering over a button
 * 
 * I switched to using GetGlobalBounds().contains instead of this, keeping here for future reference.
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 * @return If the mouse is hovering over a button.
 */
bool MouseUtil::IsHoveringOverButton(float x1, float y1, float x2, float y2) const
{
	if (getMousePosWindow().x >= x1 &&
		getMousePosWindow().x <= x2 &&
		getMousePosWindow().y >= y1 &&
		getMousePosWindow().y <= y2
		)
	{
		fmt::println("Button is hovered");
		return true;
	}

	return false;
}
