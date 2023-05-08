#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"

class Game
{
public:
	void drawBackground(sf::RenderWindow& window);			// Draws the background objects
	bool onFloor(Object* obj);								// Checks if object is touching a floor surface
	bool checkCollusion(Turtle* t, Mario* m, int& side);	// Checks if Mario has hit a turtle and from which side
};


class ScoreBoard
{
public:
	void setScore(int score);	// Sets the score 
	void setLives(int lives);	// Sets the remaining lives 
	int getLives(void);			// Gets the remaining lives

private:
	std::string score;			// Current score 
	int lives;					// Remaining life count for Mario
};