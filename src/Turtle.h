#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"


class Turtle : public Object
{
public:
	Turtle(sf::RenderWindow* window);	// Constructor 
	void move();						// Moves turtle left or right
	void jump(bool down);				// Makes turtle jump (if down is true, turtle jumps down off the edge of a floor.Down being false can be
										// optionally used for fly animation of turtle when it is hit from underneath by Mario)
	void fall(void);					// Makes turtle fall when it dies

private:
	float vx;							// Horizontal speed 
	float vy;							// Vertical speed
};