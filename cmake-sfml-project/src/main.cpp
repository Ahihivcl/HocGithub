#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        std::cout << "Ditmemay";
        // Clear the window with black color
        window.clear();
        window.display();
    }
}
