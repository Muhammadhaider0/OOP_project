#include <SFML/Graphics.hpp>
#include "constant.hpp"
//const int width = 800, height = 600, blockSize = 16;

struct SnakeSegment {
    int x, y;
};

class Snake {
public:
    SnakeSegment segments[100];
    int length;
    int dx, dy;

    Snake() {
        length = 2;
        dx = 1; // Initial direction: moving right
        dy = 0;

        // Start snake in the middle of the screen
        segments[0].x = width / 2 / blockSize;
        segments[0].y = height / 2 / blockSize;
        segments[1].x = segments[0].x - 1;
        segments[1].y = segments[0].y;
    }

    void move() {
        for (int i = length - 1; i > 0; --i) {
            segments[i] = segments[i - 1];
        }
        segments[0].x += dx;
        segments[0].y += dy;
    }

    void grow() {
        if (length < 100) {
            segments[length] = segments[length - 1];
            ++length;
        }
    }

    bool checkCollision() {
        for (int i = 1; i < length; ++i) {
            if (segments[i].x == segments[0].x && segments[i].y == segments[0].y)
                return true;
        }
        if (segments[0].x < 0 || segments[0].x >= width / blockSize || segments[0].y < 0 || segments[0].y >= height / blockSize)
            return true;

        return false;
    }

    void draw(sf::RenderWindow& window) {
        sf::RectangleShape block(sf::Vector2f(blockSize - 1, blockSize - 1));
        block.setFillColor(sf::Color::Green);

        for (int i = 0; i < length; ++i) {
            block.setPosition(segments[i].x * blockSize, segments[i].y * blockSize);
            window.draw(block);
        }
    }
};
