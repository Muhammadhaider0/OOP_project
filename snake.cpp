#include <SFML/Graphics.hpp>
#include "constant.hpp"
// Include the SFML library for graphics rendering
// Include the header file "constant.hpp" which contains constants like width, height, and blockSize

// Define the structure to represent a segment of the snake
struct SnakeSegment {
    int x, y; // Position of the segment in the grid
};

// Define the Snake class to manage snake behavior
class Snake {
public:
    SnakeSegment segments[100]; // Array to store snake segments, maximum length is 100
    int length; // Current length of the snake
    int dx, dy; // Direction of movement: dx for horizontal, dy for vertical

    // Constructor to initialize the snake
    Snake() {
        length = 2; // Start with 2 segments
        dx = 1; // Initial direction: moving right
        dy = 0; // No vertical movement

        // Initialize the snake in the middle of the screen
        segments[0].x = width / 2 / blockSize; // Head segment position
        segments[0].y = height / 2 / blockSize;
        segments[1].x = segments[0].x - 1; // Second segment directly to the left of the head
        segments[1].y = segments[0].y;
    }

    // Function to move the snake in the current direction
    void move() {
        // Move each segment to the position of the segment ahead of it
        for (int i = length - 1; i > 0; --i) {
            segments[i] = segments[i - 1];
        }
        // Update the head position based on the direction
        segments[0].x += dx;
        segments[0].y += dy;
    }

    // Function to grow the snake by adding a new segment
    void grow() {
        if (length < 100) { // Ensure the maximum length is not exceeded
            segments[length] = segments[length - 1]; // Add a new segment at the end
            ++length; // Increase the length
        }
    }

    // Function to check if the snake has collided with itself or the boundaries
    bool checkCollision() {
        // Check if the head collides with any other segment
        for (int i = 1; i < length; ++i) {
            if (segments[i].x == segments[0].x && segments[i].y == segments[0].y)
                return true; // Collision with itself
        }
        // Check if the head is out of bounds
        if (segments[0].x < 0 || segments[0].x >= width / blockSize || segments[0].y < 0 || segments[0].y >= height / blockSize)
            return true; // Collision with walls

        return false; // No collision
    }

    // Function to draw the snake on the screen
    void draw(sf::RenderWindow& window) {
        sf::RectangleShape block(sf::Vector2f(blockSize - 1, blockSize - 1)); // Create a block slightly smaller than blockSize
        block.setFillColor(sf::Color::Green); // Set the block color to green

        // Draw each segment of the snake
        for (int i = 0; i < length; ++i) {
            block.setPosition(segments[i].x * blockSize, segments[i].y * blockSize); // Position the block
            window.draw(block); // Draw the block
        }
    }
};
