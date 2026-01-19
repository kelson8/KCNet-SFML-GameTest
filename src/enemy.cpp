#include "enemy.h"
#include "window_manager.h"

#include "defines.h"

#include "util/random_number_generator.h"
#include "util/timers.h"

// TODO Make a life system, if enough enemies get through it's game over, add a way to attack or something.

Enemy::Enemy()
{
	fastEnemies = false;
	fastEnemiesFall = false;

	m_RandomSpawnPos = 0.0f;

	this->Init();
}

Enemy::~Enemy()
{

}

#ifdef _IMGUI_TEST
/**
 * @brief Get the enemy random spawn position.
 * @return The random spawn position for the enemy.
 */
const float Enemy::GetRandomSpawnPos() const
{
	return m_RandomSpawnPos;
}
#endif // _IMGUI_TEST

/**
 * @brief Setup the enemies variables
 */
void Enemy::Init()
{
	// Set the position, size, and scale.
	this->enemy.setPosition(sf::Vector2f(10.0f, 10.0f));
	this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));

	// Set the fill color, outline color and outline thickness.
	this->enemyColor = sf::Color::Cyan;
	this->enemy.setFillColor(enemyColor);

	// Changing this value spawns in more enemies at once.
	
	if (fastEnemies)
	{
		this->enemySpawnTimerMax = 1.0f;
	}
	else
	{
		this->enemySpawnTimerMax = 20.0f;
	}

	// Set the enemies to fall down faster, pretty much spawning in faster.
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
	RandomNumberGenerator& randomNumberGenerator = RandomNumberGenerator::getInstance();

	// Randomizing between zero and the window size for the X
	// Using static cast, safely turning the value into a float, the random function only takes an int so it has to be
	// converted to an int first then randomize it.


#ifdef ENEMY_RANDOM_SPAWNS
	//float randomSpawnPos = randomNumberGenerator.GenerateRandomNumber(10.0f, 40.0f);
	//this->enemy.setPosition(sf::Vector2f(m_RandomSpawnPos, m_RandomSpawnPos));
	this->enemy.setPosition(
		sf::Vector2f(windowManager.getWindow().getSize().x - this->enemy.getSize().x, 
		0.0f));

#else
	this->enemy.setPosition(sf::Vector2f(
		static_cast<float> (rand() % static_cast<int>(windowManager.getWindow().getSize().x - this->enemy.getSize().x)), 0.0f)
	);

#endif // ENEMY_RANDOM_SPAWNS

	this->enemy.setFillColor(enemyColor);

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
 * 
 * TODO Set this up somewhere, I never did have it setup in my other game test.
 * 
 * This seems to work in my ImGui menu, I wonder if I can use it to setup rounds?
 * Like reset and make the enemies go faster or something.
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
 * @brief Render the enemies.
 * @param target The target window to render to.
 */
void Enemy::Render(sf::RenderTarget& target)
{
	// Draw the enemies
	for (auto& e : this->enemies)
	{
		target.draw(e);
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
	RandomNumberGenerator& randomNumberGenerator = RandomNumberGenerator::getInstance();
	Timers& timers = Timers::getInstance();

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



#ifdef ENEMY_RANDOM_SPAWNS
		// Well this makes a fun effect but the enemies disappear too fast.
		if (timers.SecondPassed())
		{
			m_RandomSpawnPos = randomNumberGenerator.GenerateRandomNumber(5.0f, 20.0f);
		}

		//this->enemies[i].move(sf::Vector2f(randomSpawnPos, enemySpeed));
		//this->enemies[i].move(sf::Vector2f(m_RandomSpawnPos, -m_RandomSpawnPos));
		this->enemies[i].move(sf::Vector2f(5.0f, m_RandomSpawnPos));

#else
		//Change the speed by changing the offsetY
		this->enemies[i].move(sf::Vector2f(0.0f, enemySpeed));
#endif // ENEMY_RANDOM_SPAWNS

		// Delete the enemy if they are past the bottom of the screen.
		if (this->enemies[i].getPosition().y > windowManager.getWindow().getSize().y
			|| this->enemies[i].getPosition().x > windowManager.getWindow().getSize().x)
		{
			this->enemies.erase(this->enemies.begin() + i);

			// Setting the player health? Although why, this must've been for something else.
			// Oh I remember why, if the enemies went off the screen it took the players health down.
			// Hmm...
			// TODO Change this to make the players lives go down if the enemy touches the player.
			//this->health -= 1;
			//std::cout << "Health: " << this->health << std::endl;
		}
	}
}