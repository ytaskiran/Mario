#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"


class Turtle : public Object
{
public:
	Turtle(sf::RenderWindow* window);	// Constructor 

	void update(Direction dir);
	void move();						// Moves turtle left or right
	void jump(bool down);				// Makes turtle jump (if down is true, turtle jumps down off the edge of a floor.Down being false can be
										// optionally used for fly animation of turtle when it is hit from underneath by Mario)
	void fall(void);					// Makes turtle fall when it dies

	void incrementSpeed(int step);
	
	float vx;							// Horizontal speed 
	float vy;							// Vertical speed

	void resetState();
	void setSurprised();

private:
	float speed; 
	Direction _prevDir;
	void initializeTurtle();
	const int STEP = 1;
	bool waitedOneSecond;
	bool surprised;
	bool flippedOver;
	sf::Clock clock;
	bool isFalling;
	bool isJumping;
};