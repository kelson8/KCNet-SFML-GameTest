#include "imgui_controller_menu.h"

#include <fmt/core.h>

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>
#include <SFML/Graphics.hpp>

void ImGuiControllerMenu::Draw()
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