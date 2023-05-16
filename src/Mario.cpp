#include <Mario.h>


Mario::Mario()
{
	liveCount = 3;	
	char path[64];

	for (int i = 1; i < 8; i++)
	{
		sprintf_s(path, "../assets/mario%d.png", i);
		textures[i].loadFromFile(path);
	}

	initializeMario();
}

// Update the state and velocity of the Mario, according to the given direction.
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
	}
	_prevDir = dir;
	sprite.setTexture(textures[state]);

}

// Sets the Mario y velocity and state in jump state.
void Mario::jump(bool down)
{
	if (!jumping) 
	{
		// TODO how does this down var help?
		if (down)
		{
			vy = GRAVITY;
		}
		else
		{
			vy = -12;
		}
		state = 6;
		jumping = true;
	}
}

// Set the Mario State to state 7 (fall state)
void Mario::fall(void)
{
	state = 7;
}

// Reset the Mario state. It is used in Game logic to exit Mario from jumping state.
void Mario::resetState()
{
	state = 1;
	vy = 0;
	vx = 0;
	jumping = false;
}

// Restart the mario if Mario dies.
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

// Initializes variables of Mario class. It is used in Constructor and restart functions.
void Mario::initializeMario() 
{
	pos.x = 400.0f;
	pos.y = 485.0f;

	heading = Direction::FIXED;
	jumping = false;
	vx = 0;
	vy = 0;

	state = 1;
	sprite.setTexture(textures[state]);
	sprite.setPosition(pos);
};

// It moves the Mario object, according to Mario velocity.
void Mario::move(void)
{
	sprite.move(vx, vy);
	pos = sprite.getPosition();
}

// Not implemented yet. It can be also implement in game logic.
void Mario::checkSlide() 
{
	return;
}

bool Mario::isJumping()
{
	return jumping;
}

