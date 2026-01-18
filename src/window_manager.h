#pragma once
#include <SFML/Graphics.hpp>
#include <string>

//class Game;

class WindowManager
{
public:
	WindowManager();
	~WindowManager();


    void initWindow(unsigned int width, unsigned int height, const std::string& title);
    void pollEvents();
    bool isOpen() const;
    void close();

    //sf::RenderWindow* getWindow(); // To access the window
    sf::RenderWindow& getWindow(); // To access the window

private:
    sf::RenderWindow* window;

    //Game* game;
};
