#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"

class Renderer
{
public:
    Renderer();

    void draw(sf::RenderWindow &window, const Game& game);

private:
    const float CELL_SIZE = 70.f;
    const float BOARD_OFFSET_X = 150.f;
    const float BOARD_OFFSET_Y = 50.f;

    void drawBoard(sf::RenderWindow &window);
    void drawPieces(sf::RenderWindow &window, const Board &board);
    void drawHands(sf::RenderWindow &window, const Board &board);

    sf::Vector2f getScreenPosition(int x, int y) const;

    sf::Font m_font;
    bool m_fontLoaded = false;
};