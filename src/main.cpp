#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Renderer.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Shogi");

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

            if (const auto *mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
            {
                float mouseX = static_cast<float>(mouseClick->position.x);
                float mouseY = static_cast<float>(mouseClick->position.y);

                int boardX = static_cast<int>((mouseX - BOARD_OFFSET_X) / TILE_SIZE);
                int boardY = static_cast<int>((mouseY - BOARD_OFFSET_Y) / TILE_SIZE);

                if (boardX >= 0 && boardX < 9 && boardY >= 0 && boardY < 9)
                {
                    Coordinates clickedCoords{boardX, boardY};

                    game.handleClickInput(clickedCoords);
                }
            }
        }
        
        window.clear(sf::Color::Black);

        renderer.draw(window, game.getBoard());

        window.display();
    }
}