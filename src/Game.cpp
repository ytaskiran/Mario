#include "Game.h"

Game::Game(sf::RenderWindow* window) : window_(window), status(Status::MainMenu)
{
    lives_texture.loadFromFile("../assets/mariohead.png");
    mario_menu.loadFromFile("../assets/mario_menu.png");
    scoreboard_.setLives(MARIO_MAX_LIVES);
}

// The function called in every frame. It draws game map, Mario and turtle objects according to their headings.
void Game::drawBackground()
{
    // First draw the game map.
    map_.drawMap(window_);

    // Iterate over the objects and draw according to their headings
    for (Object* object : objects_)
    {        
        // Mario case
        if (dynamic_cast<Mario*>(object) != nullptr)
        {
            // If else statements to determine heading
            if (object->getVelocityX() > 0 || (object->getVelocityX() == 0 && object->getHeading() == Object::Direction::RIGHT))
                object->draw(window_, -0.6, 0.6);
            else if (object->getVelocityX() < 0 || (object->getVelocityX() == 0 && object->getHeading() == Object::Direction::LEFT))
                object->draw(window_, 0.6, 0.6);
            else if (object->getVelocityX() == 0 && object->getPrevHeading() == Object::Direction::RIGHT)
                object->draw(window_, -0.6, 0.6);
            else
                object->draw(window_, 0.6, 0.6);
        }
        // Turtle case
        else
        {
            // If else statements to determine heading
            if (!dynamic_cast<Turtle*>(object)->getIsHide())
            {
                if (object->getVelocityX() > 0 || (object->getVelocityX() == 0 && object->getHeading() == Object::Direction::RIGHT))
                    object->draw(window_, 0.6, 0.6);
                else if (object->getVelocityX() < 0 || (object->getVelocityX() == 0 && object->getHeading() == Object::Direction::LEFT))
                    object->draw(window_, -0.6, 0.6);
                else
                    object->draw(window_, -0.6, 0.6);
            }       
        }
    }

    // Draw the left Mario lives 
    drawLives();
}
           
// Draw the left Mario lives 
void Game::drawLives()
{
    sprite.setTexture(lives_texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale(0.8, 0.8);

    // Draw lives according to left lives. 
    for (int i = 1; i <= scoreboard_.getLives(); i++)
    {
        sprite.setPosition(40 * i, 20);
        window_->draw(sprite);
    }

    sprite.setScale(1, 1);
}

// Create a new mario and insert it objects_ array
void Game::createMario()
{
    objects_.emplace_back(new Mario());
}

// Create given number turtles and instert it objects_ array. 
// Turtles initialized in map with a delay.  
void Game::createTurtles(int num) 
{
    for (int i = 0; i < num; i++) 
    {
        sf::Vector2f pos;
        pos.y = 75.0f;
        Turtle* turtle;
        
        // Turtles initialized left and right in turn
        if (i % 2 == 0 )
        {
            // i * 50 : Delay time for initializing in map
            turtle = new Turtle(i * 100 + 10, Object::Direction::RIGHT);
            pos.x = 118.0f;
            lastTurtleDir = Object::Direction::LEFT;
        }
        else
        {
            // i * 50 : Delay time for initializing in map
            turtle = new Turtle(i * 100 + 5, Object::Direction::LEFT);
            pos.x = 680.0f;
            lastTurtleDir = Object::Direction::RIGHT;
        }

        // Sets the turtle initial pos according to right or left initialization
        turtle->setPosition(pos);

        // Adds the turtle to objects_ array
        objects_.emplace_back(turtle);
    }

}

int Game::mainMenu()
{
    if (!font.loadFromFile("../assets/font.ttf"))
    {
        std::cout << "Unable to load the font file. " << std::endl;
        return EXIT_FAILURE;
    }

    sf::Text welcome_text("Welcome to the Mario", font, 40);
    welcome_text.setPosition(SCREEN_WIDTH / 2, 100.f);
    welcome_text.setOrigin(welcome_text.getLocalBounds().width / 2, welcome_text.getLocalBounds().height / 2);
    welcome_text.setFillColor(sf::Color::Red);
    welcome_text.setStyle(sf::Text::Bold);

    sf::Text start_text("Press ENTER to Start", font, 30);
    start_text.setPosition(SCREEN_WIDTH / 2, 250.f);
    start_text.setOrigin(start_text.getLocalBounds().width / 2, start_text.getLocalBounds().height / 2);

    sf::Sprite mario;
    mario.setTexture(mario_menu);
    mario.setScale(2, 2);
    mario.setPosition(SCREEN_WIDTH / 2, 450.f);
    mario.setOrigin(mario.getLocalBounds().width / 2, mario.getLocalBounds().height / 2);

    window_->draw(welcome_text);
    window_->draw(start_text);
    window_->draw(mario);

    return 0;
}

// Chekcs given object is on floor or not
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

// It is called in every frame. The function updates the every object in the objects_ vector.
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
                object->setPrevHeading(Object::Direction::LEFT); // remember the direction when stationary
                if (pos.x + object->getVelocityX() <= 5) object->setVelocityX(0);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                object->update(Object::Direction::RIGHT);
                object->setPrevHeading(Object::Direction::RIGHT); // remember the direction when stationary
                if (pos.x + object->getVelocityX() >= SCREEN_WIDTH - 35) object->setVelocityX(0);
            }
            else
            {
                object->update(Object::Direction::FIXED);
            }
        }
        else  // Turtle case
        {
            // onFloor, checkcollision will be added.
            float _vx = object->getVelocityX();
            if (_vx > 0)
                object->update(Object::Direction::RIGHT);
            else if (_vx < 0)
                object->update(Object::Direction::LEFT);
            else
                dynamic_cast<Turtle*>(object)->changeDirection();
        }

        if (!object->getIsDead())
        {
            onFloor(object);
            checkObstacle(object);
        }

        object->move();
    }
    checkCollusion();

}

