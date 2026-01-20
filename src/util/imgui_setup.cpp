#include "imgui_setup.h"

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>
#include "menus/debug/imgui_menu.h"
#endif // _IMGUI_TEST

#ifdef _IMGUI_TEST

ImGuiSetup::ImGuiSetup()
{
	m_ImGuiInitialized = false;
}

/**
 * @brief Check if ImGui is initialized.
 * @return If ImGui init has been run and this is initialized.
 */
const bool ImGuiSetup::IsInitialized() const
{
	return m_ImGuiInitialized;
}

/**
 * @brief Init ImGui, exit out of function if it doesn't run.
 * @param window 
 */
void ImGuiSetup::InitImGui(sf::RenderWindow* window)
{
	if (!ImGui::SFML::Init(*window))
	{
		fmt::println("ImGui init failed! Disabling");
		m_ImGuiInitialized = false;
		return;
	}

	m_ImGuiInitialized = true;

	// Setup ImGui style color to dark mode.
	ImGui::StyleColorsDark();
}

#endif // _IMGUI_TEST