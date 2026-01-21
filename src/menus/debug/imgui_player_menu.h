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

	// If the god mode checkbox is active.
	bool godModeActive;
	// This stops the loop from processing this part if god mode is turned on or off.
	bool godModeActiveFlag;
#endif // _IMGUI_TEST
};

