#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
enum class Action
{
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    Attack,
    Count
};
class InputManager
{
    private:
    std::vector<bool> currentStates;
    std::vector<bool> previousStates;
    std::vector<sf::Keyboard::Key> bindings;

    public:
    InputManager();
    void setupDefaultBindings();
    void update();
    void bindKey(Action action, sf::Keyboard::Key key);
    bool isActionPressed(Action action);
    bool isActionDown(Action action);
    bool isActionReleased(Action action);
    
};