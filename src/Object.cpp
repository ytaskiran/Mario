#include <Object.h>
#include <iostream>

// Constructor
Object::Object()
{

}

// Sets the position of sprite.
void Object::setPosition(sf::Vector2f pos) 
{
	this->pos = pos;
	sprite.setPosition(pos);
}

// Returns the position of sprite.
sf::Vector2f Object::getPosition() {
	
	return sprite.getPosition();

}

// Returns the bounding box of sprite.
sf::FloatRect Object::boundingBox(void) 
{
	return sprite.getGlobalBounds();
}

// Draws the object with given window pointer.
void Object::draw(sf::RenderWindow* window, float x_scale, float y_scale) 
{
	sprite.setScale(x_scale, y_scale);
	window->draw(sprite);
}

// Getter for vx
float Object::getVelocityX()
{
	return vx;
}

// Getter for vy
float Object::getVelocityY()
{
	return vy;
}

// Setter for vx
void Object::setVelocityX(float vel)
{
	vx = vel;
}

// Setter for vy
void Object::setVelocityY(float vel)
{
	vy = vel;
}

// Return if the object is eliminated
bool Object::getIsDead()
{
	return is_falling;
}

// Get the heading
Object::Direction Object::getHeading()
{
	return heading;
}

// Get the previous heading
Object::Direction Object::getPrevHeading()
{
	return prev_heading;
}

// Set the previous heading
void Object::setPrevHeading(Object::Direction dir)
{
	prev_heading = dir;
}

void Object::update(Direction direction) { }
void Object::move() { }
void Object::fall() { }
void Object::resetState() { }
void Object::jump() { }
void Object::initialize() { }