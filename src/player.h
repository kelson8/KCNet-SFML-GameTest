#pragma once

#include "window_manager.h"

#include "entity.h"

#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>



class Player : public Entity
{
public:
	static Player& getInstance()
	{
		static Player instance; // Guaranteed to be destroyed.
		return instance;
	}

	void Draw();

	void Respawn();
	void ResetLives();

	sf::Vector2f GetPosition();
	void SetPosition(float x, float y);

	void Move(float x, float y);

	const float GetMoveSpeed() const;
	void SetMoveSpeed(float speed);

	const int GetLives() const;
	const bool HasLives() const;
	void SetLives(int lives);

	const int GetPoints() const;
	void SetPoints(int points);

	const sf::RectangleShape GetPlayer() const;

	// You can now use the inherited functions
	void EnableGodMode() {
		SetGodMode(true); // Set god mode to true
	}

	void DisableGodMode() {
		SetGodMode(false); // Set god mode to false
	}

	bool IsInvincible() const {
		return HasGodMode(); // Check if player is invincible
	}

private:
	// Constructors / Destructors
	Player();
	~Player();

	void Setup();

	int playerHealth;
	int playerLives;
	int playerPoints;

	float moveSpeed;

	bool playerJumpStatus;

	//std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape player;
};

