#pragma once
#include "defines.h"

#include "menus/IMenuBase.h"

// Menus
#include "imgui_button_menu.h"
#include "imgui_controller_menu.h"
#include "imgui_enemy_menu.h"
#include "imgui_player_menu.h"
#include "imgui_screen_menu.h"
#include "imgui_mouse_menu.h"
#include "imgui_music_menu.h"
#include "imgui_timers_menu.h"
//

class ImGuiMenu : public IMenuBase
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

	// Menu variables
	ImGuiButtonMenu imGuiButtonMenu;
	ImGuiControllerMenu imGuiControllerMenu;
	ImGuiEnemyMenu imGuiEnemyMenu;
	ImGuiPlayerMenu imGuiPlayerMenu;

	ImGuiScreenMenu imGuiScreenMenu;
	ImGuiMouseMenu imGuiMouseMenu;

	ImGuiMusicMenu imGuiMusicMenu;
	ImGuiTimersMenu imGuiTimersMenu;

	bool showDemoWindow;
	bool showImGuiWindow;

	// The max text position for the debug display editor.
	// Checks if this value is too high for the display.
	float maxTextPosX;
	float maxTextPosY;

#endif // _IMGUI_TEST
};

