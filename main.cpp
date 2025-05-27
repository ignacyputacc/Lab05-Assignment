#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CustomSprite : public sf::Sprite {
public:
    void setBounds(int left, int right, int top, int bottom) {
        bound_top = top;
        bound_bottom = bottom;
        bound_right = right;
        bound_left = left;
    }

    bool Collision_T(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds) {
        return ((guy_bounds.top + guy_bounds.height >= wall_bounds.top - 3) &&
                (guy_bounds.top < wall_bounds.top) &&
                (guy_bounds.left + guy_bounds.width > wall_bounds.left + 3) &&
                (guy_bounds.left < wall_bounds.left + wall_bounds.width - 3));
    }

    bool Collision_B(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds) {
        return ((guy_bounds.top <= wall_bounds.top + wall_bounds.height + 3) &&
                (guy_bounds.top > wall_bounds.top) &&
                (guy_bounds.left + guy_bounds.width > wall_bounds.left + 3) &&
                (guy_bounds.left < wall_bounds.left + wall_bounds.width - 3));
    }

    bool Collision_L(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds) {
        return ((guy_bounds.left <= wall_bounds.left + wall_bounds.width + 3) &&
                (guy_bounds.left > wall_bounds.left) &&
                (guy_bounds.top + guy_bounds.height > wall_bounds.top + 3) &&
                (guy_bounds.top < wall_bounds.top + wall_bounds.height - 3));
    }

    bool Collision_R(sf::FloatRect wall_bounds, sf::FloatRect guy_bounds) {
        return ((guy_bounds.left + guy_bounds.width >= wall_bounds.left - 3) &&
                (guy_bounds.left < wall_bounds.left) &&
                (guy_bounds.top + guy_bounds.height > wall_bounds.top + 3) &&
                (guy_bounds.top < wall_bounds.top + wall_bounds.height - 3));
    }

    void moveInDirection(const sf::Time &elapsed, const std::vector<sf::Sprite> &obstacles) {
        float dx = 0, dy = 0;
        float speed = 100.0f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            dy -= speed * elapsed.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            dy += speed * elapsed.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            dx -= speed * elapsed.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            dx += speed * elapsed.asSeconds();
        }
        sf::Vector2f old_pos = getPosition();
        move(dx, 0);
        for (auto &obstacle : obstacles) {
            if (getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
                setPosition(old_pos);
                break;
            }
        }

        old_pos = getPosition();
        move(0, dy);
        for (auto &obstacle : obstacles) {
            if (getGlobalBounds().intersects(obstacle.getGlobalBounds())) {
                setPosition(old_pos);
                break;
            }
        }
    }

private:
    int bound_top = 0;
    int bound_bottom = 0;
    int bound_left = 0;
    int bound_right = 0;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Labyrinth Game");
    sf::Clock clock;

    sf::Texture guy_tex, grass_tex, wall_tex;
    guy_tex.loadFromFile("/home/put/untitled3/guy.png");

    grass_tex.loadFromFile("/home/put/untitled3/grass.png");

    wall_tex.loadFromFile("/home/put/untitled3/wall.png");



    CustomSprite player;
    player.setTexture(guy_tex);
    player.setPosition(100, 100);
    player.setScale(0.06f, 0.06f);

    std::vector<sf::Sprite> walls;



    sf::Sprite wall1;
    wall1.setTexture(wall_tex);
    wall1.setScale(0.5f, 0.2f);
    wall1.setPosition(100, 200);
    walls.push_back(wall1);


    sf::Sprite wall2;
    wall2.setTexture(wall_tex);
    wall2.setScale(0.5f, 0.2f);
    wall2.setPosition(600, 300);
    walls.push_back(wall2);


    sf::Sprite wall3;
    wall3.setTexture(wall_tex);
    wall3.setScale(0.2f, 0.5f);
    wall3.setPosition(200, 500);
    walls.push_back(wall3);



    sf::Sprite grass_tile;
    grass_tile.setTexture(grass_tex);
    grass_tile.setPosition(0, 0);
    grass_tile.setScale(20.0f, 20.0f);

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.setBounds(0, window.getSize().x, 0, window.getSize().y);
        player.moveInDirection(elapsed, walls);

        window.clear();
        window.draw(grass_tile);

        window.draw(wall1);
        window.draw(wall2);
        window.draw(wall3);

        window.draw(player);

        window.display();
    }

    return 0;
}
