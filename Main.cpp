#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Parameters.h"


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Mario Game");
    window.setVerticalSyncEnabled(true);

    Game game(&window);
    game.createMario();
    game.createTurtles(5); 
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    if (game.status == Game::Status::MainMenu)
                        game.status = Game::Status::Begin;
                    else if (game.status == Game::Status::GameOver || game.status == Game::Status::Won)
                    {
                        game.status = Game::Status::MainMenu;
                        game.restartGame(true);
                    }
                }
            }
        }
        // Clear screen
        window.clear();

        if (game.getRemainingLives() == 0)
            game.status = Game::Status::GameOver;

        else if (game.getScore() == 500)
            game.status = Game::Status::Won;

        if (game.status == Game::Status::MainMenu)
        {
            window.clear(sf::Color(15, 15, 40));
            game.mainMenu();
        }
        else if (game.status == Game::Status::GameOver)
        {
            window.clear(sf::Color(20, 5, 5));
            game.gameOver();
        }
        else if (game.status == Game::Status::Won)
        {
            window.clear(sf::Color(5, 20, 5));
            game.won();
        }
        else if (game.status == Game::Status::Begin)
        {
            game.updateObjects();
            game.drawBackground();
        }

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}