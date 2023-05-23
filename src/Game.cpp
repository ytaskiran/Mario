#include "Game.h"

Game::Game(sf::RenderWindow* window) : window_(window)
{

}

void Game::drawBackground()
{
    map_.drawMap(window_);

    for (Object* object : objects_)
    {        
        if (dynamic_cast<Mario*>(object) != nullptr)
        {
            // TODO store the latest direction to set when stationary
            if (object->getVelocityX() > 0)
                object->draw(window_, -0.6, 0.6);
            else
                object->draw(window_, 0.6, 0.6);
        }
        else
        {
            if (object->getVelocityX() > 0)
                object->draw(window_, 0.6, 0.6);
            else
                object->draw(window_, -0.6, 0.6);
        }
    }
}

void Game::createMario()
{
    objects_.emplace_back(new Mario());
}

void Game::createTurtles(int num) 
{

    turtleNotInitYet = num;
}

void Game::createTurtlesInOrder()
{
    if (turtleNotInitYet <= 0) 
    {
        return;
    }
    else {
        if (lastTurtleInit < 150)
        {
            lastTurtleInit++;
            return;
        }
        else {
            std::cout << "New turtle initialized" << std::endl;
            sf::Vector2f pos;
            pos.y = 75.0f;
     
            Turtle* turtle = new Turtle();
            if (lastTurtleDir == Object::Direction::RIGHT)
            {
                    pos.x = 118.0f;
                    turtle->update(Object::Direction::RIGHT);
                    lastTurtleDir = Object::Direction::LEFT;
             }
             else
                {
                    pos.x = 680.0f;
                    turtle->update(Object::Direction::LEFT);
                    lastTurtleDir = Object::Direction::RIGHT;
                }

                turtle->setPosition(pos);

                objects_.emplace_back(turtle);
                lastTurtleInit = 0;
                turtleNotInitYet--;
            
        }
    }
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

bool Game::onFloor(Object* object)
{
    float x_pixel{};
    float y_pixel{};
    if (object->getVelocityX() > 0)
        x_pixel = object->getPosition().x + object->sprite.getGlobalBounds().width / 2;
    else
        x_pixel = object->getPosition().x;
    if (object->getVelocityY() > 0)
        y_pixel = object->getPosition().y + object->sprite.getGlobalBounds().height / 2;
    else
        y_pixel = object->getPosition().y;

    float tile_x = x_pixel / TileMap::TILE_SIZE;
    float tile_y = y_pixel / TileMap::TILE_SIZE;

    // below functionality can be exttended and added to general collision check TODO
    
    // bottom left tile
    int tile0_x = floor(tile_x);
    int tile0_y = ceil(tile_y);

    // bottom right tile
    int tile1_x = ceil(tile_x);
    int tile1_y = ceil(tile_y);

    if (tile0_x < 0) tile0_x = 0;
    if (tile1_x > (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1) tile1_x = (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1;
    if (tile0_y < 0) tile0_y = 0; if (tile1_y < 0) tile1_y = 0;

    // take care of the case when index is out of range TODO
    if ((map_.getTile(tile0_y, tile0_x) == TileType::Floor or map_.getTile(tile1_y, tile1_x) == TileType::Floor or
         map_.getTile(tile0_y, tile0_x) == TileType::Brick or map_.getTile(tile1_y, tile1_x) == TileType::Brick) and object->getVelocityY() > 0)
    {
        object->sprite.setPosition(object->sprite.getPosition().x, tile0_y * TileMap::TILE_SIZE - 30); // consistent movement
        object->setVelocityY(0);   
        if (dynamic_cast<Mario*>(object)->isJumping())
            object->resetState();
        return true;
    }

    return false;
}

void Game::updateObjects()
{
    createTurtlesInOrder();
    for (Object* object : objects_)
    {
        auto pos = object->getPosition();
        if (dynamic_cast<Mario*>(object) != nullptr)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                object->jump(false);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                object->update(Object::Direction::LEFT);
                if (pos.x + object->getVelocityX() <= 5) object->setVelocityX(0);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                object->update(Object::Direction::RIGHT);
                if (pos.x + object->getVelocityX() >= SCREEN_WIDTH - 35) object->setVelocityX(0);
            }
            else
            {
                object->update(Object::Direction::FIXED);
            }

            onFloor(object);
            checkObstacle(object);
        }
        else  // Turtle case
        {
            // onFloor, checkcollision will be added.
            float _vx = object->getVelocityX();
            if (_vx > 0)
                object->update(Object::Direction::RIGHT);
            else
                object->update(Object::Direction::LEFT);

        }

        object->move();


    }
}

// Checks if hit any obstacle like a pipe or ceiling for Mario
void Game::checkObstacle(Object* object)
{
    float x_pixel{};
    float y_pixel{};

    int tile_x{};
    int tile_y{};

    if (object->getVelocityX() == 0 and object->getVelocityY() == 0)
        return;

    if (object->getVelocityX() > 0)
    {
        x_pixel = object->getPosition().x + object->sprite.getGlobalBounds().width / 2;
        float x = x_pixel / TileMap::TILE_SIZE;
        tile_x = ceil(x);
    }
        
    else if (object->getVelocityX() < 0)
    {
        x_pixel = object->getPosition().x - object->sprite.getGlobalBounds().width / 2;
        float x = x_pixel / TileMap::TILE_SIZE;
        tile_x = floor(x);
    }
    else
    {
        x_pixel = object->getPosition().x;
        tile_x = x_pixel / TileMap::TILE_SIZE;
    }

    if (object->getVelocityY() > 0)
    {
        y_pixel = object->getPosition().y + object->sprite.getGlobalBounds().height / 2;
        float y = y_pixel / TileMap::TILE_SIZE;
        tile_y = ceil(y);
    }    
    else if (object->getVelocityY() < 0)
    {
        y_pixel = object->getPosition().y - object->sprite.getGlobalBounds().height / 2;
        float y = y_pixel / TileMap::TILE_SIZE;
        tile_y = floor(y);
    }

    else
    {
        y_pixel = object->getPosition().y;
        tile_y = y_pixel / TileMap::TILE_SIZE;
    }


    if (tile_x < 0) tile_x = 0;
    if (tile_x > (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1) tile_x = (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1;
    if (tile_y < 0) tile_y = 0;

    if (map_.getTile(tile_y, tile_x) != TileType::Empty)
    {
        if (dynamic_cast<Mario*>(object)->isJumping() && object->getVelocityY() > 0)
            object->resetState();
        else
        {
            object->setVelocityX(0.0);
            object->setVelocityY(0.0);
        }
    }
}

Game::~Game()
{
    for (Object* object : objects_)
    {
        delete object;
    }
}

TileMap::TileMap()
{
    initializeMap();
}

void TileMap::initializeMap()
{
    floor_texture_.loadFromFile("../assets/floor.png");
    brick_texture_.loadFromFile("../assets/brick.png");
    pipe_texture_.loadFromFile("../assets/pipe.png");
    pipe_s_texture_.loadFromFile("../assets/pipeS.png");

   /* auto floor_size = floor_texture_.getSize();
    auto brick_size = brick_texture_.getSize();
    auto pipe_size = pipe_texture_.getSize();
    auto pipe_s_size = pipe_s_texture_.getSize();

    std::cout << "Tile height: " << TILE_HEIGHT << std::endl;
    std::cout << "Tile width: " << TILE_WIDTH << std::endl;

    std::cout << "Floor x: " << floor_size.x << " y: " << floor_size.y << std::endl;
    std::cout << "Brick x: " << brick_size.x << " y: " << brick_size.y << std::endl;
    std::cout << "Pipe x: " << pipe_size.x << " y: " << pipe_size.y << std::endl;
    std::cout << "PipeS x: " << pipe_s_size.x << " y: " << pipe_s_size.y << std::endl;*/

    auto brick_locations = std::list<std::vector<size_t>>{  // {row, col_left, col_right}
        {10,0,22}, {10,TILE_WIDTH - 23,TILE_WIDTH - 1}, {18,16,TILE_WIDTH - 16}, 
        {20,0,4}, {20, TILE_WIDTH - 5, TILE_WIDTH - 1}, {28,0,18}, {28,TILE_WIDTH-19,TILE_WIDTH-1}
    };    

    tile_map_ = std::vector<std::vector<TileType>>(TILE_HEIGHT, std::vector<TileType>(TILE_WIDTH, TileType::Empty));

    for (size_t r = 0; r < TILE_HEIGHT; r++)
    {
        for (size_t c = 0; c < TILE_WIDTH; c++)
        {
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

void TileMap::drawMap(sf::RenderWindow* window)
{
    const size_t ROWS = tile_map_.size();
    const size_t COLS = tile_map_[0].size();

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

TileType TileMap::getTile(size_t row, size_t col)
{
    return tile_map_[row][col];
}
