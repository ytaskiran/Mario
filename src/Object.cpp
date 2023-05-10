#include <Object.h>


Object::Object(sf::RenderWindow* window) {
	this->window = window;

}

void Object::setPosition(sf::Vector2f pos) 
{
	this->pos = pos;
	sprite.setPosition(pos);
}

sf::Vector2f Object::getPosition() {
	
	return sprite.getPosition();

}

sf::FloatRect Object::boundingBox(void) 
{
	return sprite.getGlobalBounds();
}

void Object::draw(sf::RenderWindow& window) 
{
	window.draw(sprite);
}

