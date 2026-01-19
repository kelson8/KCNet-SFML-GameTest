#include "mouse_util.h"
#include <fmt/core.h>

#include "window_manager.h"


/// <summary>
/// Updates the mouse positions:
///  Mouse position relative to window (sf::Vector2i)
///  Mouse position relative to the view (sf::Vector2i)
/// </summary>
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

sf::Vector2i MouseUtil::getMousePosWindow() const
{
	return this->mousePosWindow;
}

sf::Vector2f MouseUtil::getMousePosView() const
{
	return this->mousePosView;
}
