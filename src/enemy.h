#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "defines.h"

class Enemy
{
public:
	static Enemy& getInstance()
	{
		static Enemy instance; // Guaranteed to be destroyed.
		return instance;
	}

#ifdef _IMGUI_TEST
	const float GetRandomSpawnPos() const;

	const float GetDefaultXMovePos() const;
	void SetDefaultXMovePos(float value);

	const float GetSpeed() const;
	void SetSpeed(float value);

	const float GetSpawnRate() const;
	void SetSpawnRate(float value);


	const float GetMaxEnemies() const;
	void SetMaxEnemies(float value);
#endif // _IMGUI_TEST

	void Init();
	void Spawn();
	void Reset();
	void Render(sf::RenderTarget& target);
	void Update();

private:
	// Constructors / Destructors
	Enemy();
	~Enemy();


	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	float enemySpeed;

	// Check if the player has been hit
	bool m_PlayerHit;

	// TODO Rename these below booleans.
	// Make the enemies faster.
	bool fastEnemies;

	// Make the enemies go down faster.
	bool fastEnemiesFall;

	// Random spawn position for the enemies.
	float m_RandomSpawnPos;

	// The default X position for the enemy to move.
	float m_DefaultEnemyXMovePos;

	// Set the enemy color
	sf::Color enemyColor;
};

