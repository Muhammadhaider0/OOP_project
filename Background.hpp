#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <vector>

class Background {
public:
    Background(const sf::Vector2u& windowSize, const sf::Vector2f& playAreaSize);

    void render(sf::RenderWindow& window);

private:
    sf::RectangleShape background; // Solid color or textured background
    sf::Texture backgroundTexture; // Texture for the background
    std::vector<sf::RectangleShape> borders; // Borders surrounding the play area
};

#endif