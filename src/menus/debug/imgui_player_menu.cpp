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

		if (game.getEndScreen())
		{
			if (ImGui::Button("Respawn player"))
			{
				game.setEndGame(false);
				player.SetLives(Defines::defaultLives);
			}
		}

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