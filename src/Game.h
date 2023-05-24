#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "TileMap.h"
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"


class ScoreBoard
{
public:
	void setScore(int score);	// Sets the score 
	int getScore();				// Gets the score
	void setLives(int lives);	// Sets the remaining lives 
	int getLives(void);			// Gets the remaining lives

private:
	int score;					// Current score 
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
	int getScore();
	int getRemainingLives();
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
	void drawGameInfo();
	bool onFloor(Object* object);							// Checks if object is touching a floor surface
	void checkCollusion(Object* o1, Object* o2);			// Checks if Mario has hit a turtle and from which side
	void checkCollusion();
	void checkObstacle(Object* object);
	bool marioFail(Mario* m);
	void restartGame();

	sf::RenderWindow* window_;
	TileMap map_{};
	ScoreBoard scoreboard_{};
	std::vector<Object*> objects_{};
	sf::Sprite sprite;										// Sprite for general game menu
	sf::Texture lives_texture;
	sf::Texture mario_menu;
	sf::Font font;

	const size_t MARIO_MAX_LIVES = _MARIO_MAX_LIVES;
};


