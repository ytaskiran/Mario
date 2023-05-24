#include <Object.h>
#include <iostream>


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

float Object::getVelocityX()
{
	return vx;
}

float Object::getVelocityY()
{
	return vy;
}

void Object::setVelocityX(float vel)
{
	vx = vel;
}

void Object::setVelocityY(float vel)
{
	vy = vel;
}

bool Object::getIsDead()
{
	return is_falling;
}

Object::Direction Object::getHeading()
{
	return heading;
}

Object::Direction Object::getPrevHeading()
{
	return prev_heading;
}

void Object::setPrevHeading(Object::Direction dir)
{
	prev_heading = dir;
}


void Object::update(Direction direction)
{

}

void Object::move()
{

}

void Object::fall()
{

}

void Object::resetState()
{

}

void Object::jump()
{

}

void Object::initialize()
{

}