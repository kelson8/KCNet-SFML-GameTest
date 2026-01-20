#include "imgui_menu.h"

#include <fmt/core.h>

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>

// Menus
#include "imgui_screen_menu.h"
//

#include "player.h"
#include "entity.h"
#include "window_manager.h"
#include "game.h"

#include "enemy.h"

#include "util/text_handler.h"
#include "util/mouse_util.h"
#include "util/music_util.h"
#include "util/timers.h"

ImGuiMenu::ImGuiMenu()
{
	showDemoWindow = false;
	showImGuiWindow = false;

	showRandomScreenSize = false;

	randomScreenPosX = 0;
	randomScreenPosY = 0;

	livesPosX = 0.0f;
	livesPosY = 0.0f;

	maxTextPosX = 100.0f;
	maxTextPosY = 35.0f;

	timePassed = 0;
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
	// Variables

	WindowManager& windowManager = WindowManager::getInstance();
	Player& player = Player::getInstance();
	Entity& entity = Entity::getInstance();
	Game& game = Game::getInstance();
	Enemy& enemy = Enemy::getInstance();

	MouseUtil& mouseUtil = MouseUtil::getInstance();
	TextHandler& textHandler = TextHandler::getInstance();
	MusicUtil& musicUtil = MusicUtil::getInstance();
	Timers& timers = Timers::getInstance();

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

	// Misc variable, this keeps the time passed variable updated when ImGui is being drawn.
	// TODO Make this get value from the Game loop instead of when ImGui is being drawn.
	if (timers.SecondPassed())
	{
		timePassed++;
	}

	//----
	// Player
	if(ImGui::CollapsingHeader("Player info"))
	{
		ImGui::Text(fmt::format("Position:").c_str());
		ImGui::Text(fmt::format("X: {}", playerPosX).c_str());
		ImGui::Text(fmt::format("Y: {}", playerPosY).c_str());

		
		//-----
		// Check if player is out of bounds, I made a new function for this
		//-----
		if(!entity.IsInBounds(player.GetPlayer()))
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
			//ImGui::SliderFloat("Lives Text Y", &ImGuiDebug::livesPosY, 0.0f, screenSizeY - 30);
			ImGui::SliderFloat("Lives Text Y", &livesPosY, 0.0f, 
				screenSizeY - maxTextPosY);
			
			if (ImGui::Button("Set Lives Position"))
			{
				textHandler.SetLivesTextPos(livesPosX, livesPosY);
			}

			ImGui::Text("Current lives: {}", player.GetLives());
		}
	}

	ImGui::Separator();

	//------
	// Enemy
	//------

	if (ImGui::CollapsingHeader("Enemy Info"))
	{
		if (ImGui::Button("Reset Enemies"))
		{
			enemy.Reset();
		}

		if (ImGui::Button("Spawn Enemies"))
		{
			enemy.Spawn();
		}

		ImGui::Text(fmt::format("Random Spawn Position: {}", enemy.GetRandomSpawnPos()).c_str());
	}

	ImGui::Separator();

	//------
	// Screen
	//------
	//this->ScreenMenu();
	imGuiScreenMenu.Draw();

	ImGui::Separator();

	//------
	// Mouse
	//------
	if (ImGui::CollapsingHeader("Mouse Info"))
	{
		ImGui::Text("Mouse position on screen: ");

		ImGui::Text("Relative to window: ");
		ImGui::Text(fmt::format("X: {}", mouseUtil.getMousePosWindow().x).c_str());
		ImGui::Text(fmt::format("Y: {}", mouseUtil.getMousePosWindow().y).c_str());

		ImGui::Text("Relative to view: ");
		ImGui::Text(fmt::format("X: {}", mouseUtil.getMousePosView().x).c_str());
		ImGui::Text(fmt::format("Y: {}", mouseUtil.getMousePosView().y).c_str());
	}

	ImGui::Separator();

	//------
	// Music
	//------
	if (ImGui::CollapsingHeader("Music Info"))
	{
		ImGui::Text("Run tests for the game music");
		if (ImGui::Button("Game music test"))
		{
			fmt::println("Music volume: {}", musicUtil.GetMusicInfo()->getVolume());
			// fmt cannot display this value.
			//fmt::println("Music status: {}", musicUtil.GetMusicInfo()->getStatus());
			
			fmt::println("Is the track looping: {}", musicUtil.GetMusicInfo()->isLooping());
		}

		if (ImGui::Button("Start game music"))
		{
			musicUtil.SetMusicInfo(true, false, true);
		}

		if (ImGui::Button("Stop game music"))
		{
			musicUtil.SetMusicInfo(false, true, false);
		}
	}

	ImGui::Separator();

	//------
	// Controller
	//------
	this->ControllerMenu();

	
	//
	// Display the seconds passed since game start with ImGui open
	//ImGui::Text(fmt::format("Seconds passed since game start (ImGui was open): {}", ImGuiDebug::timePassed).c_str());
	ImGui::Text(fmt::format("Seconds passed since ImGui has been open: {}", timePassed).c_str());

	ImGui::End();
}

//----------
// Menus
// TODO Move these into separate menu files later.
//----------


void ImGuiMenu::ControllerMenu()
{
	// These don't seem to go to anything.
	//float controllerXHatPos = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);
	//float controllerRHatPos = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R);
	//float controllerPovXPos = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);
	//float controllerPovYPos = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY);
	
	// Right stick up/down
	float controllerRightStickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::V);
	// Right stick left/right
	float controllerRightStickX = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::U);

	// Left stick up/down
	float controllerLeftStickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
	// Left stick left/right
	float controllerLeftStickX = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);

	// 0 to 100 is L2 on Xbox controller.
	// 0 to -100 is R2 on Xbox controller.
	float controllerBumpers = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z);

	if (ImGui::CollapsingHeader("Controller Menu"))
	{
		//ImGui::Text(fmt::format("Controller X Hat position: {}", controllerXHatPos).c_str());
		//ImGui::Text(fmt::format("Controller R position: {}", controllerRHatPos).c_str());
		//ImGui::Text(fmt::format("Controller X Pov position: {}", controllerPovXPos).c_str());
		//ImGui::Text(fmt::format("Controller Y Pov position: {}", controllerPovYPos).c_str());

		ImGui::Text(fmt::format("Right stick X position: {}", controllerRightStickX).c_str());
		ImGui::Text(fmt::format("Right stick Y position: {}", controllerRightStickY).c_str());

		ImGui::Spacing();

		ImGui::Text(fmt::format("Left stick X position: {}", controllerLeftStickX).c_str());
		ImGui::Text(fmt::format("Left stick Y position: {}", controllerLeftStickY).c_str());

		ImGui::Spacing();

		ImGui::Text("0 to 100 is L2, 0 to -100 is R2");
		ImGui::Text(fmt::format("Controller Bumpers: {}", controllerBumpers).c_str());
	}
}


#endif // _IMGUI_TEST