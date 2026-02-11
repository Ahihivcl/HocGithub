#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "Player.hpp"
int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1600, 900}), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("Assets/sprites/characters/player.png"))
    {
        std::cerr << "Failed to load player texture!" << std::endl;
        return -1;
    }
    Player player({window.getSize().x / 2.0f, window.getSize().y / 2.0f}, window, playerTexture);
    // Player player();
    sf::Clock clock;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        float time = clock.restart().asSeconds();
        if (time > 0.1f)
            time = 0.1f;
        if (window.hasFocus())
            player.handleInput();
        player.update(time);
        // Clear the window with black color
        window.clear();
        player.draw(window);
        window.display();
    }
}
