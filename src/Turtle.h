#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"


class Turtle : public Object
{
public:
	Turtle(int initDelay, Direction dir);				// Constructor 

	void update(Direction dir);							// Updates the states of the turtle
	virtual void move() override;						// Moves turtle left or right
	virtual void jump() override;						// Makes turtle jump 
	virtual void fall(void) override;					// Makes turtle fall when it dies
	virtual void initialize() override;					// Initializes the turtles
	
	void resetState();									// Resets the state
	void setSurprised();								// Setter for surprised state
	bool getSurprised();								// Getter for surprised state
	void setFlippedOver();								// Setter for flipping over
	bool getFlippedOver();								// Getter for flipping over
	void setInPipe(int PipeDirection);					// Sets if the turtle reached to pipe (if in pipe)
	bool getIsHide();									// If it is in hide
	void changeDirection();								// Changes the direction
	void setInitDelay(int);								// Setter for initial delay
	void setHeading(Direction);							// Sets the heading

private:
	float speed;										// Turtle speed
	bool surprised;										// If the turtle is in surprised state
	bool flippedOver;									// If the turtle is flipped over
	sf::Clock clock;									// Clock to measure intervals
	bool isJumping;										// If the turtle is jumping
	bool isInPipe;										// If the turtle is in pipe
	int initDelay;										// Initial delay
	int pipeTimeout;									// Time that turtle will be in the pipe
	int pipeDir;										// Direction of the pipe
	const float MAX_SPEED_Y = _TURTLE_MAX_SPEED_Y;		
	const float MAX_SPEED_X = _TURTLE_MAX_SPEED_X;		
	bool isHide;										// If the turtle is not drawn (hidden)
};