#pragma once
#include "menus/IMenuBase.h"

#include "defines.h"

class ImGuiPlayerMenu : public IMenuBase
{
#ifdef _IMGUI_TEST
public:
	ImGuiPlayerMenu();

	void Draw() override;

private:
	// Player debug values for modifying the display on the screen.
	float livesPosX;
	float livesPosY;
#endif // _IMGUI_TEST
};

