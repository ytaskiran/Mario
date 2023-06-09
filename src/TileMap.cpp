#include <vector>
#include <list>

#include "TileMap.h"


// Constructor
TileMap::TileMap()
{
    initializeMap();
}

// Initialize the map
void TileMap::initializeMap()
{
    // Loads the textures
    floor_texture_.loadFromFile("../assets/floor.png");
    brick_texture_.loadFromFile("../assets/brick.png");
    pipe_texture_.loadFromFile("../assets/pipe.png");
    pipe_s_texture_.loadFromFile("../assets/pipeS.png");

    // Locations of the bricks in the map
    auto brick_locations = std::list<std::vector<size_t>>{  // {row, col_left, col_right}
        {10,0,22}, {10,TILE_WIDTH - 23,TILE_WIDTH - 1}, {18,16,TILE_WIDTH - 16},
        {20,0,4}, {20, TILE_WIDTH - 5, TILE_WIDTH - 1}, {28,0,18}, {28,TILE_WIDTH - 19,TILE_WIDTH - 1}
    };

    // Initialized the tile map member variable
    tile_map_ = std::vector<std::vector<TileType>>(TILE_HEIGHT, std::vector<TileType>(TILE_WIDTH, TileType::Empty));

    for (size_t r = 0; r < TILE_HEIGHT; r++)
    {
        for (size_t c = 0; c < TILE_WIDTH; c++)
        {
            // Brick tiles are setted in the tile map
            if (brick_locations.size() > 0)
            {
                std::vector<size_t> brick_location = brick_locations.front();
                if (r == brick_location[0] && c >= brick_location[1] && c <= brick_location[2])
                {
                    tile_map_[r][c] = TileType::Brick;
                    if (c == brick_location[2])
                        brick_locations.pop_front();
                    continue;
                }
            }

            // Tiles are setted in the map 

            if (r >= TILE_HEIGHT - FLOOR_HEIGHT)
            {
                tile_map_[r][c] = TileType::Floor; 
            }
            else if (r >= TILE_HEIGHT - 8 && r < TILE_HEIGHT - 4 && c >= 0 && c < 7)
            {
                tile_map_[r][c] = TileType::Pipe;
            }
            else if (r >= TILE_HEIGHT - 8 && r < TILE_HEIGHT - 4 && c >= TILE_WIDTH - 7 && c < TILE_WIDTH)
            {
                tile_map_[r][c] = TileType::Pipe;
            }
            else if ((r >= 7 && r < 9 && c >= 0 && c < 3) || (r >= 5 && r < 9 && c >= 3 && c <= 6))
            {
                tile_map_[r][c] = TileType::PipeS;
            }
            else if ((r >= 7 && r < 9 && c < TILE_WIDTH && c >= TILE_WIDTH - 3) || (r >= 5 && r < 9 && c < TILE_WIDTH - 3 && c >= TILE_WIDTH - 6))
            {
                tile_map_[r][c] = TileType::PipeS;
            }
            else
            {
                tile_map_[r][c] = TileType::Empty;
            }
        }
    }
}

// Draws the background map
void TileMap::drawMap(sf::RenderWindow* window)
{
    const size_t ROWS = tile_map_.size();
    const size_t COLS = tile_map_[0].size();

    // flags for drawing both of the pipe types in each side
    bool left_pipe = false;
    bool right_pipe = false;
    bool left_pipe_s = false;
    bool right_pipe_s = false;

    for (size_t r = 0; r < ROWS; r++)
    {
        for (size_t c = 0; c < COLS; c++)
        {
            sf::Sprite sprite{};

            if (tile_map_[r][c] == TileType::Empty)
                continue;

            else if (tile_map_[r][c] == TileType::Floor)
            {
                sprite.setTexture(floor_texture_);
                sprite.setTextureRect(sf::IntRect(c * TILE_SIZE, TILE_SIZE * (r - TILE_HEIGHT + FLOOR_HEIGHT), TILE_SIZE, TILE_SIZE));
                sprite.setPosition(c * TILE_SIZE, r * TILE_SIZE);
                window->draw(sprite);
            }

            else if (tile_map_[r][c] == TileType::Brick)
            {
                sprite.setTexture(brick_texture_);
                sprite.setScale(0.5, 0.5);
                sprite.setPosition(c * TILE_SIZE, r * TILE_SIZE);
                window->draw(sprite);
            }

            else if (tile_map_[r][c] == TileType::Pipe && c < 7 && !left_pipe)
            {
                sprite.setTexture(pipe_texture_);
                sprite.setTextureRect(sf::IntRect(0, 0, pipe_texture_.getSize().x, pipe_texture_.getSize().y));
                sprite.setOrigin(pipe_texture_.getSize().x / 2, pipe_texture_.getSize().y / 2);
                sprite.setRotation(180.0);
                sprite.setPosition(c * TILE_SIZE + (pipe_texture_.getSize().x / 2), r * TILE_SIZE + (pipe_texture_.getSize().y / 2));
                left_pipe = true;
                window->draw(sprite);
            }

            else if (tile_map_[r][c] == TileType::Pipe && c >= TILE_WIDTH - 7 && !right_pipe)
            {
                sprite.setTexture(pipe_texture_);
                sprite.setTextureRect(sf::IntRect(0, 0, pipe_texture_.getSize().x, pipe_texture_.getSize().y));
                sprite.setPosition(c * TILE_SIZE, r * TILE_SIZE);
                right_pipe = true;
                window->draw(sprite);
            }

            else if (tile_map_[r][c] == TileType::PipeS && c == 0 && !left_pipe_s)
            {
                sprite.setTexture(pipe_s_texture_);
                sprite.setTextureRect(sf::IntRect(0, 0, pipe_s_texture_.getSize().x, pipe_s_texture_.getSize().y));
                sprite.setScale(0.5, 0.5);
                sprite.setPosition(c * TILE_SIZE, (r - 2) * TILE_SIZE);
                left_pipe_s = true;
                window->draw(sprite);
            }

            else if (tile_map_[r][c] == TileType::PipeS && c == TILE_WIDTH - 1 && !right_pipe_s)
            {
                sprite.setTexture(pipe_s_texture_);
                sprite.setTextureRect(sf::IntRect(0, 0, pipe_s_texture_.getSize().x, pipe_s_texture_.getSize().y));
                sprite.setScale(-0.5, 0.5);
                sprite.setPosition((c + 1) * TILE_SIZE, (r - 2) * TILE_SIZE);
                right_pipe_s = true;
                window->draw(sprite);
            }
        }
    }
}

// Get the tile type of the tile
TileType TileMap::getTile(size_t row, size_t col)
{
    return tile_map_[row][col];
}