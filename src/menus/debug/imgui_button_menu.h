#pragma once
#include "menus/IMenuBase.h"

#include "defines.h"
#include "util/button_util.h"

class ImGuiButtonMenu : public IMenuBase
{
#ifdef _IMGUI_TEST
public:
	ImGuiButtonMenu();

	void Draw() override;

private:
	void PositionDebugSlider(float* slider1Value, float* slider2Value, float sliderMinimum,
		const char* headerText, const char* sliderText1, const char* sliderText2) const;

	void PositionDebugButton(ButtonPositions buttonPosition, float posX, float posY,
		float sizeX, float sizeY, const char* buttonLabel);

	// Button options

	// Button positions
	float m_Button1PosX;
	float m_Button1PosY;

	float m_Button2PosX;
	float m_Button2PosY;

	// Button sizes
	float m_Button1SizeX;
	float m_Button1SizeY;

	// Screen size
	float m_ScreenSizeX;
	float m_ScreenSizeY;
#endif // _IMGUI_TEST
};

