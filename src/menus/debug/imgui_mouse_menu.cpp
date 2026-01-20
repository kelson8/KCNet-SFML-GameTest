#include "imgui_mouse_menu.h"

#include <fmt/core.h>

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>

#include "util/mouse_util.h"

void ImGuiMouseMenu::Draw()
{
	MouseUtil& mouseUtil = MouseUtil::getInstance();
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
}

#endif // _IMGUI_TEST