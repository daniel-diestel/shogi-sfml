#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Renderer.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({950, 700}), "Shogi Engine");

    Game game;
    Renderer renderer;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto *mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
            {
                float clickX = mouseClick->position.x - 150.f;
                float clickY = mouseClick->position.y - 50.f;

                if (clickX >= 0 && clickY >= 0)
                {
                    int cellX = static_cast<int>(clickX / 70.f);
                    int cellY = static_cast<int>(clickY / 70.f);

                    if (cellX >= 0 && cellX < 9 && cellY >= 0 && cellY < 9)
                    {
                        game.handleInput(cellX, cellY);
                    }
                }
            }
        }

        window.clear(sf::Color(50, 50, 50));

        renderer.draw(window, game);

        window.display();
    }
}