#include "Player.hpp"
Player::Player(sf::Vector2f pos, sf::Window &win, sf::Texture &tex) : position(pos), window(win), texture(&tex), sprite(tex)
{
    frameSize = {(int)texture->getSize().x / maxframes, (int)texture->getSize().y / maxRows};
    sf::IntRect initialRec({0, 0}, {frameSize.x, frameSize.y});
    sprite.setTextureRect(initialRec);
    sprite.setOrigin({frameSize.x / 2.0f, frameSize.y / 2.0f});
    sprite.setPosition(position);
    sprite.setScale({scale, scale});
    updateAnimationRect();
}
void Player::handleInput()
{
    movement = {0.0f, 0.0f};
    if (window.hasFocus() == false)
        return;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
    {
        movement.y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
    {
        movement.y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
    {
        movement.x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
    {
        movement.x += 1;
    }
    if (movement.x != 0 || movement.y != 0)
        movement = movement.normalized();
}
void Player::update(float deltaTime)
{
    position += movement * speed * deltaTime;

    position.x = std::clamp(position.x, 0.0f, (window.getSize().x) * 1.0f);
    position.y = std::clamp(position.y, 0.0f, (window.getSize().y) * 1.0f);
    sprite.setPosition(position);
    bool isMoving = (movement.x != 0.0f || movement.y != 0.0f);
    if (isMoving)
    {
        if (movement.y > 0)
        {
            currentRow = 3; // Down
            currentDirection = Down;
        }
        else if (movement.y < 0)
        {
            currentRow = 5; // Up
            currentDirection = Up;
        }
        else if (movement.x < 0)
        {
            currentRow = 4; // Left
            currentDirection = Left;
        }
        else if (movement.x > 0)
        {
            currentRow = 4; // Right
            currentDirection = Right;
        }
        animationTimer += deltaTime;
        if (animationTimer >= frameDuration)
        {
            animationTimer -= frameDuration;
            currentFrame = (currentFrame + 1) % maxframes;
        }
    }
    else
    {
        currentFrame = 0;
        if (currentDirection == Down)
        {
            currentRow = 0; // Down
            currentDirection = Down;
        }
        else if (currentDirection == Up)
        {
            currentRow = 2; // Up
            currentDirection = Up;
        }
        else if (currentDirection == Left)
        {
            currentRow = 1; // Left
            currentDirection = Left;
        }
        else if (currentDirection == Right)
        {
            currentRow = 1; // Right
            currentDirection = Right;
        }
        animationTimer = 0.f;
    }
    if (currentDirection == Left)
    {
        sprite.setScale({-scale, scale});
    }
    else
    {
        sprite.setScale({scale, scale});
    }
    updateAnimationRect();
}
void Player::updateAnimationRect()
{
    sf::IntRect rect;
    rect.position = {currentFrame * frameSize.x, currentRow * frameSize.y};
    rect.size = {frameSize.x, frameSize.y};
    sprite.setTextureRect(rect);
}
void Player::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}
sf::Vector2f Player::getPosition()
{
    return sprite.getPosition();
}