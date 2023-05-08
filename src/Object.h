#pragma once
//#include <SFML/System/Vector2.hpp>

class Object
{
public:
	Object(sf::RenderWindow* window);		// Constructor
	void setPosition(sf::Vector2f pos);		// Sets position of the object
	sf::Vector2f getPosition();				// Gets position of the object
	sf::IntRect boundingBox(void);			// Returns the bounding rectangle of the object texture
	void draw(sf::RenderWindow& window);	// Draws current the object texture to screen
	void move(void);						// Abstract method that will be overridden
	void fall(void);						// Abstract method that will be overridden
	void jump(bool down);					// Abstract method that will be overridden

private:
	sf::Texture textures[8];				// Textures of Object (there are 8 textures total for Mario and 6 textures for Turtle)
	sf::Sprite sprite;						// Sprite for the object
	sf::Vector2f pos;						// Current position of object on screen
	sf::RenderWindow* window;				// Pointer to render window
	int state;								// Current animation state of the object (one of animation states)
	int heading;							// Facing direction of object
};