#pragma once
#include "menus/IMenuBase.h"

#include "defines.h"

class ImGuiEnemyMenu : public IMenuBase
{
#ifdef _IMGUI_TEST
public:
	ImGuiEnemyMenu() : 
		enemyMovePosX(0.0f),
		enemySpeed(0.0f),
		enemySpawnRate(0.0f)
	{}

	void Draw() override;

private:
	float enemyMovePosX;
	float enemySpeed;
	float enemySpawnRate;
	float maxEnemies;
#endif // _IMGUI_TEST
};

