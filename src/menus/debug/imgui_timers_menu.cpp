#include "imgui_timers_menu.h"

#include <fmt/core.h>

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>

#include "util/timers.h"

ImGuiTimersMenu::ImGuiTimersMenu()
{
	timePassed = 0;
}

/**
 * @brief Draw the timer debug menu.
 */
void ImGuiTimersMenu::Draw()
{
	Timers& timers = Timers::getInstance();

	if (ImGui::CollapsingHeader("Timers"))
	{
		ImGui::Text("Game timer value in seconds: ");
		ImGui::Text(fmt::format("{}", timers.GetElapsedTime()).c_str());

		if (ImGui::Button("Start timer"))
		{
			timers.StartTimer();
		}

		if (ImGui::Button("Stop timer"))
		{
			timers.StopTimer();
		}

		//
		// Display the seconds passed since game start with ImGui open

		// Misc variable, this keeps the time passed variable updated when ImGui is being drawn.
		//if (timers.SecondPassed())
		//{
		//	timePassed++;
		//}

		// This is no longer needed, I now have getters and setters on the Timers class.
		//ImGui::Text(fmt::format("Seconds passed since ImGui has been open: {}", timePassed).c_str());
	}
}

#endif // _IMGUI_TEST