#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <list>

#include "TileMap.h"
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"


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


class Game
{
public:
	Game(sf::RenderWindow* window);							// Constructor
	void drawBackground();									// Draws the background objects
	void createMario();
	void createTurtles(int);
	void updateObjects();
	int mainMenu();
	~Game();

	enum class Status
	{
		MainMenu,
		Begin,
		Won,
		GameOver
	};

	Status status;

private:
	void drawLives();
	bool onFloor(Object* object);							// Checks if object is touching a floor surface
	bool checkCollusion(Turtle* t, Mario* m, int& side);	// Checks if Mario has hit a turtle and from which side
	void checkObstacle(Object* object);
	void marioFail();

	sf::RenderWindow* window_;
	TileMap map_{};
	ScoreBoard scoreboard_{};
	std::list<Object*> objects_{};
	sf::Sprite sprite;										// Sprite for general game menu
	sf::Texture lives_texture;
	sf::Texture mario_menu;
	sf::Font font;
	Object::Direction lastTurtleDir;

	const size_t MARIO_MAX_LIVES = _MARIO_MAX_LIVES;
};


