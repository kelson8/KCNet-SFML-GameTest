#include "Enemy.h"
#include "util/MouseUtil.h"

#include "Game.h"

// #define _MOVE_ENEMY_FILE

#ifdef _MOVE_ENEMY_FILE

// TODO Fix this to work in this class, to switch over the spawn enemy function:
// To switch most other functions.
// Define _MOVE_ENEMY_FILE in defines.h

/// <summary>
/// Init the enemies
/// </summary>
void Enemy::initEnemies()
{
	Defines defines = Defines();

	// Set the position, size and scale
	this->enemy.setPosition(sf::Vector2f(10.0f, 10.0f));
	this->enemy.setSize(sf::Vector2f(100.0f, 100.0f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));

	// Set the fill color, outline color and outline thickness.
	this->enemy.setFillColor(sf::Color::Green);
	//this->enemy.setOutlineColor(sf::Color::Yellow);
	//this->enemy.setOutlineThickness(1.0f);
}



/// <summary>
/// Spawn the enemies and set their colors and positions.
/// Sets a random position
/// Sets a random color
/// Adds enemy to the vector.
/// </summary>
void Enemy::spawnEnemy()
{
    Game game = Game();
	// Randomizing between zero and the window size for the X
	// Using static cast, safely turning the value into a float, the random function only takes an int so it has to be
	// converted to an int first then randomize it.
	this->enemy.setPosition(
		// static_cast<float> (rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		static_cast<float> (rand() % static_cast<int>(game.getWindow()->getSize().x - this->enemy.getSize().x)),
		0.0f
		//static_cast<float> (rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
	);

	this->enemy.setFillColor(sf::Color::Green);

	// Spawn the enemy
	this->enemies.push_back(this->enemy);

	// Remove enemies at the end of the screen.
}

/// <summary>
///  Update the enemy spawn timer and spawns enemies.
///  When the total amount of enemies is smaller then the maximum.
///  Moves the enemies downwards.
///  Removes the enemies at the edge of the screen.
/// </summary>

void Enemy::updateEnemies()
{
    Game game = Game();

	// TODO Fix this
#ifdef _ENEMY_SOUNDS_TEST
	// Play sound effect
	sf::Sound enemySfx(*this->playEnemySfx());
	enemySfx.play();
#endif //_ENEMY_SOUNDS_TEST

	Defines defines = Defines();
	MouseUtil mouseUtil = MouseUtil();

	// Updating the timer.
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			// Spawn the enemy and reset the timer.
			this->spawnEnemy();
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
		this->enemies[i].move(0.0f, enemySpeed);

		// Delete the enemy if they are past the bottom of the screen.
		// if (this->enemies[i].getPosition().y > this->window->getSize().y)
		if (this->enemies[i].getPosition().y > game.getWindow()->getSize().y)
		{
            // TODO Figure this part out.
			this->enemies.erase(this->enemies.begin() + i);
			// this->health -= 1;
            game.setHealth();
			// std::cout << "Health: " << this->health << std::endl;
			std::cout << "Health: " << game.getHealth() << std::endl;
		}
	}

	// Remove the enemies
	// Check if clicked upon

	// Moving this into here should make it to where I can delay the mouse clicks.
	// Changing to this should optimize the code a bit
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

		// Check if the mouse is not held
		// This doesn't work, the mouse stays held in even with this.
		// TODO Fix this.
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;

			// If !deleted
			//for (size_t i = 0; i < this->enemies.size() && !deleted; i++)
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				// Only run if the mouse is clicked
#ifdef _MOVE_MOUSE_UTIL
				if (this->enemies[i].getGlobalBounds().contains(mouseUtil.getMousePosView()))
#else
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
#endif //_MOVE_MOUSE_UTIL
				{
					// Delete the enemy
					// Settings deleted to true cancels the loop.
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					// Gain points
					this->points += 1;
					std::cout << "Points: " << this->points << std::endl;
				}
			}
		} 
		// Set mouseHeld back to false.
		else 
		{ 
			this->mouseHeld = false;
		}
	}
}
#endif //!_MOVE_ENEMY_FILE