#pragma once
#include <SFML/Graphics.hpp>
#include "InputManager.hpp"
enum Direction
    {
        Down,
        Left,
        Right,
        Up
    };
enum class PlayerState
{
    Idle,
    Walking,
    Attacking,
};
class Player
{
public:
    Player(sf::Vector2f pos,sf::Window &win, sf::Texture &texture);
    void handleInput(InputManager &inputManager);
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition();
private:
    
    Direction currentDirection;
    PlayerState currentState;
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
    float timeSinceLastAnimation = 0.f;
    void updateAnimationRect();
    void loadAnimation(float deltaTime, int row, int minCol, int maxCol, float frameDuration, float animationDuration, bool loop);
};