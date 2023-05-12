#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Mario Game");
    window.setVerticalSyncEnabled(true);

    Game game(&window);
    game.createMario();
   
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
        }
        // Clear screen
        window.clear();
        // Draw the sprite
        //window.draw(sprite);

        game.drawBackground();

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}