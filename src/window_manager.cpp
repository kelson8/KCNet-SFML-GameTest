#include "window_manager.h"


#include "defines.h"

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>
#include "util/imgui_setup.h"
#include "menus/debug/imgui_menu.h"
#endif // _IMGUI_TEST

#include "defines.h"

#include "game.h"

#include "player.h"
#include "enemy.h"

#include "util/random_number_generator.h"

#include "util/input_handler.h"


// Using this for getters and setters
// https://www.geeksforgeeks.org/cpp/write-getter-and-setter-methods-in-cpp/

WindowManager::WindowManager() : 
    window(nullptr)
{

}

WindowManager::~WindowManager()
{
    delete window; // Clean up
}

/**
 * @brief Initialize the Window Manager, setup the width and height, along with the title.
 * 
 * @param width The width for the window.
 * @param height The height for the window.
 * @param title The window title.
 */
void WindowManager::initWindow(unsigned int width, unsigned int height, const std::string& title) {
    Defines defines = Defines::getInstance();
#ifdef _IMGUI_TEST
    ImGuiSetup& imGuiSetup = ImGuiSetup::getInstance();
#endif // _IMGUI_TEST

    window = new sf::RenderWindow(sf::VideoMode({ width, height }), title, sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(defines.gameFramerate);
    this->window->setVerticalSyncEnabled(defines.vsyncEnabled);

    
#ifdef _IMGUI_TEST
    // Setup ImGui window
    imGuiSetup.InitImGui(window);

    if (imGuiSetup.IsInitialized())
    {
        fmt::println("ImGui has been initialized.");
    }
    else 
    {
        fmt::println("ImGui couldn't be initialized! Debug system has been disabled.");
    }

#endif //_IMGUI_TEST
}

/**
 * @brief Poll the events that run every frame in game.
 * 
 * This handles operations like checking which key is being pressed.
 * 
 * This also processes events, and ImGui events if enabled.
 */
void WindowManager::pollEvents() 
{
    InputHandler::getInstance().Run();
}

/**
 * @brief Check if the window is open
 * @return If the window is open
 */
bool WindowManager::isOpen() const {
    return window && window->isOpen();
}

/**
 * @brief Close the window
 */
void WindowManager::close() {
    if (window)
        window->close();
}

/**
 * @brief Get the current window
 * TODO Figure out how to make this const, add different option to set window options later.
 * 
 * @return A reference to the window.
 */
//const sf::RenderWindow& WindowManager::getWindow() {
sf::RenderWindow& WindowManager::getWindow() {
    return *window;
}

/**
 * @brief Get a random X position from the max screen width.
 * @return 
 */
float WindowManager::GetRandomScreenX()
{
    RandomNumberGenerator& randomNumberGenerator = RandomNumberGenerator::getInstance();

    // TODO Make this into float? It is an int but it should be fine.
    return randomNumberGenerator.GenerateRandomNumber(0, window->getSize().x);
}

/**
 * @brief Get a random Y position from the max screen height.
 * @return
 */
float WindowManager::GetRandomScreenY()
{
    RandomNumberGenerator& randomNumberGenerator = RandomNumberGenerator::getInstance();

    // TODO Make this into float? It is an int but it should be fine.
    return randomNumberGenerator.GenerateRandomNumber(0, window->getSize().y);
}