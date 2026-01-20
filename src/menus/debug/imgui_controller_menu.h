#pragma once
#include "menus/IMenuBase.h"

#include "defines.h"

class ImGuiControllerMenu : public IMenuBase
{
#ifdef _IMGUI_TEST
public:
	ImGuiControllerMenu() {}

	void Draw() override;
#endif // _IMGUI_TEST
};

