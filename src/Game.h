#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include "Object.h"
#include "Mario.h"
#include "Turtle.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

enum class TileType
{
	Empty,
	Floor,
	Brick,
	Pipe,
	PipeS
};


class TileMap
{
public:
	TileMap();
	void drawMap(sf::RenderWindow* window);

private:
	void initializeMap();

	std::vector<std::vector<TileType>> tile_map_;

	sf::Texture floor_texture_;
	sf::Texture brick_texture_;
	sf::Texture pipe_texture_;
	sf::Texture pipe_s_texture_;

	const size_t TILE_SIZE = 15;
	const size_t FLOOR_HEIGHT = 4; // 4 * TILE_SIZE

	const size_t TILE_WIDTH = SCREEN_WIDTH / TILE_SIZE;
	const size_t TILE_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;
};


class Game
{
public:
	Game(sf::RenderWindow* window);							// Constructor
	void drawBackground();									// Draws the background objects
	void createMario();
	void createTurtles(int);
	bool onFloor(Object* obj);								// Checks if object is touching a floor surface
	bool checkCollusion(Turtle* t, Mario* m, int& side);	// Checks if Mario has hit a turtle and from which side
	void marioFail();
	int mainMenu();
	Mario* mario;
private:
	sf::RenderWindow* window_;
	TileMap map_{};
	std::list<Object*> objects_{};
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