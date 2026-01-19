#include "window_manager.h"


#include "defines.h"

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>
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
    sf::Keyboard::Scan Key_W = sf::Keyboard::Scancode::W;
    sf::Keyboard::Scan Key_A = sf::Keyboard::Scancode::A;
    sf::Keyboard::Scan Key_D = sf::Keyboard::Scancode::S;
    sf::Keyboard::Scan Key_S = sf::Keyboard::Scancode::D;
    
    sf::Keyboard::Scan Key_F2 = sf::Keyboard::Scancode::F2;

    sf::Keyboard::Scan Key_Enter = sf::Keyboard::Scancode::Enter;
}

WindowManager::WindowManager() : window(nullptr) 
{
    // Well this just freezes the program..
    //game = &Game::getInstance();
    //game = game->getInstance();
}

WindowManager::~WindowManager()
{
	delete window; // Clean up
}

void WindowManager::initWindow(unsigned int width, unsigned int height, const std::string& title) {
    Defines defines = Defines();
    //window = new sf::RenderWindow(sf::VideoMode({ 1920u, 1080u }), title, sf::Style::Titlebar | sf::Style::Close);
    window = new sf::RenderWindow(sf::VideoMode({ defines.screenWidth, defines.screenHeight }), title, sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(defines.gameFramerate);
    this->window->setVerticalSyncEnabled(defines.vsyncEnabled);

    // Setup ImGui window
#ifdef _IMGUI_TEST

    if (!ImGui::SFML::Init(*window))
        return;

#endif //_IMGUI_TEST
}

void WindowManager::pollEvents() 
{
    Player& player = Player::getInstance();
    ImGuiMenu& imGuiMenu = ImGuiMenu::getInstance();
    Game& game = Game::getInstance();
    Enemy& enemy = Enemy::getInstance();

    while (const std::optional<sf::Event> event = window->pollEvent()) 
    {
        sf::Vector2f playerPos = player.GetPosition();

        //std::cout << "Player position X: " << playerPos.x << " Y: " << playerPos.y << std::endl;

        //if(Game::getInstance().getWindowInitialized())
        //    player.Draw();


#ifdef _IMGUI_TEST
        ImGui::SFML::ProcessEvent(*window, *event);
#endif


        if (event->is<sf::Event::Closed>()) {
            close();
        }
        // Handle other events here, e.g. key presses
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                close();
            }

            //------
            // Move keys
            //------
            
            // TODO Possibly move player movement into player class somehow?
            else if (keyPressed->scancode == KeyCodes::Key_W)
            {
                //player.Move(0.f, -5.0f);
                player.Move(0.f, -player.GetMoveSpeed());
            }

            else if (keyPressed->scancode == KeyCodes::Key_A)
            {
                //player.SetPosition(playerPos.y + player.GetMoveSpeed(), playerPos.y + player.GetMoveSpeed());
                //player.Move(-1.f, 0.f); // Move left
                player.Move(-player.GetMoveSpeed(), 0.f); // Move left
                

                //Game::getInstance().setEndScreen(true);
                //std::cout << "Game end screen set with 'A' key" << std::endl;
            }

            else if (keyPressed->scancode == KeyCodes::Key_S)
            {
                //player.Move(1.f, 0.f); // Move down
                player.Move(player.GetMoveSpeed(), 0.f); // Move down

                
            }

            else if (keyPressed->scancode == KeyCodes::Key_D)
            {
                //player.Move(0.f, 5.0f);
                player.Move(0.f, player.GetMoveSpeed());
            }

            // Test

            //else if (keyPressed->scancode == sf::Keyboard::Scancode::B)
            //{
            //    Game::getInstance().setEndGame(true);
            //    std::cout << "Game ended with 'B' key" << std::endl;
            //}

            // End game key to restart
            // Set the end screen to false
            // Reset enemies
            // Set the players lives back to default.
            else if (keyPressed->scancode == KeyCodes::Key_Enter)
            {
                if (game.getEndScreen())
                {
                    game.setEndScreen(false);
                    enemy.Reset();
                    player.SetLives(Defines::defaultLives);
                }
            }

            //------
            // ImGui keys
            //-------
#ifdef _IMGUI_TEST
            else if (keyPressed->scancode == KeyCodes::Key_F2)
            {
                imGuiMenu.SetStatus(!imGuiMenu.GetStatus());
            }
#endif
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