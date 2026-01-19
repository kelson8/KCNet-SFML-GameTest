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
}

ImGuiMenu::~ImGuiMenu()
{

}

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
	}



	//ImGui::Button("Look at this pretty button");
	ImGui::End();
}

#endif // _IMGUI_TEST