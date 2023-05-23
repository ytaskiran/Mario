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
                    game.status =  Game::Status::Begin;
                }
            }
        }
        // Clear screen
        window.clear();

        if (game.status == Game::Status::MainMenu)
        {
            window.clear(sf::Color(18, 23, 53));
            if (game.mainMenu())
                return EXIT_FAILURE;
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