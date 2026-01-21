#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/**
 * @brief Keycodes I am using in the game so far, putting them here for easier access
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

class WindowManager
{
public:
    static WindowManager& getInstance()
    {
        static WindowManager instance; // Guaranteed to be destroyed.
        return instance;
    }

    void initWindow(unsigned int width, unsigned int height, const std::string& title);
    void pollEvents();
    bool isOpen() const;
    void close();

    //sf::RenderWindow* getWindow(); // To access the window
    sf::RenderWindow& getWindow(); // To access the window

    float GetRandomScreenX();
    float GetRandomScreenY();


private:
    WindowManager();
    ~WindowManager();

    //void InputHandlerLoop();

    WindowManager(const WindowManager&) = delete; // Prevent copying
    WindowManager& operator=(const WindowManager&) = delete; // Prevent assignments

    sf::RenderWindow* window;
};
