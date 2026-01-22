#include "imgui_screen_menu.h"

#include <fmt/core.h>

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>

#include "imgui_menu.h"

#include "util/text_handler.h"
#include "window_manager.h"

//ImGuiScreenMenu::ImGuiScreenMenu(ImGuiMenu& imGuiMenu)
ImGuiScreenMenu::ImGuiScreenMenu()
{
	showRandomScreenSize = false;

	randomScreenPosX = 0.0f;
	randomScreenPosY = 0.0f;

	m_PauseMenuTextPosX = 0.0f;
	m_PauseMenuTextPosY = 0.0f;

	m_PauseMenuInfoTextPosX = 0.0f;
	m_PauseMenuInfoTextPosY = 0.0f;

	m_RoundTextPosX = 0.0f;
	m_RoundTextPosY = 0.0f;

	// This works like this!
	m_ScreenSizeX = WindowManager::getInstance().getWindow().getSize().x;
	m_ScreenSizeY = WindowManager::getInstance().getWindow().getSize().y;

	std::cout << "Address of m_PauseMenuTextPosX: " << &m_PauseMenuTextPosX << std::endl;
	std::cout << "Address of m_PauseMenuTextPosY: " << &m_PauseMenuTextPosY << std::endl;
	std::cout << "Address of m_PauseMenuInfoTextPosX: " << &m_PauseMenuInfoTextPosX << std::endl;
	std::cout << "Address of m_PauseMenuInfoTextPosY: " << &m_PauseMenuInfoTextPosY << std::endl;
}


/**
 * @brief Setup two sliders for ImGui, helper function to not duplicate as much code.
 * 
 * This function will be useful for my text position sliders, so I don't have to duplicate these everywhere.
 * 
 * TODO Move this into a ImGuiUtil class.
 * 
 * @param slider1Value The storage value for the first slider
 * @param slider2Value The storage value for the first slider
 * @param sliderMinimum The sliders minimum values
 * @param headerText The text to display above the slider.
 * @param slider1Text The text for the first slider.
 * @param slider2Text The text for the second slider.
 */
void ImGuiScreenMenu::PositionDebugSlider(float *slider1Value, float *slider2Value, float sliderMinimum, 
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
 * @param textPosition The TextPositions enum value for the text to update.
 * @param posX The new X position for the text.
 * @param posY The new Y position for the text.
 * @param buttonLabel The label for the button.
 */
void ImGuiScreenMenu::PositionDebugButton(TextPositions textPosition, float posX, float posY, const char* buttonLabel)
{
	if (ImGui::Button(buttonLabel))
	{
		TextHandler::getInstance().SetDisplayPositions(textPosition, posX, posY);
	}
}

/**
 * @brief Display the screen menu.
 */
void ImGuiScreenMenu::Draw()
{
	WindowManager& windowManager = WindowManager::getInstance();
	TextHandler& textHandler = TextHandler::getInstance();
	ImGuiMenu& imGuiMenu = ImGuiMenu::getInstance();

	float screenSizeX = windowManager.getWindow().getSize().x;
	float screenSizeY = windowManager.getWindow().getSize().y;

	if (ImGui::CollapsingHeader("Screen Info"))
	{
		// TODO Move lives debug and other items into here out of player.

		ImGui::Separator();

		ImGui::Text("Screen Size: ");
		ImGui::Text(fmt::format("X: {}", screenSizeX).c_str());
		ImGui::Text(fmt::format("Y: {}", screenSizeY).c_str());


		ImGui::Separator();

		//------
		// Random screen size 
		//------

		// Random screen sizes
		ImGui::Text("Random screen size testing");

		// Update the random screen size variables
		if (ImGui::Button("Update Random Screen Size"))
		{
			this->SetRandomScreenPos();
		}

		ImGui::Checkbox("Display random screen size", &showRandomScreenSize);

		// I fixed this by making a randomScreenPosX and Y variable, and updating it on a button press.
		// This random screen size could be useful for random player or enemy spawns if I fine tune it.
		if (showRandomScreenSize)
		{
			ImGui::Text(fmt::format("X: {}", randomScreenPosX).c_str());
			ImGui::Text(fmt::format("Y: {}", randomScreenPosY).c_str());
		}

		ImGui::Separator();

		//------
		// Pause menu debug
		//------

		ImGui::Text("Pause menu debug");

		PositionDebugSlider(&m_PauseMenuTextPosX, &m_PauseMenuTextPosY, 0.0, "Pause menu main text", "Main text pos X", 
			"Main text pos Y");

		// This is using tuples and returning them, works well for a coordinate system.
		// TODO Make this into a function later
		ImGui::Text(fmt::format("Current Pos X: {}",
			std::get<0>(textHandler.GetDisplayPositions(TextPositions::PAUSE_TEXT_POSITION))).c_str());

		ImGui::Text(fmt::format("Current Pos Y: {}",
			std::get<1>(textHandler.GetDisplayPositions(TextPositions::PAUSE_TEXT_POSITION))).c_str());


		PositionDebugButton(TextPositions::PAUSE_TEXT_POSITION,
			m_PauseMenuTextPosX, m_PauseMenuTextPosY, "Apply pause positions");

		ImGui::Separator();

		
		// Pause info text, game name, version and other stuff.
		PositionDebugSlider(&m_PauseMenuInfoTextPosX, &m_PauseMenuInfoTextPosY, 0.0, "Pause info text pos", 
			"Info text pos X", "Info text pos Y");
		PositionDebugButton(TextPositions::PAUSE_NAME_VERSION_INFO_POSITION,
			m_PauseMenuInfoTextPosX, m_PauseMenuInfoTextPosY, "Apply info positions");
	}
}


//void ImGuiScreenMenu::PauseMenuMainText()
//{
//	ImGui::Text("Pause menu main text");
//	ImGui::SliderFloat("Text pos X", &m_PauseMenuTextPosX, 0.0, m_ScreenSizeX - imGuiMenu.GetMaxTextXPos());
//	ImGui::SliderFloat("Text pos Y", &m_PauseMenuTextPosY, 0.0, m_ScreenSizeY - imGuiMenu.GetMaxTextYPos());
//
//	//ImGui::Text(fmt::format("Current Pos X: {}", textHandler.GetDisplayPositions(TextPositions::PAUSE_TEXT_POSITION)).c_str());
//	ImGui::Text(fmt::format("Current Pos X: {}",
//		std::get<0>(textHandler.GetDisplayPositions(TextPositions::PAUSE_TEXT_POSITION))).c_str());
//
//	ImGui::Text(fmt::format("Current Pos Y: {}",
//		std::get<1>(textHandler.GetDisplayPositions(TextPositions::PAUSE_TEXT_POSITION))).c_str());
//
//	if (ImGui::Button("Apply new text positions"))
//	{
//		textHandler.SetDisplayPositions(TextPositions::PAUSE_TEXT_POSITION, m_PauseMenuTextPosX, m_PauseMenuTextPosY);
//	}
//}

/**
 * @brief Set a random screen position for the random screen position generator in the menu.
 */
void ImGuiScreenMenu::SetRandomScreenPos()
{
	WindowManager& windowManager = WindowManager::getInstance();
	randomScreenPosX = windowManager.GetRandomScreenX();
	randomScreenPosY = windowManager.GetRandomScreenY();
}

#endif // _IMGUI_TEST