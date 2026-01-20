#pragma once
#include "menus/IMenuBase.h"

#include "defines.h"

class ImGuiMouseMenu : public IMenuBase
{
#ifdef _IMGUI_TEST
public:
	ImGuiMouseMenu() {}

	void Draw() override;
#endif // _IMGUI_TEST
};

