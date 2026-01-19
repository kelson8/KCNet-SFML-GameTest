#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	static Enemy& getInstance()
	{
		static Enemy instance; // Guaranteed to be destroyed.
		return instance;
	}

	void Init();
	void Spawn();
	void Reset();
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

	// Make the enemies faster.
	bool fastEnemies;

	// Make the enemies go down faster.
	bool fastEnemiesFall;
};

