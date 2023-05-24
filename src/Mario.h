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
		
	bool isJumping();
	void resetState();
	float sliding_offset;

private:
	void checkSlide(Direction dir);

	const float SPEED = _MARIO_SPEED;
	const float JUMP_SPEED = _MARIO_JUMP_SPEED;
	const float MAX_SPEED = _MARIO_MAX_SPEED;
	bool jumping;
	int movement_acc;
};
