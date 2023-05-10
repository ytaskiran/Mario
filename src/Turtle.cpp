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
	timeStarted = false;
	sprite.setTexture(textures[state]);
	heading = Direction::FIXED;
	_prevDir = Direction::FIXED;
	// position iniatilize et. Position dýþardan alabilirsin. Bu durumda initialize fonksiyonunu dýþardan çaðýrýrýz.
}

void Turtle::update(Direction dir)
{
	Direction _prevDir = heading;
	heading = dir;

	if (isFalling) 
	{
		vx = 0;
		vy += GRAVITY;
		return;
	}
	else if (isJumping)
	{
		vy += GRAVITY;
		return;
	}

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
		vx = -vx;
		break;
	case 5:
		if (timeStarted) 
		{
			if (clock.getElapsedTime().asSeconds() >= 8)
			{
				state = 1;
				timeStarted = false;
			}
			
		}
		else 
		{
			timeStarted = true;
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

void Turtle::move()
{
	sprite.move(vx, vy);
	pos = sprite.getPosition();
}

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

void Turtle::fall(void)
{
	isFalling = true;
}

void Turtle::resetState()
{
	state = 1;
	vy = 0;
	vx = 0;
	isJumping = false;
}
