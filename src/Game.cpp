#include "Game.h"

// Game class constructor function
Game::Game(sf::RenderWindow* window) : window_(window), status(Status::MainMenu)
{
    // Loading the map textures
    lives_texture.loadFromFile("../assets/mariohead.png");
    mario_menu.loadFromFile("../assets/mario_menu.png");
    font.loadFromFile("../assets/font.ttf");

    // Initialize scoreboard variables
    scoreboard_.setLives(MARIO_MAX_LIVES);
    scoreboard_.setScore(0);
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

    // Draw the remaining Mario lives 
    drawGameInfo();
}
           
// Draw the score and remaining lives
void Game::drawGameInfo()
{
    sprite.setTexture(lives_texture);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale(0.8, 0.8);

    // Draw live symbols according to remaining live count 
    for (int i = 1; i <= scoreboard_.getLives(); i++)
    {
        sprite.setPosition(175.f + 40.f * i, 30.f);
        window_->draw(sprite);
    }

    sprite.setScale(1, 1);

    // Writing score info to the screen
    std::string score("Score: ");
    score += std::to_string(scoreboard_.getScore());
    sf::Text score_text(score, font, 25);
    score_text.setPosition(30.f, 12.f);
    window_->draw(score_text);
}

// Creating a new mario and inserting it to the objects_ array
void Game::createMario()
{
    objects_.emplace_back(new Mario());
}

// Create a given number of turtles and instert it to the objects_ array. 
// Turtles initialized in map with a given delay in constructor as a parameter.  
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
        }
        else
        {
            // i * 50 : Delay time for initializing in map
            turtle = new Turtle(i * 100 + 5, Object::Direction::LEFT);
            pos.x = 680.0f;
        }

        // Sets the turtle initial pos according to right or left initialization
        turtle->setPosition(pos);

        // Adds the turtle to objects_ array
        objects_.emplace_back(turtle);
    }

}

// Main menu drawing
void Game::mainMenu()
{
    // Welcome text writing to the screen
    sf::Text welcome_text("Welcome to the Mario", font, 40);
    welcome_text.setPosition(SCREEN_WIDTH / 2, 100.f);
    welcome_text.setOrigin(welcome_text.getLocalBounds().width / 2, welcome_text.getLocalBounds().height / 2);
    welcome_text.setFillColor(sf::Color::Red);
    welcome_text.setStyle(sf::Text::Bold);

    // Start text writing to the screen
    sf::Text start_text("Press ENTER to Start", font, 30);
    start_text.setPosition(SCREEN_WIDTH / 2, 250.f);
    start_text.setOrigin(start_text.getLocalBounds().width / 2, start_text.getLocalBounds().height / 2);

    // Mario menu image drawing 
    sf::Sprite mario;
    mario.setTexture(mario_menu);
    mario.setScale(2, 2);
    mario.setPosition(SCREEN_WIDTH / 2, 450.f);
    mario.setOrigin(mario.getLocalBounds().width / 2, mario.getLocalBounds().height / 2);

    // Drawing the above textures to the window 
    window_->draw(welcome_text);
    window_->draw(start_text);
    window_->draw(mario);
}

// Gameover screen drawing function
void Game::gameOver()
{
    // Gameover text setting
    sf::Text game_over("GAME OVER", font, 64);
    game_over.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.f);
    game_over.setOrigin(game_over.getLocalBounds().width / 2, game_over.getLocalBounds().height / 2);
    game_over.setFillColor(sf::Color::Red);
    game_over.setStyle(sf::Text::Bold);

    // Return menu text setting
    sf::Text return_menu("Press ENTER to Return Main Menu", font, 32);
    return_menu.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100.f);
    return_menu.setOrigin(return_menu.getLocalBounds().width / 2, return_menu.getLocalBounds().height / 2);
    return_menu.setFillColor(sf::Color::White);
    return_menu.setStyle(sf::Text::Bold);

    // Drawing the above text objects to the window
    window_->draw(game_over);
    window_->draw(return_menu);
}

