#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Renderer.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({1200, 950}), "Shogi");

    Renderer renderer;
    Game game;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        renderer.draw(window, game.getBoard());

        window.display();
    }
}