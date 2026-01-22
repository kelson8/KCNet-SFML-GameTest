#pragma once
#include "menus/IMenuBase.h"

#include "defines.h"

#include "util/text_handler.h"

// Hmm, adding this here gives a bunch of errors..
//#include "imgui_menu.h"

class ImGuiScreenMenu : public IMenuBase
{
#ifdef _IMGUI_TEST
public:
	// Constructors / Destructors
	//ImGuiScreenMenu(ImGuiMenu& imGuiMenu);
	ImGuiScreenMenu();
	//~ImGuiScreenMenu();

	void Draw() override;

private:
	//void PauseMenuMainText();
	void SetRandomScreenPos();

	void PositionDebugSlider(float *slider1Value, float *slider2Value, float sliderMinimum,
		const char* headerText, const char* sliderText1, const char* sliderText2) const;

	void PositionDebugButton(TextPositions textPosition, float posX, float posY, const char* buttonLabel);

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

	float m_RoundTextPosX;
	float m_RoundTextPosY;

	float m_ScreenSizeX;
	float m_ScreenSizeY;
#endif // _IMGUI_TEST
};

