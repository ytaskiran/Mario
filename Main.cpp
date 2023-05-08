#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>


int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mario Game");
    // Load a sprite to display
    //sf::Texture texture;
    //if (!texture.loadFromFile("cute_image.jpg"))
        //return EXIT_FAILURE;
    //sf::Sprite sprite(texture);
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("../assets/font.ttf"))
    {
        std::cout << "Unable to load the font file from " << std::filesystem::current_path() << std::endl;
        std::cin.get();
        return EXIT_FAILURE;
    }

    sf::Text text("Welcome to the Mario ", font, 40);
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
        // 
        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}