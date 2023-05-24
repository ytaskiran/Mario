#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class Mario : public Object
{
public:
	Mario();											// Constructor

	virtual void update(Direction direction) override;	// Moves Mario left or right
	virtual void jump() override;						// Makes Mario jump 
	virtual void fall(void) override;					// Makes Mario fall straight down when he dies
	virtual void move(void) override;					// Moves the Mario sprite in the map
	void initialize() override;							// Initializes the Mario 
		
	bool isJumping();									// Return if in jumping state
	void resetState();									// Reset the state to beginning
	float sliding_offset;								// Offset for sliding

private:
	void checkSlide(Direction dir);						// Function that checks the sliding effect while changing directions

	const float SPEED = _MARIO_SPEED;					// Default Mario speed
	const float JUMP_SPEED = _MARIO_JUMP_SPEED;			// Default jump speed
	const float MAX_SPEED = _MARIO_MAX_SPEED;			// Terminal velocity while falling with gravity
	bool jumping;										// Variable storing the jumping state
	int movement_acc;									// Acceleration
};
