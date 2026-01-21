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

		ImGui::Spacing();
		
		//-----
		// Set X Move pos
		//-----

		ImGui::SliderFloat("Enemy X move pos", &enemyMovePosX, 0.0f, 40.0f);

		if (ImGui::Button("Apply X move pos"))
		{
			enemy.SetDefaultXMovePos(enemyMovePosX);
			fmt::println("New enemy X move pos set to {}", enemyMovePosX);
		}

		if (ImGui::Button("Reset X move pos"))
		{
			enemy.SetDefaultXMovePos(0.0f);
			fmt::println("New enemy X move pos set to default 0.0");
		}

		ImGui::Spacing();

		//-----
		// Set speed
		//-----

		ImGui::SliderFloat("Enemy speed", &enemySpeed, 0.0, 40.0f);

		if (ImGui::Button("Apply speed"))
		{
			enemy.SetSpeed(enemySpeed);
			fmt::println("New enemy speed set to {}", enemySpeed);
		}

		if (ImGui::Button("Reset speed"))
		{
			enemy.SetSpeed(5.0f);
			fmt::println("Enemy speed reset to 5.0");
		}

		ImGui::Spacing();

		//-----
		// Set spawn rate
		// Well, the higher this is the slower the enemies spawn in, I guess that's how this enemy class is designed.
		//-----

		ImGui::SliderFloat("Enemy spawn rate", &enemySpawnRate, 0.0, 40.0f);

		if (ImGui::Button("Apply spawn rate"))
		{
			enemy.SetSpawnRate(enemySpawnRate);
			fmt::println("New enemy spawn rate set to {}", enemySpawnRate);
		}

		if (ImGui::Button("Reset spawn rate"))
		{
			enemy.SetSpawnRate(20.0f);
			fmt::println("Enemy spawn rate reset to 20.0");
		}

		ImGui::Spacing();

		//-----
		// Max enemies
		//-----

		ImGui::SliderFloat("Max enemies", &maxEnemies, 0.0, 40.0f);

		if (ImGui::Button("Apply max enemies"))
		{
			enemy.SetMaxEnemies(maxEnemies);
			fmt::println("New enemy max enemies set to {}", maxEnemies);
		}

		if (ImGui::Button("Reset max enemies"))
		{
			enemy.SetMaxEnemies(10.0f);
			fmt::println("Max enemies reset to 10.0");
		}

		ImGui::Spacing();
	}
}

#endif