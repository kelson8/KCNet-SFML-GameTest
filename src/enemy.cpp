#include "enemy.h"
#include "window_manager.h"

#include "defines.h"

// TODO Fix this, copied from my other game test
// TODO Implement this into my Game class later.

Enemy::Enemy()
{
	fastEnemies = false;
	fastEnemiesFall = false;

	this->Init();
}

Enemy::~Enemy()
{

}


/**
 * @brief Setup the enemies variables
 */
void Enemy::Init()
{
	// Set the enemies to be fast
	if (fastEnemies)
	{
		this->enemySpawnTimerMax = 1.0f;
	}
	else
	{
		this->enemySpawnTimerMax = 20.0f;
	}

	// Set the enemy speed
	if (fastEnemiesFall)
	{
		// Fast enemies
		this->enemySpeed = 25.0f;
	}
	else
	{
		// Normal speed
		this->enemySpeed = 5.0f;
	}

	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10.0f;
}

/**
 * @brief Spawn the enemies and set their colors and positions.
 * Sets a random position
 * Sets a random color
 * Adds enemy to the vector.
 */
void Enemy::Spawn()
{
	WindowManager& windowManager = WindowManager::getInstance();

	// Randomizing between zero and the window size for the X
	// Using static cast, safely turning the value into a float, the random function only takes an int so it has to be
	// converted to an int first then randomize it.

	this->enemy.setPosition(sf::Vector2f(
		static_cast<float> (rand() % static_cast<int>(windowManager.getWindow().getSize().x - this->enemy.getSize().x)), 0.0f)
		//static_cast<float> (rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
	);

	this->enemy.setFillColor(sf::Color::Green);

	// Spawn the enemy
	this->enemies.push_back(this->enemy);

	// Remove enemies at the end of the screen.
}

//void Game::playEnemySfx()

#ifdef _ENEMY_SOUNDS_TEST
sf::SoundBuffer* Game::playEnemySfx()
{
	Defines defines = Defines();

	sf::SoundBuffer* buffer = &sf::SoundBuffer();
	if (!buffer->loadFromFile(defines.enemyHitSound))
	{
		std::cerr << "Could not load the enemy sound" << std::endl;
		delete buffer;
		return nullptr; // Handle error
	}

	return buffer;

	// Play the sound
	//sf::Sound sound(buffer);
	//sound.play();
}
#endif //_ENEMY_SOUNDS_TEST

/**
 * @brief Clear the enemies if the game ends or something.
 */
void Enemy::Reset()
{
	bool deleted = false;

	// If !deleted
	//for (size_t i = 0; i < this->enemies.size() && !deleted; i++)
	for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
	{
		// Delete the enemy
		// Setting deleted to true cancels the loop.
		deleted = true;
		// TODO Test this.
		this->enemies.clear();
		// this->enemies.erase(this->enemies.);

	}
}

/**
 * @brief Update the enemy spawn timer and spawns enemies.
 * When the total amount of enemies is smaller then the maximum.
 * Moves the enemies downwards.
 * Removes the enemies at the edge of the screen.
 */
void Enemy::Update()
{
	WindowManager& windowManager = WindowManager::getInstance();

	// TODO Fix this
#ifdef _ENEMY_SOUNDS_TEST
	// Play sound effect
	sf::Sound enemySfx(*this->playEnemySfx());
	enemySfx.play();
#endif //_ENEMY_SOUNDS_TEST

	Defines defines = Defines();
	Enemy enemy = Enemy();

	// Updating the timer.
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{

			this->Spawn();

			this->enemySpawnTimer = 0.0f;
		}
		else
		{
			this->enemySpawnTimer += 1.0f;
		}
	}

	// Moving and updating the enemies, check if they are below the screen
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		// Change the speed by changing the offsetY
		this->enemies[i].move(sf::Vector2f(0.0f, enemySpeed));

		// Delete the enemy if they are past the bottom of the screen.
		if (this->enemies[i].getPosition().y > windowManager.getWindow().getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);

			// Setting the player health? Although why, this must've been for something else.
			//this->health -= 1;
			//std::cout << "Health: " << this->health << std::endl;
		}
	}
}