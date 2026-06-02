#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <utility>
#include "Board.hpp"
#include "Config.hpp"

class Renderer
{
public:
    Renderer();

    void draw(sf::RenderWindow &window, const Board &board);

private:
    sf::Font m_font;
    sf::Texture m_board_texture;
    std::map<std::pair<PieceType, bool>, sf::Texture> m_pieceTextures;

    void loadFont();
    void loadBoardTexture();
    void loadPieceTextures();

    void drawBoard(sf::RenderWindow &window, const Board &board);
    void drawPieces(sf::RenderWindow &window, const Board &board);
    void drawHand(sf::RenderWindow &window, const Board &board);
};