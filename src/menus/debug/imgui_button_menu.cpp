#include "imgui_button_menu.h"

#include <fmt/core.h>

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>

#include "game.h"

#include "imgui_menu.h"
#include "util/text_handler.h"
#include "window_manager.h"

ImGuiButtonMenu::ImGuiButtonMenu()
{
	m_Button1PosX = 0.0f;
	m_Button1PosY = 0.0f;

	m_Button2PosX = 0.0f;
	m_Button2PosY = 0.0f;

	m_Button1SizeX = 0.0f;
	m_Button1SizeY = 0.0f;

	// Get the current screen X and Y size.
	m_ScreenSizeX = WindowManager::getInstance().getWindow().getSize().x;
	m_ScreenSizeY = WindowManager::getInstance().getWindow().getSize().y;
}

void ImGuiButtonMenu::Draw()
{
	if (ImGui::CollapsingHeader("Button debug"))
	{
		ImGui::Text("Set button position and size.");
		PositionDebugSlider(&m_Button1PosX, &m_Button1PosY, 0.0f, "Pause button 1 text pos",
			"Button 1 X", "Button 1 Y");

		PositionDebugSlider(&m_Button1SizeX, &m_Button1SizeY, 0.0f, "Pause button 1 size",
			"Button 1 size X", "Button 1 size Y");

		PositionDebugButton(ButtonPositions::PAUSE_MENU_TEST_BUTTON1_POSITION, m_Button1PosX, m_Button1PosY, 
			m_Button1SizeX, m_Button1SizeY,
			"Set pause button text pos");
	}
}

//-----------
// Taken from ImGuiScreenMenu, adapted for this usage
//-----------

/**
* @brief Setup two sliders for ImGui, helper function to not duplicate as much code.
*
* This function will be useful for my button position sliders, so I don't have to duplicate these everywhere.
*
* @param slider1Value The storage value for the first slider
* @param slider2Value The storage value for the first slider
* @param sliderMinimum The sliders minimum values
* @param headerText The text to display above the slider.
* @param slider1Text The text for the first slider.
* @param slider2Text The text for the second slider.
*/
void ImGuiButtonMenu::PositionDebugSlider(float* slider1Value, float* slider2Value, float sliderMinimum,
	const char* headerText, const char* sliderText1, const char* sliderText2) const
{
	ImGui::Text(headerText);
	ImGui::SliderFloat(sliderText1, slider1Value, 0.0, m_ScreenSizeX - ImGuiMenu::getInstance().GetMaxTextXPos());
	ImGui::SliderFloat(sliderText2, slider2Value, 0.0, m_ScreenSizeY - ImGuiMenu::getInstance().GetMaxTextYPos());
}

/**
 * @brief Shortcut function for creating position update debug buttons.
 *
 * This allows me to place a button with a custom text
 * and perform actions for moving texts on the game menu
 * 
 *
 * @param buttonPosition The ButtonPositions enum value for the button to update.
 * @param posX The new X position for the text.
 * @param posY The new Y position for the text.
 * @param sizeX The new Y size for the text.
 * @param sizeY The new Y size for the text.
 * @param buttonLabel The label for the button.
 */
void ImGuiButtonMenu::PositionDebugButton(ButtonPositions buttonPosition, float posX, float posY, 
	float sizeX, float sizeY, const char* buttonLabel)
{
	if (ImGui::Button(buttonLabel))
	{
		Game::getInstance().SetButtonPositions(buttonPosition, sf::Vector2f(posX, posY), sf::Vector2f(sizeX, sizeY));
	}
}

#endif // _IMGUI_TEST