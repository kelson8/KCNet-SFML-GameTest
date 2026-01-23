#pragma once
#include <SFML/Graphics.hpp>

#include "defines.h"

enum class ButtonPositions
{
	// New for buttons
	PAUSE_MENU_TEST_BUTTON1_POSITION, // Pause menu, test button
	PAUSE_MENU_TEST_BUTTON2_POSITION, // Pause menu, test button1
	NONE,
};

class ButtonUtil
{
public:
	//static ButtonUtil& getInstance(sf::Vector2f size, sf::Vector2f position, sf::Vector2f color)
	//{
	//	static ButtonUtil instance; // Guaranteed to be destroyed.
	//	return instance;
	//}
	

	// Constructors / Destructors	
	ButtonUtil(sf::Vector2f size, sf::Vector2f position, sf::Color color);
	//ButtonUtil(sf::Vector2f size, sf::Vector2f position, sf::Color color,
		//std::string& text);
	//~ButtonUtil();

	void Draw(sf::RenderWindow& window);

	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition() const;

	void SetSize(sf::Vector2f size);
	sf::Vector2f GetSize() const;

	void SetColor(sf::Color color);
	sf::Color GetColor() const;

	sf::FloatRect GetGlobalBounds() const;
	
private:
	sf::RectangleShape buttonShape;

	sf::Font font;
	//sf::Text label(std::string&);
};

