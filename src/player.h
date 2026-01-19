#pragma once

#include "window_manager.h"

#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>



class Player
{
public:
	static Player& getInstance()
	{
		static Player instance; // Guaranteed to be destroyed.
		return instance;
	}

	void Draw();

	sf::Vector2f GetPosition();
	void SetPosition(float x, float y);

	void Move(float x, float y);

	const float GetMoveSpeed() const;
	void SetMoveSpeed(float speed);


private:
	// Constructors / Destructors
	Player();
	~Player();

	void Setup();

	int playerHealth;
	int playerLives;

	float moveSpeed;

	bool playerJumpStatus;

	//std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape player;
};

