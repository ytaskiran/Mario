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
	TileMap();
	void drawMap(sf::RenderWindow* window);
	TileType getTile(size_t row, size_t col);

	const static size_t TILE_SIZE = _TILE_SIZE;

private:
	void initializeMap();

	std::vector<std::vector<TileType>> tile_map_;

	sf::Texture floor_texture_;
	sf::Texture brick_texture_;
	sf::Texture pipe_texture_;
	sf::Texture pipe_s_texture_;

	const size_t FLOOR_HEIGHT = _FLOOR_HEIGHT; // 4 * TILE_SIZE
	const size_t TILE_WIDTH = SCREEN_WIDTH / TILE_SIZE;
	const size_t TILE_HEIGHT = SCREEN_HEIGHT / TILE_SIZE;
};