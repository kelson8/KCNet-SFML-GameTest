#include "imgui_menu.h"

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>

#include "player.h"
#include "window_manager.h"
#include "game.h"

#include <fmt/core.h>

ImGuiMenu::ImGuiMenu()
{
	showDemoWindow = false;
	showImGuiWindow = false;

	showRandomScreenSize = false;

	randomScreenPosX = 0;
	randomScreenPosY = 0;
}

ImGuiMenu::~ImGuiMenu()
{

}

/**
 * @brief Set a random screen position for the random screen position generator in the menu.
 */
void ImGuiMenu::SetRandomScreenPos()
{
	WindowManager& windowManager = WindowManager::getInstance();
	randomScreenPosX = windowManager.GetRandomScreenX();
	randomScreenPosY = windowManager.GetRandomScreenY();
}

/**
 * @brief Get the status of the ImGui window
 * @return If the ImGui window is set to display or not.
 */
const bool ImGuiMenu::GetStatus()
{
	return this->showImGuiWindow;
}

/**
 * @brief Toggle the ImGui menu
 * @param toggle The status of the ImGui menu.
 */
void ImGuiMenu::SetStatus(bool toggle)
{
	//showImGuiWindow = toggle;
	this->showImGuiWindow = toggle;
}

/**
 * @brief Draw the ImGui window.
 */
void ImGuiMenu::Draw()
{
	//----
	// Variables

	WindowManager& windowManager = WindowManager::getInstance();
	Player& player = Player::getInstance();
	Game& game = Game::getInstance();

	float playerPosX = player.GetPosition().x;
	float playerPosY = player.GetPosition().y;

	float screenSizeX = windowManager.getWindow().getSize().x;
	float screenSizeY = windowManager.getWindow().getSize().y;

	// This is the amount of space above the screen for the X and Y, otherwise it won't count as being out of bounds until
	//  the player leaves the map a bit.
	int maxBounds = 50;

	//----
	// Window drawing.

	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow();
	}

	ImGui::Begin("Game Debugger");

	if(ImGui::CollapsingHeader("Player info"))
	{
		ImGui::Text(fmt::format("Position:").c_str());
		ImGui::Text(fmt::format("X: {}", playerPosX).c_str());
		ImGui::Text(fmt::format("Y: {}", playerPosY).c_str());

		
		// Check if player is out of bounds, I made a new function for this
		if(!player.IsInBounds())
		{
			ImGui::Text("Player is out of bounds.");
		}
		else {
			ImGui::Text("Player is in bounds.");
		}
	}


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
		if(showRandomScreenSize)
		{
			ImGui::Text(fmt::format("X: {}", randomScreenPosX).c_str());
			ImGui::Text(fmt::format("Y: {}", randomScreenPosY).c_str());
		}
	}

	ImGui::End();
}



#endif // _IMGUI_TEST