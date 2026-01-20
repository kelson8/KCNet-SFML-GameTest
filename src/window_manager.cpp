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


// Using this for getters and setters
// https://www.geeksforgeeks.org/cpp/write-getter-and-setter-methods-in-cpp/

// 


/**
 * @brief Keycodes I am using in the game so far, putting them here for easier access
 * These shouldn't need accessed outside this file.
 * 
 * If these need accessed elsewhere, move into the window_manager.h header.
 */
namespace KeyCodes
{
    const sf::Keyboard::Key Key_W = sf::Keyboard::Key::W;
    const sf::Keyboard::Key Key_A = sf::Keyboard::Key::A;
    const sf::Keyboard::Key Key_D = sf::Keyboard::Key::S;
    const sf::Keyboard::Key Key_S = sf::Keyboard::Key::D;

    const sf::Keyboard::Key Key_B = sf::Keyboard::Key::B;
    
    const sf::Keyboard::Key Key_F2 = sf::Keyboard::Key::F2;
    const sf::Keyboard::Key Key_F4 = sf::Keyboard::Key::F4;

    const sf::Keyboard::Key Key_Enter = sf::Keyboard::Key::Enter;
    const sf::Keyboard::Key Key_Escape = sf::Keyboard::Key::Escape;    
}

WindowManager::WindowManager() : window(nullptr) 
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
    Defines defines = Defines();
    ImGuiSetup& imGuiSetup = ImGuiSetup::getInstance();

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
    Player& player = Player::getInstance();
    ImGuiMenu& imGuiMenu = ImGuiMenu::getInstance();
    Game& game = Game::getInstance();
    Enemy& enemy = Enemy::getInstance();

    while (const std::optional<sf::Event> event = window->pollEvent()) 
    {
#ifdef _IMGUI_TEST
        ImGui::SFML::ProcessEvent(*window, *event);
#endif // _IMGUI_TEST

        if (event->is<sf::Event::Closed>()) {
            close();
        }

        // Handle other events here, e.g. key presses
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

            // I figured out the switch statement for this! I had to change the settings
            // For my key handling, and switch from keyPressed->scancode to keyPressed-Code.
            switch (keyPressed->code)
            {
                //------
                // Pause the game
                //------

                case KeyCodes::Key_Escape:
                    game.setPaused(!game.getPaused());
                    break;

                //------
                // Move keys
                // These check if the game is paused, and if the end screen is shown.
                // Otherwise it doesn't update the values.
                //------

                // Move Up
                case KeyCodes::Key_W:
                    if (game.getPaused() || game.getEndScreen()) return;
                    player.Move(0.f, -player.GetMoveSpeed());
                    break;

                // Move Down
                case KeyCodes::Key_S:
                    if (game.getPaused() || game.getEndScreen()) return;
                    player.Move(player.GetMoveSpeed(), 0.f); // Move down
                    break;

                // Move Left
                case KeyCodes::Key_A:
                    if (game.getPaused() || game.getEndScreen()) return;
                    player.Move(-player.GetMoveSpeed(), 0.f); // Move left
                    break;

                // Move right
                case KeyCodes::Key_D:
                    break;

                
                // If the player is on the end screen, reset the game.
                case KeyCodes::Key_Enter:
                    if (game.getEndScreen())
                    {
                        game.setEndScreen(false);
                        enemy.Reset();
                        player.SetLives(Defines::defaultLives);
                    }
                    break;

                //------
                // Debug Keys
                //------
                
                case KeyCodes::Key_B:
                    
                    // Game::getInstance().setEndGame(true);
                    // std::cout << "Game ended with 'B' key" << std::endl;
                    break;

                // ImGui Key
#ifdef _IMGUI_TEST
                case KeyCodes::Key_F2:
                    imGuiMenu.SetStatus(!imGuiMenu.GetStatus());
                    break;
#endif // _IMGUI_TEST

                //------
                // Close the game
                //------

                case KeyCodes::Key_F4:
                    close();
                    break;
            }
        }
    }
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