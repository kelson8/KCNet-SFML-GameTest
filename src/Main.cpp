#include "Main.h"
#include "util/defines.h"

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


// https://www.youtube.com/watch?v=kxb0GvBNOGU&list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&index=5
// I got the linker and include files fixed for this in Debug and Release

int main()
{
	Defines defines = Defines();

	// About in console
	std::cout << "Welcome to: " << defines.windowTitle << std::endl;
	std::cout << "Version: " << defines.programVersion << std::endl;

	//Window
	sf::RenderWindow window(sf::VideoMode(defines.screenHeight, defines.screenWidth), defines.windowTitle, sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;

	// Game loop
	while (window.isOpen())
	{
		// Event polling
		// While we are getting events from the window, save them in here
		while (window.pollEvent(event))
		{
			switch (event.type)
			{

			// Close the window
			case sf::Event::Closed:
				window.close();
				break;

			// Keys pressed
			case sf::Event::KeyPressed:
				// Close the window using escape.
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				break;
			}
		}

		// Update


		// Render
		// Use this to generate colors:
		// https://www.rapidtables.com/web/color/RGB_Color.html
		// Light blue
		// window.clear(sf::Color(102, 178, 255, 255)); // Clear old frame
		// Gray
		window.clear(sf::Color(64, 64, 64, 255)); // Clear old frame

		// Draw your game


		window.display(); // Tell app that window is done drawing.
	}

	// End of application


}