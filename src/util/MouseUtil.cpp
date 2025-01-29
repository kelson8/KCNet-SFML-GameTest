#include "MouseUtil.h"

#include "Game.h"

/// <summary>
/// Updates the mouse positions:
///  Mouse position relative to window (Vector2i)
/// TODO Fix this to work in this file
/// It just makes the screen flicker, it can be toggled by defining _MOVE_MOUSE_UTIL in defines.h.
/// Just uncomment that at the top to test this.
/// </summary>
//void MouseUtil::updateMousePositions()
void MouseUtil::updateMousePositions(sf::RenderWindow &window)
{
	Game game = Game();

	//this->mousePosWindow = sf::Mouse::getPosition(*game.getWindow());
	this->mousePosWindow = sf::Mouse::getPosition(window);

	// This takes a pixel from the window, making it a float.
	//this->mousePosView = game.getWindow()->mapPixelToCoords(this->mousePosWindow);
	this->mousePosView = window.mapPixelToCoords(this->mousePosWindow);

	//int mousePosX = sf::Mouse::getPosition().x;
//int mousePosY = sf::Mouse::getPosition().y;

//// Relative to the window
//int mousePosRelX = sf::Mouse::getPosition(*this->window).x;
//int mousePosRelY = sf::Mouse::getPosition(*this->window).y;

	// Update mouse position

// Relative to the screen
//std::cout << "Mouse pos: \nX:" << mousePosX
//	<< "\nY: " << mousePosY << std::endl;

	// Relative to the window
#ifdef _SHOW_MOUSE_POS
	std::cout << "Mouse pos: \nX:" << mousePosRelX
		<< "\nY: " << mousePosRelY << std::endl;
#endif //_SHOW_MOUSE_POS
}

sf::Vector2i MouseUtil::getMousePosWindow() const
{
	return this->mousePosWindow;
}

sf::Vector2f MouseUtil::getMousePosView() const
{
	return this->mousePosView;
}
