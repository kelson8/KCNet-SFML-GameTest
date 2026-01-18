#include "window_manager.h"

#include "defines.h"

#include "game.h"

// Using this for getters and setters
// https://www.geeksforgeeks.org/cpp/write-getter-and-setter-methods-in-cpp/

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

    // Setup ImGui window
#ifdef _IMGUI_TEST
    ImGui::SFML::Init(*this->window);
#endif //_IMGUI_TEST

    this->window->setFramerateLimit(defines.gameFramerate);
    this->window->setVerticalSyncEnabled(defines.vsyncEnabled);
}

void WindowManager::pollEvents() {
    while (const std::optional<sf::Event> event = window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            close();
        }
        // Handle other events here, e.g. key presses
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                close();
            }

            if (keyPressed->scancode == sf::Keyboard::Scancode::A)
            {
                // Well this just open another window and don't do anything else.
                Game::getInstance().setEndGame(true);
                Game::getInstance().setEndScreen(true);
                //game->setEndGame(true);
                //game->setEndScreen(true);
            }
        }
    }
}

bool WindowManager::isOpen() const {
    return window && window->isOpen();
}

void WindowManager::close() {
    if (window)
        window->close();
}

sf::RenderWindow& WindowManager::getWindow() {
    return *window; // Return a reference to the window
}