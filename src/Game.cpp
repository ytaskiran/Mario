#include "Game.h"

Game::Game(sf::RenderWindow* window) : window_(window)
{
    char path[64];

    sprintf_s(path, "../assets/mariohead.png");
    lives_texture.loadFromFile(path);

    scoreboard_.setLives(MARIO_MAX_LIVES);
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
            if (!dynamic_cast<Turtle*>(object)->getIsHide())
            {
                if (object->getVelocityX() > 0)
                    object->draw(window_, 0.6, 0.6);
                else
                    object->draw(window_, -0.6, 0.6);
            }
        }
    }

    drawLives();
}
           

void Game::drawLives()
{
    sprite.setTexture(lives_texture);
    sprite.setScale(0.8, 0.8);

    for (int i = 1; i <= scoreboard_.getLives(); i++)
    {
        sprite.setPosition(40 * i, 10);
        window_->draw(sprite);
    }

    sprite.setScale(1, 1);
}

void Game::createMario()
{
    objects_.emplace_back(new Mario());
}

void Game::createTurtles(int num) 
{
    for (int i = 0; i < num; i++) 
    {
        sf::Vector2f pos;
        pos.y = 75.0f;
        Turtle* turtle;
        
        if (i % 2 == 0 )
        {
            turtle = new Turtle(i * 50, Object::Direction::RIGHT);
            pos.x = 118.0f;
            lastTurtleDir = Object::Direction::LEFT;
        }
        else
        {
            turtle = new Turtle(i * 50, Object::Direction::LEFT);
            pos.x = 680.0f;
            lastTurtleDir = Object::Direction::RIGHT;
        }

        turtle->setPosition(pos);

        objects_.emplace_back(turtle);
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
    if (tile0_x > (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1) tile0_x = (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1;
    if (tile1_x > (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1) tile1_x = (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1;
    if (tile0_y < 0) tile0_y = 0; if (tile1_y < 0) tile1_y = 0;

    // take care of the case when index is out of range TODO
    if ((map_.getTile(tile0_y, tile0_x) == TileType::Floor or map_.getTile(tile1_y, tile1_x) == TileType::Floor or
         map_.getTile(tile0_y, tile0_x) == TileType::Brick or map_.getTile(tile1_y, tile1_x) == TileType::Brick) and object->getVelocityY() > 0)
    {
        object->sprite.setPosition(object->sprite.getPosition().x, tile0_y * TileMap::TILE_SIZE - 30); // consistent movement
        object->setVelocityY(0);   
        if (dynamic_cast<Mario*>(object) != nullptr && dynamic_cast<Mario*>(object)->isJumping())
        if (dynamic_cast<Mario*>(object) != nullptr &&dynamic_cast<Mario*>(object)->isJumping())
            object->resetState();
        return true;
    }

    return false;
}

void Game::updateObjects()
{
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

            onFloor(object);

            onFloor(object);
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

void ScoreBoard::setScore(int score)
{
    this->score = score;
}

void ScoreBoard::setLives(int lives)
{
    this->lives = lives;
}

int ScoreBoard::getLives(void)
{
    return lives;
}
