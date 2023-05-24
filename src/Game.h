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
	void createMario();										// Creates mario
	void createTurtles(int);								// Crates turtles
	void updateObjects();									// Update every object in the vector
	void restartGame(bool begin);							// Restarts the game
	void mainMenu();										// Draws the main menu screen
	void gameOver();										// Draws the gameOver screen
	void won();												//  Draws the won screen
	int getScore();											// Returns the score the player get
	int getRemainingLives();								// Returns the remaining lives of the Mario
	~Game();												// Destructor funtion to delete dynamic allocated objects

	// Enum class for the game status
	enum class Status
	{
		MainMenu,
		Begin,
		Won,
		GameOver
	};

	Status status;

private:
	void drawGameInfo();									// Draws the game info
	bool onFloor(Object* object);							// Checks if object is touching a floor surface
	void checkcollision(Object* o1, Object* o2);			// Checks if Mario has hit a turtle and from which side, or turtles are meet each other
	void checkcollision();									// Check collision of the every object couple
	void checkObstacle(Object* object);						// Checks the object will encounter with obstacle or not
	bool marioFail(Mario* m);								// Returns the mario fail state

	sf::RenderWindow* window_;								// Game window object
	TileMap map_{};											// TileMap class, to store map 2D array
	ScoreBoard scoreboard_{};								// Score board object
	std::vector<Object*> objects_{};						// Objects array, which contain all objects in the game
	sf::Sprite sprite;										// Sprite for general game menu
	sf::Texture lives_texture;								// Lives symbol texture
	sf::Texture mario_menu;									// Mario menu symbol texture
	sf::Font font;											// Game text fonts

	const size_t MARIO_MAX_LIVES = _MARIO_MAX_LIVES;		// Mario max lives constant value
};


