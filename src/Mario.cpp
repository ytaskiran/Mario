#include <Mario.h>


Mario::Mario(sf::RenderWindow* window) : Object(window)
{
	liveCount = 3;
	initializeMario();
	
	char path[64];

	for (int i = 0; i<8 ; i ++)
	{
		sprintf_s(path, "../assets/mario%d.png", i);
		textures[i].loadFromFile(path);
	}
}

void Mario::update(Direction dir)
{
	Direction _prevDir = heading;
	heading = dir;
	switch (state)
	{
	case 1:
		if (dir == Direction::FIXED)
		{
			vx = 0;
		}
		else if (dir == Direction::LEFT)
		{
			vx = -SPEED;
			state = 2;
		}
		else if (dir == Direction::RIGHT)
		{
			vx = SPEED;
			state = 2;
		}
		break;
	case 2:
		if (dir == Direction::FIXED)
		{
			state = 1;
			vx = 0;
		}
		else if (dir == Direction::LEFT)
		{
			vx = -SPEED;

			if (_prevDir == Direction::LEFT)
			{
				state = 3;
			}
			else if (_prevDir == Direction::RIGHT)
			{
				state = 2;
			}
		}
		else if (dir == Direction::RIGHT)
		{
			vx = SPEED;

			if (_prevDir == Direction::RIGHT)
			{
				state = 3;
			}
			else if (_prevDir == Direction::LEFT)
			{
				state = 2;
			}
		}
		break;
	case 3:
		if (dir == Direction::FIXED)
		{
			state = 1;
			vx = 0;
		}
		else if (dir == Direction::LEFT)
		{
			vx = -SPEED;

			if (_prevDir == Direction::LEFT)
			{
				state = 4;
			}
			else if (_prevDir == Direction::RIGHT)
			{
				state = 2;
			}
		}
		else if (dir == Direction::RIGHT)
		{
			vx = SPEED;

			if (_prevDir == Direction::RIGHT)
			{
				state = 4;
			}
			else if (_prevDir == Direction::LEFT)
			{
				state = 2;
			}
		}
		break;
	case 4:
		if (dir == Direction::FIXED)
		{
			state = 1;
			vx = 0;
		}
		else
		{
			state = 2;

			if (dir == Direction::RIGHT)
			{
				vx = SPEED;
			}

			else if (dir == Direction::LEFT)
			{
				vx = -SPEED;
			}
		}
		break;
	case 5: // Sliding
		break;
	case 6:
		// düþmeye devam et.	
		vy += GRAVITY;
		break;
	case 7:
	{
		vx = 0;
		vy += GRAVITY; // Ekranýn aþaðýsýna düþmeye devam etsin. // Hýzýný arttýralým.
		break;
	}

	_prevDir = dir;
	sprite.setTexture(textures[state]);

	if (heading  != _prevDir)
	{
		int width = sprite.getTexture()->getSize().x;
		int height = sprite.getTexture()->getSize().y;
		sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
	}
	}
}
void Mario::jump(bool down)
{
	if (down)
	{
		vy = GRAVITY;
	}
	else
	{
		vy = -20;
	}
	state = 6;
}

void Mario::fall(void)
{
	state = 7;
}

void Mario::resetState()
{
	state = 1;
	vy = 0;
	vx = 0;
}

bool Mario::restart()
{
	if (liveCount == 0)
	{
		return false;
	}
	else 
	{
		initializeMario();
		return true;
	}
}


void Mario::initializeMario() 
{
	pos.x = 0.0f;
	pos.y = 0.0f;

	heading = Direction::FIXED;

	vx = 0;
	vy = 0;

	state = 1;
	sprite.setTexture(textures[state]);

};

void Mario::move(void)
{
	sprite.move(vx, vy);
	pos = sprite.getPosition();
}



