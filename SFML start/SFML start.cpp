// SFML start.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

// Window size
const int WIDTH = 800;
const int HEIGHT = 600;

// Enemy class
class Enemy {
public:
    sf::RectangleShape shape;
    float speed = 2.0f;

    Enemy(float x, float y) {
        shape.setSize(sf::Vector2f(40, 40));
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
    }

    void move() {
        shape.move(speed, 0);
    }

    bool reachedEnd() {
        return shape.getPosition().x >= WIDTH;
    }
};

// Bullet class
class Bullet {
public:
    sf::CircleShape shape;
    float speed = 5.0f;

    Bullet(float x, float y) {
        shape.setRadius(5);
        shape.setFillColor(sf::Color::White);
        shape.setPosition(x, y);
    }

    void move() {
        shape.move(speed, 0);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Simple Tower Defense");
    sf::RectangleShape tower(sf::Vector2f(50, 100));
    tower.setFillColor(sf::Color::Blue);
    tower.setPosition(50, HEIGHT / 2 - 50);

    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;

    sf::Clock enemySpawnClock;
    sf::Clock bulletClock;

    bool gameOver = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (!gameOver) {
            // Spawn enemies every 2 seconds
            if (enemySpawnClock.getElapsedTime().asSeconds() > 2) {
                enemies.push_back(Enemy(0, rand() % (HEIGHT - 40)));
                enemySpawnClock.restart();
            }

            // Shoot bullets every 0.5 seconds
            if (bulletClock.getElapsedTime().asSeconds() > 0.5) {
                bullets.push_back(Bullet(100, HEIGHT / 2));
                bulletClock.restart();
            }

            // Move bullets
            for (auto& bullet : bullets) bullet.move();

            // Move enemies
            for (auto& enemy : enemies) enemy.move();

            // Check for collisions
            for (auto it = bullets.begin(); it != bullets.end();) {
                bool bulletDeleted = false;
                for (auto jt = enemies.begin(); jt != enemies.end();) {
                    if (it->shape.getGlobalBounds().intersects(jt->shape.getGlobalBounds())) {
                        it = bullets.erase(it);
                        jt = enemies.erase(jt);
                        bulletDeleted = true;
                        break;
                    }
                    else {
                        ++jt;
                    }
                }
                if (!bulletDeleted) ++it;
            }

            // Check if an enemy reaches the right side
            for (auto& enemy : enemies) {
                if (enemy.reachedEnd()) {
                    gameOver = true;
                    break;
                }
            }
        }

        window.clear();

        if (gameOver) {
            sf::Font font;
            font.loadFromFile("arial.ttf");
            sf::Text text("YOU DIED", font, 50);
            text.setFillColor(sf::Color::Red);
            text.setPosition(WIDTH / 2 - 100, HEIGHT / 2);
            window.draw(text);
        }
        else {
            window.draw(tower);
            for (auto& enemy : enemies) window.draw(enemy.shape);
            for (auto& bullet : bullets) window.draw(bullet.shape);
        }

        window.display();
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
