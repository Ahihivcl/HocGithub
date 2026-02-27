#include "InputManager.hpp"
InputManager::InputManager() : currentStates(sf::Keyboard::KeyCount, false),
                             previousStates(sf::Keyboard::KeyCount, false),
                              bindings((int)Action::Count, sf::Keyboard::Key::Unknown)
{
    setupDefaultBindings();
    
}
void InputManager::setupDefaultBindings()
{
    bindKey(Action::MoveUp, sf::Keyboard::Key::W);
    bindKey(Action::MoveDown, sf::Keyboard::Key::S);
    bindKey(Action::MoveLeft, sf::Keyboard::Key::A);
    bindKey(Action::MoveRight, sf::Keyboard::Key::D);
    bindKey(Action::Attack, sf::Keyboard::Key::Space);
}
void InputManager::bindKey(Action action, sf::Keyboard::Key key)
{
    bindings[(int)action] = (key);
}
void InputManager::update()
{
    previousStates = currentStates;
    for (size_t i = 0; i < bindings.size(); i++)
    {
        if (bindings[i] != sf::Keyboard::Key::Unknown)
        {
            currentStates[i] = sf::Keyboard::isKeyPressed(bindings[i]);
        }
    }
}
bool InputManager::isActionDown(Action action)
{
    sf::Keyboard::Key key = bindings[(int)action];
    if (key == sf::Keyboard::Key::Unknown)
        return false;
    return currentStates[(int)action];
}
bool InputManager::isActionPressed(Action action)
{
    sf::Keyboard::Key key = bindings[(int)action];
    if (key == sf::Keyboard::Key::Unknown)
        return false;
    return currentStates[(int)action] && !previousStates[(int)action];
}
bool InputManager::isActionReleased(Action action)
{
    auto key = bindings[(int)action];
    if(key == sf::Keyboard::Key::Unknown)
    {
        return false;
    }
    return !currentStates[(int)action] && previousStates[(int)action];
}
