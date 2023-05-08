#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class Mario : public Object
{
public:
	Mario(sf::RenderWindow* window);	// Constructor
	void move();						// Moves Mario left or right
	void jump(bool down);				// Makes Mario jump (if down is true, Mario jumps down off the edge of a floor, otherwise he jumps up)
	void fall(void);					// Makes Mario fall straight down when he dies
	
private:
	float vx;							// Horizontal speed 
	float vy;							// Vertical speed
};