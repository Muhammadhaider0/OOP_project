#include "Background.hpp"

Background::Background(const sf::Vector2u& windowSize, const sf::Vector2f& playAreaSize) {
    // Load the texture from a file
    if (!backgroundTexture.loadFromFile("C:/Users/haide/OneDrive/Desktop/backgroun.jpg")) {
        // Handle error (e.g., log or throw an exception)
        throw std::runtime_error("Failed to load background texture");
    }

    // Set the texture to repeat
    backgroundTexture.setRepeated(true);

    // Configure the background rectangle
    background.setSize(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)));
    background.setTexture(&backgroundTexture);
    background.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));

    // Border thickness
    float borderThickness = 10.f;

    // Top border
    sf::RectangleShape topBorder(sf::Vector2f(playAreaSize.x, borderThickness));
    topBorder.setFillColor(sf::Color::Red);
    topBorder.setPosition(0.f, 0.f); // Top-left corner
    borders.push_back(topBorder);

    // Bottom border
    sf::RectangleShape bottomBorder(sf::Vector2f(playAreaSize.x, borderThickness));
    bottomBorder.setFillColor(sf::Color::Red);
    bottomBorder.setPosition(0.f, playAreaSize.y - borderThickness); // Bottom of play area
    borders.push_back(bottomBorder);

    // Left border
    sf::RectangleShape leftBorder(sf::Vector2f(borderThickness, playAreaSize.y));
    leftBorder.setFillColor(sf::Color::Red);
    leftBorder.setPosition(0.f, 0.f); // Top-left corner
    borders.push_back(leftBorder);

    // Right border
    sf::RectangleShape rightBorder(sf::Vector2f(borderThickness, playAreaSize.y));
    rightBorder.setFillColor(sf::Color::Red);
    rightBorder.setPosition(playAreaSize.x - borderThickness, 0.f); // Top-right corner
    borders.push_back(rightBorder);
}

void Background::render(sf::RenderWindow& window) {
    // Draw the background
    window.draw(background);

    // Draw the borders
    for (const auto& border : borders) {
        window.draw(border);
    }
}