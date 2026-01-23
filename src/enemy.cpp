#include "enemy.h"
#include "window_manager.h"

#include <fmt/core.h>

#include "defines.h"

#include "entity.h"
#include "player.h"
#include "game.h"

#include "util/random_number_generator.h"
#include "util/timers.h"



// TODO Work on the life system, sometimes the player gets hit
// more then once from a single enemy, and sometimes the hit doesn't register.

// TODO Add a way to attack or something.

Enemy::Enemy()
{
	// Set the fast enemy variables
	m_FastEnemies = false;
	m_FastEnemiesFall = false;

	m_RandomSpawnPos = 0.0f;

	m_DefaultEnemyXMovePos = 0.0f;
	
	// Set the enemy size and scale
	m_EnemySize = 100.0f;
	m_EnemyScale = 0.5f;

	// Set the enemy color
	m_EnemyColor = sf::Color::Cyan;

	Init();
}

Enemy::~Enemy()
{

}

/**
 * @brief Setup the enemies variables
 */
void Enemy::Init()
{
	// Set the position, size, and scale.
	m_Enemy.setPosition(sf::Vector2f(10.0f, 10.0f));
	// For now these use the same values, another value can be added to change the X and Y.
	m_Enemy.setSize(sf::Vector2f(m_EnemySize, m_EnemySize));
	m_Enemy.setScale(sf::Vector2f(m_EnemyScale, m_EnemyScale));

	// Set the fill color, outline color and outline thickness.
	m_Enemy.setFillColor(m_EnemyColor);

	// Changing this value spawns in more enemies at once.
	
	if (m_FastEnemies)
	{
		m_EnemySpawnTimerMax = 1.0f;
	}
	else
	{
		m_EnemySpawnTimerMax = 20.0f;
	}

	// Set the enemies to fall down faster, pretty much spawning in faster.
	if (m_FastEnemiesFall)
	{
		// Fast enemies
		m_EnemySpeed = 25.0f;
	}
	else
	{
		// Normal speed
		m_EnemySpeed = 5.0f;
	}

	m_EnemySpawnTimer = m_EnemySpawnTimerMax;
	m_MaxEnemies = 10.0f;

	m_PlayerHit = false;
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
	//m_Enemy.setPosition(sf::Vector2f(m_RandomSpawnPos, m_RandomSpawnPos));
	m_Enemy.setPosition(
		sf::Vector2f(windowManager.getWindow().getSize().x - m_Enemy.getSize().x,
		0.0f));

#else
	m_Enemy.setPosition(sf::Vector2f(
		static_cast<float> (rand() % static_cast<int>(windowManager.getWindow().getSize().x - m_Enemy.getSize().x)), 0.0f)
	);

#endif // ENEMY_RANDOM_SPAWNS

	m_Enemy.setFillColor(m_EnemyColor);

	// Spawn the enemy
	m_Enemies.push_back(m_Enemy);

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
 * This seems to work in my ImGui menu.
 */
void Enemy::Reset()
{
	bool deleted = false;

	// If !deleted
	//for (size_t i = 0; i < m_Enemies.size() && !deleted; i++)
	for (size_t i = 0; i < m_Enemies.size() && deleted == false; i++)
	{
		// Delete the m_Enemy
		// Setting deleted to true cancels the loop.
		deleted = true;
		m_Enemies.clear();
	}
}

/**
 * @brief Render the enemies.
 * @param target The target window to render to.
 */
void Enemy::Render(sf::RenderTarget& target)
{
	// Draw the enemies
	for (auto& e : m_Enemies)
	{
		target.draw(e);
	}
}

/**
 * @brief Update the m_Enemy spawn timer and spawns enemies.
 * When the total amount of enemies is smaller then the maximum.
 * Moves the enemies downwards.
 * Removes the enemies at the edge of the screen.
 */
void Enemy::Update()
{
	WindowManager& windowManager = WindowManager::getInstance();
	RandomNumberGenerator& randomNumberGenerator = RandomNumberGenerator::getInstance();
	Timers& timers = Timers::getInstance();

	Entity& entity = Entity::getInstance();
	Player& player = Player::getInstance();
	Game& game = Game::getInstance();

	sf::FloatRect playerBoundingBox = player.GetPlayer().getGlobalBounds();

	// Make this do nothing if the game is paused or the end screen is hit.
	// This should save me from having to do it everywhere in this function.
	if(!game.isPlaying())
	{
		return;
	}

	// TODO Fix this
#ifdef _ENEMY_SOUNDS_TEST
	// Play sound effect
	sf::Sound enemySfx(*playEnemySfx());
	enemySfx.play();
#endif //_ENEMY_SOUNDS_TEST

	Defines defines = Defines::getInstance();
	Enemy enemy = Enemy();
	

	// Updating the timer.
	if (m_Enemies.size() < m_MaxEnemies)
	{
		if (m_EnemySpawnTimer >= m_EnemySpawnTimerMax)
		{
			if (game.isPlaying())
			{
				Spawn();
				m_EnemySpawnTimer = 0.0f;
			}
		}
		else
		{
			m_EnemySpawnTimer += 1.0f;
			// Changing this allows more enemies to spawn in at once.
			// TODO Mess with this value later.
			//m_EnemySpawnTimer += 5.0f;
		}
	}

	// Moving and updating the enemies, check if they are below the screen
	for (int i = 0; i < m_Enemies.size(); i++)
	{
		bool deleted = false;



#ifdef ENEMY_RANDOM_SPAWNS
		// Well this makes a fun effect but the enemies disappear too fast.
		if (timers.SecondPassed())
		{
			m_RandomSpawnPos = randomNumberGenerator.GenerateRandomNumber(5.0f, 20.0f);
		}

		//m_Enemies[i].move(sf::Vector2f(randomSpawnPos, m_EnemySpeed));
		//m_Enemies[i].move(sf::Vector2f(m_RandomSpawnPos, -m_RandomSpawnPos));
		m_Enemies[i].move(sf::Vector2f(5.0f, m_RandomSpawnPos));

#else
		
		if (game.isPlaying())
		{
			// Change the speed by changing the offsetY
			//m_Enemies[i].move(sf::Vector2f(0.0f, m_EnemySpeed));
			m_Enemies[i].move(sf::Vector2f(m_DefaultEnemyXMovePos, m_EnemySpeed));
		}
		
#endif // ENEMY_RANDOM_SPAWNS

		// New
			
		// This works for basic collisions!
		// I got this mostly working better then it was. I had to add the m_PlayerHit variable.

#ifdef ENEMY_DAMAGE_PLAYER
		// Only damage the player if they don't have god mode, and they are within range of the m_Enemy.
		if (!player.HasGodMode() && entity.GetGlobalBounds(m_Enemies[i]).contains(player.GetPosition()))
		{
			if (timers.SecondPassed() && !m_PlayerHit)
			{
				player.SetLives(player.GetLives() - 1);
				m_PlayerHit = true;
				//fmt::println("Enemy is hitting the player, new lives: {}", player.GetLives());
			}
		}
		else
		{
			m_PlayerHit = false;
		}
#endif
		//

		// Delete the enemy if they are past the bottom of the screen.
		if (m_Enemies[i].getPosition().y > windowManager.getWindow().getSize().y
			|| m_Enemies[i].getPosition().x > windowManager.getWindow().getSize().x)
		{
			m_Enemies.erase(m_Enemies.begin() + i);
		}
	}
}

//----------------------------------------
// Enemy debug
//----------------------------------------

#ifdef _IMGUI_TEST
// TODO Move these into debug/enemy_debug.cpp/.h later, along with the other debug options.

/**
 * @brief Get the enemy random spawn position.
 * @return The random spawn position for the enemy.
 */
const float Enemy::GetRandomSpawnPos() const
{
	return m_RandomSpawnPos;
}

/**
 * @brief Get the X Move position for the enemy.
 * @return
 */
const float Enemy::GetDefaultXMovePos() const
{
	return m_DefaultEnemyXMovePos;
}

/**
 * @brief Set the X Move position for the enemy.
 * @param value
 */
void Enemy::SetDefaultXMovePos(float value)
{
	m_DefaultEnemyXMovePos = value;
}

/**
 * @brief Get the player speed (Y value)
 * @return
 */
const float Enemy::GetSpeed() const
{
	return m_EnemySpeed;
}

/**
 * @brief Set the enemies speed (Y value)
 * @param value
 */
void Enemy::SetSpeed(float value)
{
	m_EnemySpeed = value;
}

const float Enemy::GetSpawnRate() const
{
	return m_EnemySpawnTimerMax;
}

void Enemy::SetSpawnRate(float value)
{
	m_EnemySpawnTimerMax = value;
}

const float Enemy::GetMaxEnemies() const
{
	return m_MaxEnemies;
}

void Enemy::SetMaxEnemies(float value)
{
	m_MaxEnemies = value;
}

#endif // _IMGUI_TEST