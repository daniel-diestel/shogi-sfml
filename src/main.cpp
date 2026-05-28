#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 800}), "Shogi");
    Game game;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto *mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
            {
                int x = mouseClick->position.x / 80;
                int y = mouseClick->position.y / 80;
                if (x >= 0 && x < 9 && y >= 0 && y < 9)
                {
                    game.handleInput(x, y);
                }
            }
            window.clear(sf::Color(240, 217, 181));

            for (int y = 0; y < 9; y++)
            {
                for (int x = 0; x < 9; x++)
                {
                    Piece *p = game.getBoard().getPiece(x, y);
                }
            }

            window.display();
        }
    }
}