#pragma once
#include "menus/IMenuBase.h"

#include "defines.h"

class ImGuiEnemyMenu : public IMenuBase
{
#ifdef _IMGUI_TEST
public:
	ImGuiEnemyMenu() {}

	void Draw() override;
#endif // _IMGUI_TEST
};

