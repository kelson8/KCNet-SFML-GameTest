#pragma once
#include "pch.h"

class ImGuiSetup
{
#ifdef _IMGUI_TEST
public:
	static ImGuiSetup& getInstance()
	{
		static ImGuiSetup instance; // Guaranteed to be destroyed.
		return instance;
	}

	const bool IsInitialized() const;
	void InitImGui(sf::RenderWindow* window);

private:
	// Constructors / Destructors
	ImGuiSetup();
	//~ImGuiSetup();

	bool m_ImGuiInitialized;
#endif //_IMGUI_TEST
};

