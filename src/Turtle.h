#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"


class Turtle : public Object
{
public:
	Turtle(int initDelay, Direction dir);	// Constructor 

	void update(Direction dir);
	virtual void move() override;						// Moves turtle left or right
	virtual void jump() override;						// Makes turtle jump 
	virtual void fall(void) override;					// Makes turtle fall when it dies
	virtual void initialize() override;					// Initializes the turtles
	
	void resetState();
	void setSurprised();
	bool getSurprised();
	void setFlippedOver();
	bool getFlippedOver();
	void setInPipe(int PipeDirection);
	bool getIsHide();
	void changeDirection();
	bool getFlippedOver();
	void setInitDelay(int);
	void setHeading(Direction);

private:
	float speed; 
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