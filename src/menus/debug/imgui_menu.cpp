#include "imgui_menu.h"

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>

#include "player.h"
#include "window_manager.h"
#include "game.h"

ImGuiMenu::ImGuiMenu()
{
	showDemoWindow = false;
}

ImGuiMenu::~ImGuiMenu()
{

}

void ImGuiMenu::Draw()
{
	WindowManager& windowManager = WindowManager::getInstance();
	Player& player = Player::getInstance();
	Game& game = Game::getInstance();

	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow();
	}

	//ImGui::Begin("Hello, world!");
	ImGui::Begin("Player values: ");

	// TODO Fix this to work
	ImGui::Text("Position: ", player.GetPosition().x);
	ImGui::Text("X: ", player.GetPosition().x);
	ImGui::Text("Y: ", player.GetPosition().y);

	//ImGui::Button("Look at this pretty button");
	ImGui::End();
}

#endif // _IMGUI_TEST