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

	bool showDemoWindow;
	bool showImGuiWindow;


#endif // _IMGUI_TEST
};

