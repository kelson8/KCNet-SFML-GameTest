#include "imgui_controller_menu.h"

#include <fmt/core.h>

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/Graphics.hpp>

void ImGuiControllerMenu::Draw()
{
	// This didn't seem to go to anything.
	float controllerRHatPos = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::R);

	// DPad Left/Right
	// If this is -100, the DPAD is left.
	// If this is +100, The DPAD is right.
	float controllerDpadLeftRight = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);

	// DPad Up/Down
	// If this is -100, the DPAD is down.
	// If this is +100, The DPAD is up.
	float controllerDpadUpDown = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY);

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
		if (!sf::Joystick::isConnected(0))
		{
			ImGui::Text("There is no controller connected");
			return;
		}

		ImGui::Text("Displays if buttons are being pressed on a controller.");
		
		// Display if the controller is connected or not.
		//if (!sf::Joystick::isConnected(0))
		//{
			//ImGui::Text("There is no controller connected");
		//}
		//else 
		//{
			//ImGui::Text("Controller is connected");
		//}

		//ImGui::Text(fmt::format("Controller Dpad left/right pos: {}", controllerDpadLeftRight).c_str());

		// Dpad Left button
		if (controllerDpadLeftRight == -100)
		{
			ImGui::Text("Controller Left DPad button pressed");
		}

		// Dpad Right button
		else if (controllerDpadLeftRight == 100)
		{
			ImGui::Text("Controller Right DPad button pressed");
		}

		// Dpad down button
		if (controllerDpadUpDown == -100)
		{
			ImGui::Text("Controller Down DPad button pressed");
		} 

		// Dpad up button
		else if (controllerDpadUpDown == 100)
		{
			ImGui::Text("Controller Up DPad button pressed");
		}

		// LT on controller
		// TODO Figure the values out for these
		//if (controllerBumpers <= -101 && controllerBumpers <= -1 )
		//{
		//	ImGui::Text("Controller Left bumper pressed");
		//	ImGui::Text(fmt::format("Value: {}", controllerBumpers).c_str());
		//}

		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Text("0 to 100 is L2, 0 to -100 is R2");
		ImGui::Text(fmt::format("Controller Bumpers: {}", controllerBumpers).c_str());
		ImGui::Spacing();

		ImGui::Text(fmt::format("Controller R position: {}", controllerRHatPos).c_str());
		ImGui::Spacing();

		ImGui::Text(fmt::format("Controller Dpad up/down pos: {}", controllerDpadUpDown).c_str());
		ImGui::Spacing();

		ImGui::Text(fmt::format("Right stick X position: {}", controllerRightStickX).c_str());
		ImGui::Text(fmt::format("Right stick Y position: {}", controllerRightStickY).c_str());
		ImGui::Spacing();

		ImGui::Text(fmt::format("Left stick X position: {}", controllerLeftStickX).c_str());
		ImGui::Text(fmt::format("Left stick Y position: {}", controllerLeftStickY).c_str());

		//ImGui::Spacing();

		//ImGui::Text("0 to 100 is L2, 0 to -100 is R2");
		//ImGui::Text(fmt::format("Controller Bumpers: {}", controllerBumpers).c_str());
	}
}

#endif // _IMGUI_TEST