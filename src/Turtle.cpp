#include "Turtle.h"
Turtle::Turtle(sf::RenderWindow* window) : Object(window)
{
	char path[64];
	initializeTurtle();

	for (int i = 0; i < 6; i++)
	{
		sprintf_s(path, "../assets/turtle%d.png", i);
		textures[i].loadFromFile(path);
	}
}

void Turtle::incrementSpeed(int STEP)
{
	speed += STEP;
}

void Turtle::initializeTurtle()
{
	speed = 5;
	state = 1;
	vx = 0;
	vy = 0;
	isFalling = false;
	isJumping = false;
	flippedOver = false;
	sprite.setTexture(textures[state]);
	heading = Direction::FIXED;
	_prevDir = Direction::FIXED;
	// position iniatilize et. Position dýþardan alabilirsin. Bu durumda initialize fonksiyonunu dýþardan çaðýrýrýz.
}

// Update the Turtle velocity, state and heading. Is is called in every frame.
void Turtle::update(Direction dir)
{
	Direction _prevDir = heading;
	heading = dir;

	// Checks turtle is falling or not. If falling, turtle continue to fall, until it leaves the frame.
	if (isFalling) 
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

	// If the turtle not jumping or falling, state diagram works.
	switch (state)
	{
	case 1:
		if (dir == Direction::FIXED) 
		{
			vx = 0;
		}
		else if (dir == Direction::LEFT)
		{
			vx = -speed;
			if (_prevDir == Direction::LEFT) 
			{
				state = 2;
			}
		}
		else if (dir == Direction::RIGHT)
		{
			vx = speed;
			if (_prevDir == Direction::RIGHT)
			{
				state = 2;
			}
		}
		break;
	case 2:
		if (dir == Direction::FIXED)
		{
			vx = 0;
			state = 1;
		}
		else if (dir == Direction::LEFT)
		{
			vx = -speed;
			if (_prevDir == Direction::LEFT)
			{
				state = 3;
			}
			else if (_prevDir == Direction::RIGHT)
			{
				state = 1;
			}
		}
		else if (dir == Direction::RIGHT)
		{
			vx = speed;
			if (_prevDir == Direction::RIGHT)
			{
				state = 3;
			}
			if (_prevDir == Direction::LEFT)
			{
				state = 1;
			}
		}		
		break;
	case 3:
		state = 1;
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
				speed += 30; // Keep moving faster as it has been aggravated
				flippedOver = false;
			}
			
		}
		else 
		{
			flippedOver = true;
			clock.restart();
		}
		break;
	}

	sprite.setTexture(textures[state]);

	if (heading != _prevDir)
	{
		int width = sprite.getTexture()->getSize().x;
		int height = sprite.getTexture()->getSize().y;
		sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
	}
}

// Moves the turtle one interation, according to the velocity.
void Turtle::move()
{
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
	isFalling = true;
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