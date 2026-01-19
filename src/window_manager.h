#pragma once
#include <SFML/Graphics.hpp>
#include <string>

//class Game;

class WindowManager
{
public:
    // TODO Fix this....
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

private:
    WindowManager();
    ~WindowManager();

    WindowManager(const WindowManager&) = delete; // Prevent copying
    WindowManager& operator=(const WindowManager&) = delete; // Prevent assignments

    sf::RenderWindow* window;

    //Game* game;
};
