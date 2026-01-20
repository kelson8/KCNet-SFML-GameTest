#pragma once
#include "defines.h"

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


private:
	// Constructors / Destructors
	ImGuiMenu();
	~ImGuiMenu();

	void SetRandomScreenPos();

	void ScreenMenu();

	void ControllerMenu();

	bool showDemoWindow;
	bool showImGuiWindow;

	// Toggle the random screen size display
	bool showRandomScreenSize;

	// Random X position from the window.
	float randomScreenPosX;

	// Random Y position from the window.
	float randomScreenPosY;


#endif // _IMGUI_TEST
};

