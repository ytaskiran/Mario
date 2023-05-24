#include "Turtle.h"
Turtle::Turtle(int initDelay, Direction dir)
{
	char path[64];
	
	for (int i = 1; i < 6; i++)
	{
		sprintf_s(path, "../assets/turtle%d.png", i);
		textures[i].loadFromFile(path);
	}

	this->heading = dir;
	this->initDelay = initDelay;
	initializeTurtle();
}


void Turtle::initializeTurtle()
{
	speed = 3;
	state = 1;
	animation_offset = _DEF_ANIMATION_OFFSET;
	is_falling = false;
	isJumping = false;
	flippedOver = false;
	isInPipe = false;
	sprite.setTexture(textures[state]);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	// position iniatilize et. Position dýþardan alabilirsin. Bu durumda initialize fonksiyonunu dýþardan çaðýrýrýz.
	vy = 10;
	if (heading == Direction::RIGHT)
	{
		vx = 1;
	}
	else 
	{
		vx = -1;
	}

	if (initDelay == 0) 
	{
		isHide = false;
	}
	else 
	{
		isHide = true;
	}
}

// Update the Turtle velocity, state and heading. Is is called in every frame.
void Turtle::update(Direction dir)
{
	speed += 0.0004;
	speed = std::min(MAX_SPEED_X, speed);
	Direction prev_dir = heading;
	heading = dir;

	if (initDelay > 0)
	{
		if (--initDelay == 0)
		{
			isHide = false;
		}
		return;
	}

	if (isInPipe) 
	{
		if (pipeTimeout == 0)
		{
			state = 1;
			isInPipe = false;
			isHide = false;
			// initalize turtle again
			pos.y = 75.0f;
			vy = 1;
			if (pipeDir == 0)
			{
				vx = speed;
				pos.x = 110.0f;
			}
			else if (pipeDir == 1)
			{
				vx = -speed;
				pos.x = 680.0f;
			}
			sprite.setPosition(pos);
			return;
		}
		else
		{
			pipeTimeout--;
			return;
		}
	}
	// Checks turtle is falling or not. If falling, turtle continue to fall, until it leaves the frame.
	else if (is_falling) 
	{
		vx = 0;
		vy += GRAVITY;
		return;
	}

	// Checks the turtle is jumping. If jumping, turtle y velocity increase as gravity, anf x velocit will be same.
	else if (isJumping)
	{
		vy += GRAVITY;
		return;
	}

	// If the turtle not in the above states, state diagram works.
	switch (state)
	{
	case 1:
		if (animation_offset > 0)
		{
			animation_offset--;
			break;
		}

		if (dir == Direction::FIXED) 
		{
			vx = 0;
		}
		else if (dir == Direction::LEFT)
		{
			vx = -speed;
			if (prev_dir == Direction::LEFT)
			{
				state = 2;
			}
		}
		else if (dir == Direction::RIGHT)
		{
			vx = speed;
			if (prev_dir == Direction::RIGHT)
			{
				state = 2;
			}
		}
		break;
	case 2:
		if (animation_offset > 0)
		{
			animation_offset--;
			break;
		}

		if (dir == Direction::FIXED)
		{
			vx = 0;
			state = 1;
		}
		else if (dir == Direction::LEFT)
		{
			vx = -speed;
			if (prev_dir == Direction::LEFT)
			{
				state = 3;
			}
			else if (prev_dir == Direction::RIGHT)
			{
				state = 1;
			}
		}
		else if (dir == Direction::RIGHT)
		{
			vx = speed;
			if (prev_dir == Direction::RIGHT)
			{
				state = 3;
			}
			if (prev_dir == Direction::LEFT)
			{
				state = 1;
			}
		}		
		break;
	case 3:
		if (animation_offset > 0)
		{
			animation_offset--;
			break;
		}
		if (dir == Direction::FIXED)
		{
			vx = 0;
		}
		else if (dir == Direction::LEFT)
		{
			vx = -speed;
		}
		else if (dir == Direction::RIGHT)
		{
			vx = speed;
		}		
		state = 1;
		break;
	case 4:
		// Þaþýrma durumu. Yön deðiþitirecek.
		if (surprised)
		{
			if (clock.getElapsedTime().asSeconds() >= 1)
			{
				vx = -vx;
				if (vx > 0)
				{
					dir = Direction::RIGHT;
					heading = dir;
				}
				else 
				{
					dir = Direction::LEFT;
					heading = dir;
				}
				state = 1;
			}
		}
		else 
		{
			surprised = true;
			clock.restart();
		}
		
		break;
	case 5:
		if (flippedOver) 
		{
			if (clock.getElapsedTime().asSeconds() >= 8)
			{
				state = 1;
				speed += 1; // Keep moving faster as it has been aggravated
				flippedOver = false;
			}
		}
		else 
		{
			vx = 0;
			flippedOver = true;
			clock.restart();
		}
		break;
	}

	if (animation_offset == 0)
		animation_offset = _DEF_ANIMATION_OFFSET;
	animation_offset--;

	vy = std::min<float>(vy + GRAVITY, MAX_SPEED_Y);

	sprite.setTexture(textures[state]);
}

// Moves the turtle one interation, according to the velocity.
void Turtle::move()
{
	if (pos.x + vx > SCREEN_WIDTH || pos.x + vx < 30) 
		vx = 0;
	if(!isHide)
		sprite.move(vx, vy);
	pos = sprite.getPosition();
}

// Sets the y velocity and isJumping variable. It is used to start the jumping state.
void Turtle::jump(bool down)
{
	if (down)
	{
		vy = GRAVITY;
	}
	else
	{
		vy = -20; // Bu deðer gravityden fazla olacak. Yukarý zýpladýðýmýzda hýzlýca yükseliriz 
	}
	isJumping = true;
}

// Sets the isFalling variable true. It is used to fall Turtle. 
void Turtle::fall(void)
{
	sprite.setTexture(textures[5]);
	is_falling = true;
}

// Resets the turtle state and y velocity. It is used to exit turtle from jump state
void Turtle::resetState()
{
	state = 1;
	vy = 0;
	vx = 0;
	isJumping = false;
}

// Sets the turtle state surprised state. It is used when two turtle touch each other.
void Turtle::setSurprised()
{
	state = 4;
}

void Turtle::setFlippedOver()
{
	vy = -10;
	state = 5;
}

void Turtle::setInPipe(int PipeDirection)
{
	vx = 0;
	vy = 0;

	pipeDir = PipeDirection;
	pipeTimeout = 100;

	isInPipe = true;
	isHide = true;
}

bool Turtle::getIsHide() 
{
	return isHide;
}

void Turtle::changeDirection()
{
	if (state != 5)
	{
		if (heading == Direction::LEFT)
		{
			vx = speed;
			update(Direction::RIGHT);
		}
		else
		{
			vx = -speed;
			update(Direction::LEFT);
		}
	}
	else 
	{
		update(Direction::FIXED);
	}
}
