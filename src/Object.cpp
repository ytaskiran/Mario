#include <Object.h>


Object::Object(sf::RenderWindow* window) {
	this->window = window;

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

// Draws the object in given window onject.
void Object::draw(sf::RenderWindow& window) 
{
	window.draw(sprite);
}

