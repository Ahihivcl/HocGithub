#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "Player.hpp"
#include "TextBox.hpp"
#include "InputManager.hpp"
int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1600, 900}), "CMake SFML Project");
    window.setFramerateLimit(60);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("Assets/sprites/characters/player.png"))
    {
        std::cerr << "Failed to load player texture!" << std::endl;
        return -1;
    }
    sf::Font font;
    if (!font.openFromFile("Assets/fonts/arial.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }
    InputManager inputManager;
    TextBox text(font, window);
    sf::Text fps(font, "", 20);
    int frameCount = 0;
    float fpsTimer = 0.f;
    text.setText("Welcome to the game! This is a simple text box implementation that can handle word wrapping and display text for a certain duration. Enjoy playing!. This is a simple text box implementation that can handle word wrapping and display text for a certain duration. Enjoy playing!. This is a simple text box implementation that can handle word wrapping and display text for a certain duration. Enjoy playing!. This is a simple text box implementation that can handle word wrapping and display text for a certain duration. Enjoy playing!. This is a simple text box implementation that can handle word wrapping and display text for a certain duration. Enjoy playing!. This is a simple text box implementation that can handle word wrapping and display text for a certain duration. Enjoy playing!. This is a simple text box implementation that can handle word wrapping and display text for a certain duration. Enjoy playing!. This is a simple text box implementation that can handle word wrapping and display text for a certain duration. Enjoy playing!.");
    Player player({window.getSize().x / 2.0f, window.getSize().y / 2.0f}, window, playerTexture);
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
        
        inputManager.update();
        float time = clock.restart().asSeconds();
        if (time > 0.1f)
            time = 0.1f;
        if (window.hasFocus())
            player.handleInput(inputManager);
        player.update(time);
        // Clear the window with black color
        window.clear();
        player.draw(window);
        // text.show(window, time, 5.f);
        frameCount++;
        fpsTimer += time;
        if (fpsTimer >= 1.0f)
        {
            fps.setString("FPS: " + std::to_string(frameCount));
            frameCount = 0;
            fpsTimer -= 1.0f;
        }
        window.draw(fps);
        window.display();
    }
}