// Won screen drawing function
void Game::won()
{
    // Won text setting
    sf::Text won("YOU WON", font, 64);
    won.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100.f);
    won.setOrigin(won.getLocalBounds().width / 2, won.getLocalBounds().height / 2);
    won.setFillColor(sf::Color::Green);
    won.setStyle(sf::Text::Bold);

    // To return menu text setting
    sf::Text return_menu("Press ENTER to Return Main Menu", font, 32);
    return_menu.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100.f);
    return_menu.setOrigin(return_menu.getLocalBounds().width / 2, return_menu.getLocalBounds().height / 2);
    return_menu.setFillColor(sf::Color::White);
    return_menu.setStyle(sf::Text::Bold);

    // Drawing above objects to the window
    window_->draw(won);
    window_->draw(return_menu);
}

// Getter function for the getScore variable
int Game::getScore()
{
    return scoreboard_.getScore();
}

// Getter function for the getLives variable
int Game::getRemainingLives()
{
    return scoreboard_.getLives();
}

// Checks given object is on floor or not
bool Game::onFloor(Object* object)
{
    float x_pixel{}; // x coordinate as a pixel
    float y_pixel{}; // y coordinate as a pixel
    
    // Calcualate next pixel values to determine on floor state.
    if (object->getVelocityX() > 0)
        x_pixel = object->getPosition().x + object->sprite.getGlobalBounds().width / 2;
    else
        x_pixel = object->getPosition().x;
    if (object->getVelocityY() > 0)
        y_pixel = object->getPosition().y + object->sprite.getGlobalBounds().height / 2;
    else
        y_pixel = object->getPosition().y;

    // Converting pixel coordinates to tile array coordinates
    float tile_x = x_pixel / TileMap::TILE_SIZE;
    float tile_y = y_pixel / TileMap::TILE_SIZE;
    
    // bottom left tile
    int tile0_x = floor(tile_x);
    int tile0_y = ceil(tile_y);

    // bottom right tile
    int tile1_x = ceil(tile_x);
    int tile1_y = ceil(tile_y);

    // Limit the tile values to the frame sizes
    if (tile0_x < 0) tile0_x = 0;
    if (tile0_x > (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1) tile0_x = (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1;
    if (tile1_x > (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1) tile1_x = (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1;
    if (tile0_y < 0) tile0_y = 0; if (tile1_y < 0) tile1_y = 0;

    // Determine onFloor state acording to tile coordinate values
    if ((map_.getTile(tile0_y, tile0_x) == TileType::Floor or map_.getTile(tile1_y, tile1_x) == TileType::Floor or
         map_.getTile(tile0_y, tile0_x) == TileType::Brick or map_.getTile(tile1_y, tile1_x) == TileType::Brick) and object->getVelocityY() > 0)
    {
        if (dynamic_cast<Mario*>(object) != nullptr)
            object->sprite.setPosition(object->sprite.getPosition().x, tile0_y * TileMap::TILE_SIZE - 30); // consistent movement
        else if (dynamic_cast<Turtle*>(object) != nullptr)
            object->sprite.setPosition(object->sprite.getPosition().x, tile0_y * TileMap::TILE_SIZE - 20); // consistent movement

        // Set V speeed to 0, to stay above floor
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
    // Iterate over the objects array
    for (Object* object : objects_)
    {
        auto pos = object->getPosition();

        // Mario object case
        if (dynamic_cast<Mario*>(object) != nullptr)
        {
            // mario fail state
            if (marioFail(dynamic_cast<Mario*>(object)))
            {
                restartGame(false);
                return;
            }

            // Update the mario according to pressed key
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                object->jump();
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
            // No left,right or up key pressed
            else
            {
                object->update(Object::Direction::FIXED);
            }
        }
        else  // Turtle case
        {
            float _vx = object->getVelocityX();
            // Update the turtle according to previous velocity
            if (_vx > 0)
                object->update(Object::Direction::RIGHT);
            else if (_vx < 0)
                object->update(Object::Direction::LEFT);
            else
                dynamic_cast<Turtle*>(object)->changeDirection();
        }

        // If object not dead, check the onFloor and checkObstacle cases
        if (!object->getIsDead())
        {
            onFloor(object);
            checkObstacle(object);
        }

        // Move the object, after the update, onFloor and obstacle check 
        object->move();
    }
    // Check the collision of the two object
    checkcollision();

}

// Check the collision of the every two object in the objects array
void Game::checkcollision()
{
    size_t left = 0;
    size_t right = 1;

    // Iterate over every object couple
    while (right < objects_.size())
    {
        checkcollision(objects_[left], objects_[right]);
        right++;

        if (right == objects_.size())
        {
            left++;
            right = left + 1;
        }
    }
}

// Checks collision of two given object
void Game::checkcollision(Object* o1, Object* o2)
{
    // If one of the object is dead, no need to check collision
    if (o1->getIsDead() || o2->getIsDead())
        return;

    // Define the collision offset values
    const float collision_x_offset = 10.f;
    const float collision_y_offset = 20.f;
    const float above_collision_offset = 20.f;

    // collision case between mario and turtle
    if (dynamic_cast<Mario*>(o1) != nullptr)
    {
        // Get the mario corner points 
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

        if (mario_right < turtle_left || mario_left > turtle_right || mario_bottom < turtle_top || mario_top > turtle_bottom)
        {
            return;
        }

        if (mario_bottom <= turtle_top + above_collision_offset)
        {
            o2->fall();
            scoreboard_.setScore(scoreboard_.getScore() + 100);
        }
        else
        {
            if (dynamic_cast<Turtle*>(o2)->getFlippedOver())
            {
                o2->fall();
                scoreboard_.setScore(scoreboard_.getScore() + 100);
            }
            else
            {
                o1->fall();
                scoreboard_.setLives(scoreboard_.getLives() - 1);
            }
        }
    }

    // 2 turtles case (surprise effect)
    else
    {
        // If two turtle meet, they get surprised and change their directions
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

    // If objects not moving, no need to check
    if (object->getVelocityX() == 0 and object->getVelocityY() == 0)
        return;

    // Calculate the next coordinates according to velocity

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

    // Limit the coordinates
    if (tile_x < 0) tile_x = 0;
    if (tile_x > (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1) tile_x = (SCREEN_WIDTH / TileMap::TILE_SIZE) - 1;
    if (tile_y < 0) tile_y = 0;

    // Checks the tile is empty or not, to define obstacle state
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

// Restart the game
void Game::restartGame(bool begin)
{
    // Initialize objects again
    for (int i = 0; i < objects_.size(); i++)
    {
        if (dynamic_cast<Turtle*>(objects_[i]) != nullptr)
        {
            Turtle* turtle = dynamic_cast<Turtle*>(objects_[i]);

            sf::Vector2f pos;
            pos.y = 75.0f;

            // Turtles initialized left and right in turn
            if (i % 2 == 0)
            {
                turtle->setInitDelay((i - 1) * 100 + 10);
                turtle->setHeading(Object::Direction::RIGHT);
                pos.x = 118.0f;
            }
            else
            {
                turtle->setInitDelay((i - 1) * 100 + 5);
                turtle->setHeading(Object::Direction::LEFT);
                pos.x = 680.0f;
            }

            // Sets the turtle initial pos according to right or left initialization
            turtle->setPosition(pos);
        }
        objects_[i]->initialize();
    }

    // Sets the scoreboard variables
    if (begin)
        scoreboard_.setLives(3);

    scoreboard_.setScore(0);
}

// returns the mario is failed or not
bool Game::marioFail(Mario* m)
{
    if (m->getIsDead() && m->sprite.getPosition().y > SCREEN_HEIGHT * 3)
    {
        return true;
    }

    return false;
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

// Getter function for the game score
int ScoreBoard::getScore(void)
{
    return score;
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
