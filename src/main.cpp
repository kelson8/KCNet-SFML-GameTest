#include <SFML/Graphics.hpp>

#include "defines.h"
#include "game.h"

int main()
{
    //auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    //window.setFramerateLimit(144);

    //while (window.isOpen())
    //{
    //    while (const std::optional event = window.pollEvent())
    //    {
    //        if (event->is<sf::Event::Closed>())
    //        {
    //            window.close();
    //        }
    //    }

    //    //window.clear();
    //    // Change the window background color
    //    window.clear(sf::Color(64, 64, 64, 255)); // Clear old frame
    //    window.display();
    //}


    // Init srand for random.
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init Game engine
    Game& game = Game::getInstance();

    // Game loop
    // Moved into Game class.
    game.Run();
}
