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
	initialize();
}


void Turtle::initialize()
{
	speed = 3;
	state = 1;
	animation_offset = _DEF_ANIMATION_OFFSET;
	is_falling = false;
	isJumping = false;
	flippedOver = false;
	isInPipe = false;
	surprised = false;
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
	speed += 0.001;
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
		if (pos.y < SCREEN_HEIGHT)
		{
			vx = 0;
			vy += GRAVITY;
		}
		else if (!isHide)
		{
			vx = 0;
			vy = 0;
			isHide = true;
		}
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
		// Surprise state, change directions
		if (surprised)
		{
			vx = 0;
			if (clock.getElapsedTime().asSeconds() >= 1)
			{
				if (prev_heading == Direction::RIGHT)
				{
					vx = -speed;
				}
				else 
				{
					vx = speed;
				}
				state = 1;
				surprised = false;
			}
		}
		else 
		{
			surprised = true;
			vx = 0;
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
void Turtle::jump()
{
	
	vy = -20; 
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
	//setPosition(sf::Vector2f(pos.x,pos.y - 5));
	if (!surprised)
	{
		prev_heading = heading;
		state = 4;
	}
}

bool Turtle::getSurprised()
{
	return surprised;
}

void Turtle::setFlippedOver()
{
	vy = -10;
	state = 5;
}

// Getter function for the flippedOver variable.
bool Turtle::getFlippedOver()
{
	return flippedOver;
}

void Turtle::setInPipe(int PipeDirection)
{
	if (!isInPipe)
	{
		vx = 0;
		vy = 0;

		if (PipeDirection == 0)
		{
			setPosition(sf::Vector2f(70, 510));
		}
		else
		{
			setPosition(sf::Vector2f(720, 510));
		}
		pipeDir = PipeDirection;
		pipeTimeout = 100;

		isInPipe = true;
		isHide = true;
	}
}

bool Turtle::getIsHide() 
{
	return isHide;
}

void Turtle::changeDirection()
{
	if (state != 5 && state != 4)
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

void Turtle::setInitDelay(int delay)
{
	initDelay = delay;
}

void Turtle::setHeading(Direction dir)
{
	heading = dir;
}
