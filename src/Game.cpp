#include "Game.h"

Game::Game()
{

}

void Game::drawBackground(sf::RenderWindow& window)
{
    map_.drawMap(window);
}

int Game::mainMenu()
{
    //sf::Font font;
    //if (!font.loadFromFile("../assets/font.ttf"))
    //{
    //    std::cout << "Unable to load the font file from " << std::filesystem::current_path() << std::endl;
    //    std::cin.get();
    //    return EXIT_FAILURE;
    //}

    //sf::Text text("Welcome to the Mario ", font, 40);

    return 0;
}


TileMap::TileMap()
{
    initializeMap();
}

void TileMap::initializeMap()
{
    floor_texture_.loadFromFile("../assets/floor.png");
    brick_texture_.loadFromFile("../assets/brick.png");

    auto floor_size = floor_texture_.getSize();
    auto brick_size = brick_texture_.getSize();

    std::cout << "Floor x: " << floor_size.x << " y: " << floor_size.y << std::endl;
    std::cout << "Brick x: " << brick_size.x << " y: " << brick_size.y << std::endl;

    brick_locations_ = std::vector<std::vector<size_t>>{ {} };

    tile_map_ = std::vector<std::vector<TileType>>(TILE_HEIGHT, std::vector<TileType>(TILE_WIDTH, TileType::Empty));

    for (size_t r = 0; r < TILE_HEIGHT; r++)
    {
        for (size_t c = 0; c < TILE_WIDTH; c++)
        {
            if (r > TILE_HEIGHT - FLOOR_HEIGHT)
            {
                tile_map_[r][c] = TileType::Floor;
            }

            else if (r == TILE_HEIGHT / 2 && c < TILE_WIDTH / 2)
            {
                tile_map_[r][c] = TileType::Brick;
            }
            else
            {
                tile_map_[r][c] = TileType::Empty;
            }
        }
    }
}

void TileMap::drawMap(sf::RenderWindow& window)
{
    const size_t ROWS = tile_map_.size();
    const size_t COLS = tile_map_[0].size();

    sf::Sprite sprite{};

    for (size_t r = 0; r < ROWS; r++)
    {
        for (size_t c = 0; c < COLS; c++)
        {
            if (tile_map_[r][c] == TileType::Empty)
                continue;

            else if (tile_map_[r][c] == TileType::Floor)
            {
                sprite.setTexture(floor_texture_);
                sprite.setTextureRect(sf::IntRect(c * TILE_SIZE, TILE_SIZE * (r - TILE_HEIGHT + FLOOR_HEIGHT), TILE_SIZE, TILE_SIZE));
                sprite.setScale(1, 1);
            }

            else if (tile_map_[r][c] == TileType::Brick)
            {
                sprite.setTexture(brick_texture_);
                sprite.setScale(0.5, 0.5);
            }
            
            sprite.setPosition(c * TILE_SIZE, r * TILE_SIZE);

            window.draw(sprite);
        }
    }
}