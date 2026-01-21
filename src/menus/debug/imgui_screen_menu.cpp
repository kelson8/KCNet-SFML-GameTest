#include "imgui_screen_menu.h"

#include <fmt/core.h>

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>

#include "imgui_menu.h"

#include "util/text_handler.h"
#include "window_manager.h"

ImGuiScreenMenu::ImGuiScreenMenu()
{
	showRandomScreenSize = false;

	randomScreenPosX = 0;
	randomScreenPosY = 0;

	m_PauseMenuTextPosX = 0.0f;
	m_PauseMenuTextPosY = 0.0f;

	m_PauseMenuInfoTextPosX = 0.0f;
	m_PauseMenuInfoTextPosY = 0.0f;
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
		ImGui::Text("Screen Size: ");
		ImGui::Text(fmt::format("X: {}", screenSizeX).c_str());
		ImGui::Text(fmt::format("Y: {}", screenSizeY).c_str());


		ImGui::Separator();

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

		// This is using tuples and returning them, works well for a coordinate system.
		// TODO Make helper functions for some of these later.
		
		ImGui::Text("Pause menu debug");
		ImGui::Text("Pause menu main text");
		ImGui::SliderFloat("Text pos X", &m_PauseMenuTextPosX, 0.0, screenSizeX - imGuiMenu.GetMaxTextXPos());
		ImGui::SliderFloat("Text pos Y", &m_PauseMenuTextPosY, 0.0, screenSizeY - imGuiMenu.GetMaxTextYPos());

		//ImGui::Text(fmt::format("Current Pos X: {}", textHandler.GetDisplayPositions(TextPositions::PAUSE_TEXT_POSITION)).c_str());
		ImGui::Text(fmt::format("Current Pos X: {}",
			std::get<0>(textHandler.GetDisplayPositions(TextPositions::PAUSE_TEXT_POSITION))).c_str());

		ImGui::Text(fmt::format("Current Pos Y: {}",
			std::get<1>(textHandler.GetDisplayPositions(TextPositions::PAUSE_TEXT_POSITION))).c_str());

		if (ImGui::Button("Apply new text positions"))
		{
			textHandler.SetDisplayPositions(TextPositions::PAUSE_TEXT_POSITION, m_PauseMenuTextPosX, m_PauseMenuTextPosY);
		}

		ImGui::Separator();

		// This currently doesn't work, I'll try to fix it later.
		ImGui::Text("Pause menu info text");
		ImGui::SliderFloat("Text pos X", &m_PauseMenuInfoTextPosX, 0.0, screenSizeX - imGuiMenu.GetMaxTextXPos());
		ImGui::SliderFloat("Text pos Y", &m_PauseMenuInfoTextPosY, 0.0, screenSizeY - imGuiMenu.GetMaxTextYPos());

		if (ImGui::Button("Apply new text positions"))
		{
			textHandler.SetDisplayPositions(TextPositions::PAUSE_NAME_VERSION_INFO_POSITION, m_PauseMenuInfoTextPosX, m_PauseMenuInfoTextPosY);
		}
	}
}

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