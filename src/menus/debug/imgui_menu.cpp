#include "imgui_menu.h"

#include <fmt/core.h>

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>

ImGuiMenu::ImGuiMenu()
{
	showDemoWindow = false;
	showImGuiWindow = false;

	maxTextPosX = 100.0f;
	maxTextPosY = 35.0f;
}

ImGuiMenu::~ImGuiMenu()
{

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
 * @brief Get the max text X position bounds for the window
 * @return 
 */
const float ImGuiMenu::GetMaxTextXPos() const
{
	return maxTextPosX;
}

/**
 * @brief Get the max text Y position bounds for the window
 * @return
 */
const float ImGuiMenu::GetMaxTextYPos() const
{
	return maxTextPosY;
}

/**
 * @brief Draw the ImGui window.
 */
void ImGuiMenu::Draw()
{
	//----
	// Window drawing.

	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow();
	}

	// I didn't know I could have multiple ImGui screens at once.
	//ImGui::Begin("Test screen");

	//ImGui::End();


	ImGui::Begin("Game Debugger");

	//----
	// Player
	imGuiPlayerMenu.Draw();

	ImGui::Separator();
	ImGui::Spacing();

	//------
	// Enemy
	//------
	imGuiEnemyMenu.Draw();

	ImGui::Separator();

	//------
	// Screen
	//------
	imGuiScreenMenu.Draw();

	ImGui::Separator();

	//------
	// Mouse
	//------
	imGuiMouseMenu.Draw();

	ImGui::Separator();

	//------
	// Music
	//------
	imGuiMusicMenu.Draw();

	ImGui::Separator();

	//------
	// Controller
	//------
	imGuiControllerMenu.Draw();

	ImGui::Separator();

	//------
	// Timers
	//------
	imGuiTimersMenu.Draw();

	ImGui::End();
}

#endif // _IMGUI_TEST