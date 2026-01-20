#pragma once
#include "menus/IMenuBase.h"

#include "defines.h"

class ImGuiScreenMenu : public IMenuBase
{
#ifdef _IMGUI_TEST
public:
	static ImGuiScreenMenu& getInstance()
	{
		static ImGuiScreenMenu instance; // Guaranteed to be destroyed.
		return instance;
	}

	void Draw() override;

private:
	// Constructors / Destructors
	ImGuiScreenMenu();
	//~ImGuiScreenMenu();

	void SetRandomScreenPos();

	// Toggle the random screen size display
	bool showRandomScreenSize;

	// Random X position from the window.
	float randomScreenPosX;

	// Random Y position from the window.
	float randomScreenPosY;

	float m_PauseMenuTextPosX;
	float m_PauseMenuTextPosY;
#endif // _IMGUI_TEST
};

