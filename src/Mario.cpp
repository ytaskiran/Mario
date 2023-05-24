#include <Mario.h>

// Constructor
Mario::Mario()
{
	char path[64];

	for (int i = 1; i < 8; i++)
	{
		sprintf_s(path, "../assets/mario%d.png", i);
		textures[i].loadFromFile(path);
	}

	initialize(); // Initialize Mario
}

// Update the state and velocity of the Mario, according to the given direction.
void Mario::update(Direction dir)
{
	checkSlide(dir);

	if ((heading == Direction::RIGHT && dir == Direction::RIGHT)
		|| (heading == Direction::LEFT && dir == Direction::LEFT))
		movement_acc++;
	else
		movement_acc = 0;

	Direction prev_dir = heading;
	heading = dir;
	// State machine
	switch (state)
	{
		case 1: // Stationary
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
		case 2: // Run animation 
			if (animation_offset > 0) // Offset for smooth animation
			{
				animation_offset--;
				break;
			}

			if (dir == Direction::FIXED)
			{
				state = 1;
				vx = 0;
			}
			else if (dir == Direction::LEFT)
			{
				vx = -SPEED;

				if (prev_dir == Direction::LEFT)
				{
					state = 3;
				}
				else if (prev_dir == Direction::RIGHT)
				{
					state = 2;
				}
			}
			else if (dir == Direction::RIGHT)
			{
				vx = SPEED;

				if (prev_dir == Direction::RIGHT)
				{
					state = 3;
				}
				else if (prev_dir == Direction::LEFT)
				{
					state = 2;
				}
			}
			break;
		case 3: // Run animation
			if (animation_offset > 0)
			{
				animation_offset--;
				break;
			}
			if (dir == Direction::FIXED)
			{
				state = 1;
				vx = 0;
			}
			else if (dir == Direction::LEFT)
			{
				vx = -SPEED;

				if (prev_dir == Direction::LEFT)
				{
					state = 4;
				}
				else if (prev_dir == Direction::RIGHT)
				{
					state = 2;
				}
			}
			else if (dir == Direction::RIGHT)
			{
				vx = SPEED;

				if (prev_dir == Direction::RIGHT)
				{
					state = 4;
				}
				else if (prev_dir == Direction::LEFT)
				{
					state = 2;
				}
			}
			break;
		case 4: // Run animation
			if (animation_offset > 0)
			{
				animation_offset--;
				break;
			}
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
			if (sliding_offset > 0)
			{
				sliding_offset--;
				if (heading == Direction::LEFT)
				{
					vx += -0.1;
				}
				else if (heading == Direction::RIGHT)
				{
					vx += 0.1;
				}
				break;
			}
			else
				sliding_offset = 10;
				state = 1;
		case 6: // Jump
			if (dir == Direction::FIXED)
			{
				vx = 0;
			}
			else if (dir == Direction::RIGHT)
			{
				vx = SPEED;
			}
			else if (dir == Direction::LEFT)
			{
				vx = -SPEED;
			}
			break;
		case 7: // Falling state
		{
			vx = 0;
			vy += GRAVITY; 
			break;
		}
	}

	// Offset for smoother motion animation
	if (animation_offset == 0)
		animation_offset = _DEF_ANIMATION_OFFSET;
	animation_offset--;
	vy = std::min<float>(vy + GRAVITY, MAX_SPEED);
	prev_dir = dir;
	sprite.setTexture(textures[state]);
}

// Sets the Mario y velocity and state in jump state.
void Mario::jump()
{
	if (!jumping && !is_falling) 
	{
		vy = JUMP_SPEED;
		state = 6;
		jumping = true;
	}
}

// Set the Mario State to state 7 (fall state)
void Mario::fall(void)
{
	is_falling = true;
	vy = -20;
	state = 7;
}

// Reset the Mario state. It is used in Game logic to exit Mario from jumping state.
void Mario::resetState()
{
	state = 5;
	vy = 0;
	jumping = false;
}

// Initializes variables of Mario class. It is used in Constructor and restart functions.
void Mario::initialize() 
{
	pos.x = 400.0f;
	pos.y = 450.0f;

	heading = Direction::FIXED;
	jumping = false;
	is_falling = false;
	vx = 0;
	vy = 0;

	animation_offset = _DEF_ANIMATION_OFFSET;
	sliding_offset = 10;
	movement_acc = 0;

	state = 1;
	sprite.setTexture(textures[state]);
	sprite.setPosition(pos);
	sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
};

// It moves the Mario object, according to Mario velocity.
void Mario::move(void)
{
	sprite.move(vx, vy);
	pos = sprite.getPosition();
}

// Checks the sliding effect
void Mario::checkSlide(Direction dir)
{
	if (heading != Direction::FIXED && heading != dir && movement_acc > 10)
	{
		state = 5;
	}

	// Other jumping slide effect is handled in resetState function
	return;
}

// Get if Mario is in jumping state
bool Mario::isJumping()
{
	return jumping;
}

