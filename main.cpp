#include "Snake.cpp"
#include "Background.hpp"
#include "constant.hpp" 
#include <SFML/Graphics.hpp>
#include <ctime> // For time-based random numbers

int getRandom(int max) {
    return rand() % max; // Generate a random number between 0 and max-1
}

int main() {
    srand(time(0)); // Seed for random number generation

    sf::RenderWindow window(sf::VideoMode(width, height), "Snake Game");
    window.setFramerateLimit(10);

    Background background(sf::Vector2u(width, height), sf::Vector2f(width, height));


    Snake snake;
    sf::Vector2i food(getRandom(width / blockSize), getRandom(height / blockSize));
    sf::Vector2i obstacle(-1, -1);
    int score = 0;

    sf::Font font;
    if (!font.loadFromFile("aerial.ttf")) {
        return -1; // Exit if font fails to load
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Control snake direction
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake.dy != 1) {
            snake.dx = 0;
            snake.dy = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake.dy != -1) {
            snake.dx = 0;
            snake.dy = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake.dx != 1) {
            snake.dx = -1;
            snake.dy = 0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake.dx != -1) {
            snake.dx = 1;
            snake.dy = 0;
        }

        // Move snake
        snake.move();

        // Check for collisions
        if (snake.checkCollision() || (snake.segments[0].x == obstacle.x && snake.segments[0].y == obstacle.y)) {
            snake = Snake();
            score = 0;
            obstacle = sf::Vector2i(-1, -1); // Reset obstacle
        }

        // Check if food is eaten
        if (snake.segments[0].x == food.x && snake.segments[0].y == food.y) {
            snake.grow();
            score++;
            food = sf::Vector2i(getRandom(width / blockSize), getRandom(height / blockSize));

            // Add an obstacle every 5 points
            //if (score == getRandom(Width/BlockSize)) {
            if (score % 5 == 0) {
                obstacle = sf::Vector2i(getRandom(width / blockSize), getRandom(height / blockSize));
            }
        }

        // Render the game
        window.clear();

        background.render(window);


        // Draw food
        sf::RectangleShape foodShape(sf::Vector2f(blockSize - 1, blockSize - 1));
        foodShape.setFillColor(sf::Color::Red);
        foodShape.setPosition(food.x * blockSize, food.y * blockSize);
        window.draw(foodShape);

        // Draw obstacle if it exists
        if (obstacle.x != -1 && obstacle.y != -1) {
            sf::RectangleShape obstacleShape(sf::Vector2f(blockSize - 1, blockSize - 1));
            obstacleShape.setFillColor(sf::Color::Blue);
            obstacleShape.setPosition(obstacle.x * blockSize, obstacle.y * blockSize);
            window.draw(obstacleShape);
        }

        // Draw snake
        snake.draw(window);

        // Draw score
        sf::Text scoreText;
        scoreText.setFont(font);
        scoreText.setString("Score: " + std::to_string(score));
        scoreText.setCharacterSize(20);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);
        window.draw(scoreText);

        window.display();
    }

    return 0;
}
