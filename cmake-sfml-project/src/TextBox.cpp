#include "TextBox.hpp"
#include <iostream>
TextBox::TextBox(sf::Font &font, sf::Window &window) : font(font), window(window), text(font, "", 24)
{
    text.setFillColor(sf::Color::White);
    sf::Vector2 backgroundSize = {window.getSize().x * 0.8f, window.getSize().y * 0.15f};
    background.setSize(backgroundSize);
    background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black background
    background.setPosition({window.getSize().x * 0.1f, window.getSize().y * 0.75f});
    text.setPosition(background.getPosition() + sf::Vector2f(10.f, 10.f)); // Padding inside the background
}
void TextBox::setText(const std::string &str)
{
    content = str;
    ss.str(content);
}
bool TextBox::isEmpty()
{
    return content.empty();
}
bool TextBox::draw(sf::RenderWindow &window)
{
    int lineCount = 0;
    fullText = "";
    sf::Text tmpText(font, "", 24);
    tmpText.setFillColor(sf::Color::White);
    std::string word;
    // std::cout << ss.str() << std::endl;
    while (ss >> word)
    {
        if (isOutOfLine(tmpText, word))
        {
            fullText += tmpText.getString() + "\n";
            tmpText.setString(word);
            lineCount++;
        }
        else
        {
            tmpText.setString(tmpText.getString() + " " + word);
        }
        if (isOutOfBox(lineCount))
        {
            text.setString(fullText);
            return true;
        }
    }
    if(tmpText.getString() == "") return false;
    fullText += tmpText.getString();
    text.setString(fullText);
    return true;
}
bool TextBox::isOutOfLine(sf::Text str, std::string word)
{
    sf::Text tmpText = str;
    tmpText.setString(tmpText.getString() + " " + word);
    return tmpText.getGlobalBounds().size.x > background.getSize().x - 30; // 20 for padding
}
bool TextBox::isOutOfBox(int lineCount)
{
    return (lineCount + 1) * text.getCharacterSize() > background.getSize().y - 20; // 20 for padding
}
void TextBox::show(sf::RenderWindow &window, float deltaTime, float displayDuration)
{
    displayTimer += deltaTime;
    if (displayTimer >= displayDuration || state == TextBoxState::Idle)
    {
        text.setString("");
        std::cout << "Resetting TextBox. Timer: " << displayTimer << "s" << std::endl;
        state = TextBoxState::Displaying;
        displayTimer = 0.f;
        if (draw(window))
        {
            std::cout << "Drawing TextBox with content: " << text.getString().toAnsiString() << std::endl;
        }
        else
        {
            state = TextBoxState::Idle;
        }
    }
    if (state == TextBoxState::Displaying)
    {
        window.draw(background);
        window.draw(text);
    }
}
