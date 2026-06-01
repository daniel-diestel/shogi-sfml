#include "Renderer.hpp"

Renderer::Renderer () {

}

void Renderer::draw(sf::RenderWindow &window, const Board &board)
{
    drawBoard(window, board);
}

void Renderer::drawBoard(sf::RenderWindow &window, const Board &board)
{
    sf::RectangleShape boardUi(sf::Vector2f(812.f, 884.f));
    boardUi.setFillColor(sf::Color(240, 210, 160));
    window.draw(boardUi);

    sf::RectangleShape boardBorder(sf::Vector2f(792.f, 864.f));
    boardBorder.setFillColor(sf::Color::Transparent);
    boardBorder.setOutlineColor(sf::Color::Black);
    boardBorder.setOutlineThickness(2.f);
    boardBorder.setPosition({10.f, 10.f});
    window.draw(boardBorder);

    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            sf::RectangleShape square(sf::Vector2f(88.f, 96.f));
            square.setFillColor(sf::Color::Transparent);
            square.setOutlineColor(sf::Color::Black);
            square.setOutlineThickness(1.f);

            square.setPosition({(10.f + 88.f * y), (10.f + 96.f * x)});
            
            window.draw(square);
        }
    }
}