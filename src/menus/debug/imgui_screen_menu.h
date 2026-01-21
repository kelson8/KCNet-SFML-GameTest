#pragma once
#include "menus/IMenuBase.h"

#include "defines.h"

class ImGuiScreenMenu : public IMenuBase
{
#ifdef _IMGUI_TEST
public:
	// Constructors / Destructors
	ImGuiScreenMenu();
	//~ImGuiScreenMenu();

	void Draw() override;

private:
	void SetRandomScreenPos();

	// Toggle the random screen size display
	bool showRandomScreenSize;

	// Random X position from the window.
	float randomScreenPosX;

	// Random Y position from the window.
	float randomScreenPosY;

	float m_PauseMenuTextPosX;
	float m_PauseMenuTextPosY;

	float m_PauseMenuInfoTextPosX;
	float m_PauseMenuInfoTextPosY;
#endif // _IMGUI_TEST
};

