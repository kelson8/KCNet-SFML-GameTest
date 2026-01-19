#include "entity.h"

#include "window_manager.h"

// TODO Move items shared between the player and entities such as enemies into here
// So far, that's just the out of bounds checking.

/**
 * @brief Setup the entity
 */
Entity::Entity()
{

}

/**
 * @brief Unset the variables and stuff for the entity
 */
Entity::~Entity()
{

}

/**
 * @brief Check if the entity is in the bounds of the map
 * This works in the player class and for my ImGui menu.
 * 
 * TODO Possibly switch to sprite for this in the future?
 *
 * @param entity The sf::RectangleShape for the entity
 * @return If the entity is in the map bounds.
 */
const bool Entity::IsInBounds(sf::RectangleShape entity)
{
	WindowManager& windowManager = WindowManager::getInstance();

	//float playerPosX = GetPosition().x;
	float entityPosX = entity.getPosition().x;
	float entityPosY = entity.getPosition().y;
	//float playerPosY = GetPosition().y;

	float screenSizeX = windowManager.getWindow().getSize().x;
	float screenSizeY = windowManager.getWindow().getSize().y;

	// This is the amount of space above the screen for the X and Y, otherwise it won't count as being out of bounds until
	//  the player leaves the map a bit.
	int maxBounds = 50;

	if (
		entityPosX > screenSizeX - maxBounds ||
		entityPosY > screenSizeY - maxBounds ||
		entityPosX < -5 ||
		entityPosY < -5)
	{
		return false;
	}

	return true;
}