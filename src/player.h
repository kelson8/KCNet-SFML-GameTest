#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>

#include "bullet.h"
#include "window_manager.h"
#include "entity.h"





class Player : public Entity
{
public:
	static Player& getInstance()
	{
		static Player instance; // Guaranteed to be destroyed.
		return instance;
	}

	void Draw();

	void FireBullet();

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

	// Bullet for the player
	Bullet m_Bullet;

	int m_PlayerSize;

	int m_PlayerHealth;
	int m_PlayerLives;
	int m_PlayerPoints;

	float m_MoveSpeed;

	bool m_PlayerJumpStatus;

	bool m_FiringBullet;
	bool m_BulletMoving;

	//std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape m_Player;

	sf::Color m_PlayerColor;
};

