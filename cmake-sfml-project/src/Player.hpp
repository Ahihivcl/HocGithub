#pragma once
#include <SFML/Graphics.hpp>
enum Direction
    {
        Down,
        Left,
        Right,
        Up
    };
class Player
{
public:
    Player(sf::Vector2f pos,sf::Window &win, sf::Texture &texture);
    void handleInput();
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition();
// private:
    
    Direction currentDirection;
    sf::Sprite sprite;
    sf::Vector2f position;
    float speed = 500.0f; // pixels per second
    sf::Vector2f movement;
    sf::Window &window;
    sf::Texture *texture;
    sf::Vector2i frameSize;
    float scale = 4;
    int currentFrame = 0, currentRow = 0, maxframes = 6, maxRows = 10;
    float animationTimer = 0.f, frameDuration = 0.1f;

    void updateAnimationRect();
};