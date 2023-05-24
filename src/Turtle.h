#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"


class Turtle : public Object
{
public:
	Turtle(int initDelay, Direction dir);	// Constructor 

	void update(Direction dir);
	virtual void move() override;						// Moves turtle left or right
	virtual void jump(bool down) override;				// Makes turtle jump (if down is true, turtle jumps down off the edge of a floor.Down being false can be
														// optionally used for fly animation of turtle when it is hit from underneath by Mario)
	virtual void fall(void) override;					// Makes turtle fall when it dies
	
	void resetState();
	void setSurprised();
	void setFlippedOver();
	void setInPipe(int PipeDirection);
	bool getIsHide();
	void changeDirection();

private:
	float speed; 
	void initializeTurtle();
	const int STEP = 1;
	bool waitedOneSecond;
	bool surprised;
	bool flippedOver;
	sf::Clock clock;
	bool isJumping;
	bool isInPipe;
	int initDelay;
	int pipeTimeout;
	int pipeDir;
	const float MAX_SPEED_Y = _TURTLE_MAX_SPEED_Y;
	const float MAX_SPEED_X = _TURTLE_MAX_SPEED_X;
	bool isHide;
};