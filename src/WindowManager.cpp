#include "WindowManager.h"

// TODO Move all window management into this class.

// This is incomplete, not sure how to do it yet.

#ifdef _MOVE_WINDOW_FILE

WindowManager::WindowManager()
{
	this->window = nullptr;

	this->initWindow();
}

WindowManager::~WindowManager()
{
	// Delete the window
	delete this->window;
}

/// <summary>
/// Create the window
/// </summary>
void WindowManager::initWindow()
{
	Defines defines = Defines();

	this->videoMode.height = defines.screenHeight;
	this->videoMode.width = defines.screenWidth;

	//this->videoMode.getDesktopMode();

	this->window = new sf::RenderWindow(this->videoMode, defines.windowTitle, sf::Style::Titlebar | sf::Style::Close);

	// Setup ImGui window
#ifdef _IMGUI_TEST
	ImGui::SFML::Init(*this->window);
#endif //_IMGUI_TEST

	this->window->setFramerateLimit(defines.gameFramerate);
}

/// <summary>
/// Get the window
/// </summary>
/// <returns></returns>
const sf::RenderWindow* WindowManager::getWindow() const
{
	return this->window;
}

/// <summary>
/// Check if the window is running
/// TODO Fix this, it says Access violation reading location?
/// </summary>
/// <returns></returns>
const bool WindowManager::running() const
{
	return this->window->isOpen();
}

#endif //_MOVE_WINDOW_FILE