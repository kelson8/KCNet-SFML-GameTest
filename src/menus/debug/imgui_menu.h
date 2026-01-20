#pragma once
#include "defines.h"

#include "imgui_screen_menu.h"


class ImGuiMenu
{
#ifdef _IMGUI_TEST
public:
	static ImGuiMenu& getInstance()
	{
		static ImGuiMenu instance; // Guaranteed to be destroyed.
		return instance;
	}

	void Draw();

	const bool GetStatus();
	void SetStatus(bool toggle);

	const float GetMaxTextXPos() const;
	const float GetMaxTextYPos() const;


private:
	// Constructors / Destructors
	ImGuiMenu();
	~ImGuiMenu();


	void ControllerMenu();

	ImGuiScreenMenu imGuiScreenMenu;

	bool showDemoWindow;
	bool showImGuiWindow;

	// Debug variables for game menu, these are for the float sliders to use.
	float livesPosX;
	float livesPosY;

	// The max text position for the debug display editor.
	// Checks if this value is too high for the display.
	float maxTextPosX;
	float maxTextPosY;

	//int timePassed = 0;
	int timePassed;

	// Toggle the random screen size display
	bool showRandomScreenSize;

	// Random X position from the window.
	float randomScreenPosX;

	// Random Y position from the window.
	float randomScreenPosY;


#endif // _IMGUI_TEST
};

