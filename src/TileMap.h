#pragma once

#include <SFML/Graphics.hpp>

#include "Parameters.h"

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
	TileMap();											// Constructor
	void drawMap(sf::RenderWindow* window);				// Draws the background map
	TileType getTile(size_t row, size_t col);			// Getter function for the specified tile
														
	const static size_t TILE_SIZE = _TILE_SIZE;			// Tile size constant
														
private:												
	void initializeMap();								// Initializes the map 
														
	std::vector<std::vector<TileType>> tile_map_;		// Stores the tiles
														
	sf::Texture floor_texture_;							// Texture for the floor
	sf::Texture brick_texture_;							// Texture for the brick
	sf::Texture pipe_texture_;							// Texture for the pipes at the bottom
	sf::Texture pipe_s_texture_;						// Texture for the S pipes at the top
														
	const size_t FLOOR_HEIGHT = _FLOOR_HEIGHT;			// Floor height (4 * TILE_SIZE)
	const size_t TILE_WIDTH = SCREEN_WIDTH / TILE_SIZE;
	const size_t TILE_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;
};