#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cmath>
#include <algorithm>

#include "Parameters.h"

class Object
{
public:
	Object();											// Constructor
	void setPosition(sf::Vector2f pos);					// Sets position of the object
	sf::Vector2f getPosition();							// Gets position of the object
	sf::FloatRect boundingBox(void);					// Returns the bounding rectangle of the object texture
	void draw(sf::RenderWindow* window, float, float);	// Draws current the object texture to screen

	float getVelocityX();
	float getVelocityY();

	void setVelocityX(float);
	void setVelocityY(float);

	// Direction enumaretion class. It is to represent heading of the object.
	enum class Direction {
		FIXED,
		LEFT,
		RIGHT
	};
	
	// Virtual functions
	virtual void update(Direction direction);			// Abstract method that will be overridden
	virtual void move(void);							// Abstract method that will be overridden
	virtual void fall(void);							// Abstract method that will be overridden
	virtual void resetState();   						// Abstract method that will be overridden
	virtual void jump(bool down);						// Abstract method that will be overridden

	sf::Sprite sprite;									// Sprite for the object
	int state;											// Current animation state of the object (one of animation states)

protected:
	const float GRAVITY = 1;							// Constant gravity value used in objects.
	sf::Vector2f pos;									// Current position of object on screen
	Direction heading;									// Facing direction of object
	sf::Texture textures[8];							// Textures of Object (there are 8 textures total for Mario and 6 textures for Turtle)
	//sf::RenderWindow* window_;						// Pointer to render window
	float vx;											// Horizontal speed 
	float vy;											// Vertical speed
};