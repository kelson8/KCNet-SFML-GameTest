#pragma once
#include "menus/IMenuBase.h"

#include "defines.h"

class ImGuiMusicMenu : public IMenuBase
{
#ifdef _IMGUI_TEST
public:
	ImGuiMusicMenu() {}

	void Draw() override;

#endif // _IMGUI_TEST
};

