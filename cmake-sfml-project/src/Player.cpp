#include "Player.hpp"
#include "InputManager.hpp"
Player::Player(sf::Vector2f pos, sf::Window &win, sf::Texture &tex) : position(pos), window(win), texture(&tex), sprite(tex)
{
    frameSize = {(int)texture->getSize().x / maxframes, (int)texture->getSize().y / maxRows};
    sf::IntRect initialRec({0, 0}, {frameSize.x, frameSize.y});
    sprite.setTextureRect(initialRec);
    sprite.setOrigin({frameSize.x / 2.0f, frameSize.y / 2.0f});
    sprite.setPosition(position);
    sprite.setScale({scale, scale});
    timeSinceLastAnimation = 0.f;
    currentDirection = Down;
    currentState = PlayerState::Idle;
    updateAnimationRect();
}
void Player::handleInput(InputManager &inputManager)
{
    movement = {0.0f, 0.0f};
    if (window.hasFocus() == false)
        return;
    if (currentState != PlayerState::Attacking)
    {
        if (inputManager.isActionDown(Action::MoveUp))
        {
            movement.y -= 1;
        }
        if (inputManager.isActionDown(Action::MoveDown))
        {
            movement.y += 1;
        }
        if (inputManager.isActionDown(Action::MoveLeft))
        {
            movement.x -= 1;
        }
        if (inputManager.isActionDown(Action::MoveRight))
        {
            movement.x += 1;
        }
        if (movement.x != 0 || movement.y != 0)
        {
            movement = movement.normalized();
            currentState = PlayerState::Walking;
        }
        else
        {
            currentState = PlayerState::Idle;
        }
    }
    if (inputManager.isActionDown(Action::Attack) && currentState == PlayerState::Idle)
    {
        currentState = PlayerState::Attacking;
        currentFrame = 0;
        animationTimer = 0.f;
        movement = {0.0f, 0.0f};
    }
}
void Player::update(float deltaTime)
{
    position += movement * speed * deltaTime;
    position.x = std::clamp(position.x, 0.0f, (window.getSize().x) * 1.0f);
    position.y = std::clamp(position.y, 0.0f, (window.getSize().y) * 1.0f);
    sprite.setPosition(position);
    if (currentState == PlayerState::Idle)
    {
        frameDuration = 0.5f;
    }
    else
        frameDuration = 0.1f;
    if(animationTimer >= 1.5f)
    {
        animationTimer = 0.1f;
    }
    if (currentState == PlayerState::Walking)
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
    else if (currentState == PlayerState::Attacking)
    {
        if (currentDirection == Down)
            currentRow = 6;
        else if (currentDirection == Up)
            currentRow = 8;
        else
            currentRow = 7;
        animationTimer += deltaTime;
        if (animationTimer >= frameDuration)
        {
            animationTimer -= frameDuration;
            currentFrame++;
            if (currentFrame >= 3)
            {
                currentState = PlayerState::Idle;
                // Reset to idle frame
                currentFrame = 0;
                currentRow = (currentDirection == Down) ? 0 : (currentDirection == Up) ? 2
                                                                                       : 1;
            }
        }
    }
    else
    {
        // currentFrame = 0;
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
        // animationTimer = 0.f;
        // frameDuration = 0.5f;
        animationTimer += deltaTime;
        if (animationTimer >= frameDuration)
        {
            animationTimer -= frameDuration;
            currentFrame = (currentFrame + 1) % maxframes;
        }
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