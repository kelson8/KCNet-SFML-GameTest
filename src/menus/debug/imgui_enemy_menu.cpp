#include "imgui_enemy_menu.h"

#include <fmt/core.h>

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>

#include "enemy.h"

void ImGuiEnemyMenu::Draw()
{
	Enemy& enemy = Enemy::getInstance();
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
}

#endif