void Game::checkCollusion()
{
    size_t left = 0;
    size_t right = 1;

    while (right < objects_.size())
    {
        checkCollusion(objects_[left], objects_[right]);
        right++;

        if (right == objects_.size())
        {
            left++;
            right = left + 1;
        }
    }
}

void Game::checkCollusion(Object* o1, Object* o2)
{
    if (o1->getIsDead() || o2->getIsDead())
        return;

    const float collision_x_offset = 10.f;
    const float collision_y_offset = 20.f;
    const float above_collision_offset = 20.f;

    // collision case between mario and turtle
    if (dynamic_cast<Mario*>(o1) != nullptr)
    {
        size_t mario_left     =  o1->sprite.getPosition().x - o1->sprite.getLocalBounds().width / 2 + collision_x_offset;
        size_t mario_right    =  o1->sprite.getPosition().x + o1->sprite.getLocalBounds().width / 2 - collision_x_offset;
        size_t mario_top      =  o1->sprite.getPosition().y - o1->sprite.getLocalBounds().height / 2 + collision_y_offset;
        size_t mario_bottom   =  o1->sprite.getPosition().y + o1->sprite.getLocalBounds().height / 2 - collision_y_offset;

        sf::RectangleShape mario_bounding(sf::Vector2f(mario_right - mario_left, mario_bottom - mario_top));
        mario_bounding.setPosition(mario_left, mario_top);
        mario_bounding.setFillColor(sf::Color::Transparent);
        mario_bounding.setOutlineColor(sf::Color::White);
        mario_bounding.setOutlineThickness(1);

        size_t turtle_left    =  o2->sprite.getPosition().x - o2->sprite.getLocalBounds().width / 2 + collision_x_offset + 5.f;
        size_t turtle_right   =  o2->sprite.getPosition().x + o2->sprite.getLocalBounds().width / 2 - collision_x_offset;
        size_t turtle_top     =  o2->sprite.getPosition().y - o2->sprite.getLocalBounds().height / 2 + collision_y_offset;
        size_t turtle_bottom  =  o2->sprite.getPosition().y + o2->sprite.getLocalBounds().height / 2 - collision_y_offset;

        sf::RectangleShape turtle_bounding(sf::Vector2f(turtle_right - turtle_left, turtle_bottom - turtle_top));
        turtle_bounding.setPosition(turtle_left, turtle_top);
        turtle_bounding.setFillColor(sf::Color::Transparent);
        turtle_bounding.setOutlineColor(sf::Color::White);
        turtle_bounding.setOutlineThickness(1);

        window_->draw(mario_bounding);
        window_->draw(turtle_bounding);

        if (mario_right < turtle_left || mario_left > turtle_right || mario_bottom < turtle_top || mario_top > turtle_bottom)
        {
            return;
        }

        if (mario_bottom <= turtle_top + above_collision_offset)
        {
            o2->fall();
            std::cout << "Turtle dead!!!" << std::endl;
        }
        else
        {
            o1->fall();
            std::cout << "Mario dies!!!" << std::endl;
        }
    }

    // 2 turtles case (surprise effect)
    else
    {
        if (!dynamic_cast<Turtle*>(o1)->getIsHide() && !dynamic_cast<Turtle*>(o2)->getIsHide() &&  o1->boundingBox().intersects(o2->boundingBox()))
        {
            dynamic_cast<Turtle*>(o1)->setSurprised();
            dynamic_cast<Turtle*>(o2)->setSurprised();
            if (o1->getPosition().x > o2->getPosition().x)
            {
                if (!dynamic_cast<Turtle*>(o1)->getSurprised())
                {
                    if (o1->getPosition().x + 10 < SCREEN_WIDTH)
                        o1->setPosition(sf::Vector2f(o1->getPosition().x + 10, o1->getPosition().y));
                }
                if (!dynamic_cast<Turtle*>(o1)->getSurprised())
                {
                    if (o2->getPosition().x - 5 > 0)
                        o2->setPosition(sf::Vector2f(o2->getPosition().x - 10, o2->getPosition().y));
                }
            }
            else
            {
                if (!dynamic_cast<Turtle*>(o1)->getSurprised())
                {
                    if (o1->getPosition().x - 5 > 0)
                        o1->setPosition(sf::Vector2f(o1->getPosition().x - 10, o1->getPosition().y));
                }
                if (!dynamic_cast<Turtle*>(o1)->getSurprised())
                {
                    if (o2->getPosition().x + 10 < SCREEN_WIDTH)
                        o2->setPosition(sf::Vector2f(o2->getPosition().x + 10, o2->getPosition().y));
                }
            }
        
        }
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
        if (dynamic_cast<Mario*>(object) != nullptr)
        {
            if (object->getVelocityY() < 0 && map_.getTile(tile_y, tile_x) == TileType::Brick)
            {
                for (Object* object : objects_)
                {
                    if (dynamic_cast<Turtle*>(object) != nullptr)
                    {
                        if (dynamic_cast<Turtle*>(object)->boundingBox().contains(x_pixel, y_pixel - 20))
                    {
                        dynamic_cast<Turtle*>(object)->setFlippedOver();
                    }
                    }
                }
            }

            if (dynamic_cast<Mario*>(object)->isJumping() && object->getVelocityY() > 0)
                object->resetState();
            else
            {
                object->setVelocityX(0.0);
                object->setVelocityY(0.0);
            }
        }
        else if (dynamic_cast<Turtle*>(object) != nullptr && map_.getTile(tile_y, tile_x) == TileType::Pipe)
            if (tile_x < 10)
                dynamic_cast<Turtle*>(object)->setInPipe(0);
            else if (tile_x > 40)
                dynamic_cast<Turtle*>(object)->setInPipe(1);
    }
}

// Destructor funtion to delete dynamic allocated objects
Game::~Game()
{
    for (Object* object : objects_)
    {
        delete object;
    }
}

// Setter function for the ScoreBoard score
void ScoreBoard::setScore(int score)
{
    this->score = score;
}

// Setter function for the Mario lives

void ScoreBoard::setLives(int lives)
{
    this->lives = lives;
}

// Getter function for the Mario lives
int ScoreBoard::getLives(void)
{
    return lives;
}
