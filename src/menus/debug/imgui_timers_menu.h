#pragma once
#include "menus/IMenuBase.h"

#include "defines.h"

class ImGuiTimersMenu : public IMenuBase
{
#ifdef _IMGUI_TEST
public:
	ImGuiTimersMenu();

	void Draw() override;
private:
	int timePassed;
#endif // _IMGUI_TEST
};

