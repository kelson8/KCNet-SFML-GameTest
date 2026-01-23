#include "button_util.h"

// https://stackoverflow.com/questions/79570600/sfml-3-how-to-deal-with-texts-within-a-rectangle

// Mostly adapted from this guide
// https://www.youtube.com/watch?v=s2g0mPxZnvM

// This class can setup buttons, update their positions and more.
// It is setup in game.cpp, and updated in imgui_button_menu.cpp.

// So far this doesn't display any text on the buttons, I will try to fix that later.

/**
 * @brief Setup a button with a label on it
 * @param size The button size
 * @param position The button position
 * @param color The button color
 * @param text The label for the button
 */
ButtonUtil::ButtonUtil(sf::Vector2f size, sf::Vector2f position, sf::Color color)
//ButtonUtil::ButtonUtil(sf::Vector2f size, sf::Vector2f position, sf::Color color, 
	//std::string& text)
{
	if (!font.openFromFile(Defines::getInstance().fontFile))
	{
		std::cerr << "Error loading font" << std::endl;
	}

	sf::Font font(Defines::getInstance().fontFile);
	//sf::Text label(font);

	//std::string testT = "Test";
	//label(testT);

	buttonShape.setSize(size);
	buttonShape.setPosition(position);
	buttonShape.setFillColor(color);

	//label.setString(text);
	//label.setFont(font);
	//label.setPosition(position);
}

/**
 * @brief Draw the button to the screen, and once I set it up the label.
 * @param window 
 */
void ButtonUtil::Draw(sf::RenderWindow& window)
{
	window.draw(buttonShape);
	//window.draw(label);
}

/**
 * @brief Set the button position
 * @param position The Vector2 for the new position.
 */
void ButtonUtil::SetPosition(sf::Vector2f position)
{
	buttonShape.setPosition(position);
}

/**
 * @brief Get the current button position.
 * @return A sf::Vector2f of the current buttons position.
 */
sf::Vector2f ButtonUtil::GetPosition() const
{
	return buttonShape.getPosition();
}

/**
 * @brief Set the buttons current size.
 * @param position 
 */
void ButtonUtil::SetSize(sf::Vector2f size)
{
	buttonShape.setSize(size);
}

/**
 * @brief Get the buttons current size.
 * @return 
 */
sf::Vector2f ButtonUtil::GetSize() const
{
	return buttonShape.getSize();
}

sf::Color ButtonUtil::GetColor() const
{
	return buttonShape.getFillColor();
}

void ButtonUtil::SetColor(sf::Color color)
{
	buttonShape.setFillColor(color);
}

sf::FloatRect ButtonUtil::GetGlobalBounds() const
{
	return buttonShape.getGlobalBounds();
}