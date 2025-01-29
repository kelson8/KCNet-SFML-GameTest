#pragma once
#include "pch.h"

class Enemy {

private:
	// Enemy
#ifdef _MOVE_ENEMY_FILE
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	float enemySpeed; // The speed of the enemy
#endif //!_MOVE_ENEMY_FILE

	// Game objects
	// TODO Switch to sprites
	//sf::Sprite
#ifdef _MOVE_ENEMY_FILE
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
#endif //!_MOVE_ENEMY_FILE

public:
    void spawnEnemy();
    void updateEnemies();

	void initEnemies();
};