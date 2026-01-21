#include "imgui_player_menu.h"

#include <fmt/core.h>

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>

#include "imgui_menu.h"

#include "player.h"
#include "entity.h"
#include "window_manager.h"
#include "game.h"

#include "util/text_handler.h"

ImGuiPlayerMenu::ImGuiPlayerMenu()
{
	livesPosX = 0.0f;
	livesPosY = 0.0f;

	godModeActive = false;
	godModeActiveFlag = false;
}

void ImGuiPlayerMenu::Draw()
{
	WindowManager& windowManager = WindowManager::getInstance();
	Player& player = Player::getInstance();
	Entity& entity = Entity::getInstance();
	Game& game = Game::getInstance();
	TextHandler& textHandler = TextHandler::getInstance();

	float maxTextPosX = ImGuiMenu::getInstance().GetMaxTextXPos();
	float maxTextPosY = ImGuiMenu::getInstance().GetMaxTextYPos();

	float playerPosX = player.GetPosition().x;
	float playerPosY = player.GetPosition().y;

	float screenSizeX = windowManager.getWindow().getSize().x;
	float screenSizeY = windowManager.getWindow().getSize().y;

	if (ImGui::CollapsingHeader("Player info"))
	{
		ImGui::Text(fmt::format("Position:").c_str());
		ImGui::Text(fmt::format("X: {}", playerPosX).c_str());
		ImGui::Text(fmt::format("Y: {}", playerPosY).c_str());

		ImGui::Spacing();

		//-----
		// Check if player is out of bounds, I made a new function for this
		//-----
		if (!entity.IsInBounds(player.GetPlayer()))
		{
			ImGui::Text("Player is out of bounds.");
		}
		else
		{
			ImGui::Text("Player is in bounds.");
		}

		ImGui::Spacing();

		if (game.getEndScreen())
		{
			if (ImGui::Button("Respawn player"))
			{
				game.setEndGame(false);
				player.SetLives(Defines::defaultLives);
			}
		}

		ImGui::Spacing();

		//------
		// God mode
		// TODO Make these into checkboxes
		//------
		ImGui::Text("Toggle god mode");
		if (ImGui::Button("Enable god mode"))
		{
			if (!player.HasGodMode())
			{
				player.SetGodMode(true);
				fmt::println("God mode enabled");
			}
		}

		if (ImGui::Button("Disable god mode"))
		{
			if (player.HasGodMode())
			{
				player.SetGodMode(false);
				fmt::println("God mode disabled");
			}
		}

		// TODO Fix this
		//ImGui::Checkbox("Toggle god mode", &godModeActive);
		//if (godModeActive && !godModeActiveFlag && !player.HasGodMode())
		//{
		//	godModeActiveFlag = true;
		//	player.SetGodMode(true);
		//	fmt::println("God mode enabled");
		//}
		//else if (godModeActive && godModeActiveFlag && player.HasGodMode())
		//{
		//	godModeActiveFlag = false;
		//	player.SetGodMode(false);
		//	fmt::println("God mode disabled");
		//}

		// Bounds check testing with my new template
		// TODO Try to fix this template in the Entity class, not sure if it'll work like this.
		//ImGui::Text(fmt::format("Player bounds: X: {}", entity.GetGlobalBoundsTest(player.GetPlayer().getPosition().x)).c_str());
		//ImGui::Text(fmt::format("Player bounds: Y: {}", entity.GetGlobalBoundsTest(player.GetPlayer().getPosition().y)).c_str());

		//-----
		// Lives debug
		//-----
		if (ImGui::CollapsingHeader("Lives debug"))
		{
			ImGui::Text("Current lives position: ");
			ImGui::Text(fmt::format("X: {}", textHandler.GetLivesTextPosX()).c_str());
			ImGui::Text(fmt::format("Y: {}", textHandler.GetLivesTextPosY()).c_str());

			ImGui::SliderFloat("Lives Text X", &livesPosX, 0.0f,
				screenSizeX - maxTextPosX);
			ImGui::SliderFloat("Lives Text Y", &livesPosY, 0.0f,
				screenSizeY - maxTextPosY);

			if (ImGui::Button("Set Lives Position"))
			{
				textHandler.SetLivesTextPos(livesPosX, livesPosY);
			}

			ImGui::Text(fmt::format("Current lives: {}", player.GetLives()).c_str());
		}
	}
}

#endif // _IMGUI_TEST