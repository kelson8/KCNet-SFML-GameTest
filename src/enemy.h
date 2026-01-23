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


	std::vector<sf::RectangleShape> m_Enemies;
	sf::RectangleShape m_Enemy;

	float m_EnemySpawnTimer;
	float m_EnemySpawnTimerMax;
	int m_MaxEnemies;
	float m_EnemySpeed;

	// Check if the player has been hit
	bool m_PlayerHit;

	// TODO Rename these below booleans.
	// Make the enemies faster.
	bool m_FastEnemies;

	// Make the enemies go down faster.
	bool m_FastEnemiesFall;

	// Random spawn position for the enemies.
	float m_RandomSpawnPos;

	// The default X position for the enemy to move.
	float m_DefaultEnemyXMovePos;

	// The size of the m_Enemy
	float m_EnemySize;

	// The scale of the m_Enemy
	float m_EnemyScale;

	// Set the m_Enemy color
	sf::Color m_EnemyColor;
};

