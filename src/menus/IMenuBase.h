#pragma once

// All menus should inherit this base class
// To use for menu drawing:
// Include this in the class to draw this with, such as "menu_system.h":

/*
#include "IMenuBase.h"
class MenuSystem : public IMenuBase {}
*/

class IMenuBase
{
public:
	virtual ~IMenuBase() = default;

	virtual void Draw() = 0;
};