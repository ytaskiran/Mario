#pragma once

#include <SFML/Graphics.hpp>
#include "Object.h"

class Mario : public Object
{
public:
	Mario();		// Constructor

	virtual void update(Direction direction) override;	// Moves Mario left or right
	virtual void jump(bool down) override;				// Makes Mario jump (if down is true, Mario jumps down off the edge of a floor, otherwise he jumps up)
	virtual void fall(void) override;					// Makes Mario fall straight down when he dies
	virtual void move(void) override;
	bool isJumping();
	void resetState();
	bool restart();

private:
	const float SPEED = 3.0;
	void initializeMario();
	void checkSlide();
	int liveCount;
	bool jumping;
};
