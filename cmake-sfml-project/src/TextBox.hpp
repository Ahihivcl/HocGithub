#pragma once
#include <SFML/Graphics.hpp>
enum class TextBoxState
{
    Idle,
    Displaying,
    Done
};
class TextBox
{
private:
    sf::Text text;
    std::string fullText;
    std::string content;
    sf::Font &font;
    sf::RectangleShape background;
    sf::Window &window;
    std::stringstream ss;
    float displayTimer = 0.f;
    TextBoxState state = TextBoxState::Idle;
public:
    TextBox(sf::Font &font, sf::Window &window);
    void setText(const std::string &str);
    bool draw(sf::RenderWindow &window);
    bool isEmpty();
    bool isOutOfLine(sf::Text str, std::string word);
    bool isOutOfBox(int lineCount);
    void show(sf::RenderWindow &window, float deltaTime, float displayDuration = 5.f);
};