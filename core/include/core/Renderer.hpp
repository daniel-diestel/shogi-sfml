#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <utility>
#include <set>
#include <cstdint>
#include "Board.hpp"
#include "Config.hpp"
#include "Game.hpp"

class Renderer
{
public:
    Renderer();

    void draw(sf::RenderWindow &window, const Board &board, Coordinates selectedCoords, bool dropSelected, PieceType selectedPieceTye, Player currentPlayer, GameState currentState, Player winner);

private:
    sf::Font m_font;
    sf::Texture m_board_texture;
    std::map<std::pair<PieceType, bool>, sf::Texture> m_pieceTextures;
    sf::Texture m_menu_texture;
    sf::Texture m_game_over_texture;
    sf::Texture m_promotion_texture;
    sf::Clock m_blink_clock;

    void loadFont();
    void loadBoardTexture();
    void loadPieceTextures();
    void loadStateTextures();

    void drawStartMenuState(sf::RenderWindow &window);
    void drawPlayingState(sf::RenderWindow &window, const Board &board, Coordinates selectedCoords, bool dropSelected, PieceType selectedPieceTye, Player currentPlayer);
    void drawPromotionState(sf::RenderWindow &window);
    void drawGameOverState(sf::RenderWindow &window, Player winner);

    void drawBoard(sf::RenderWindow &window, const Board &board);
    void drawPieces(sf::RenderWindow &window, const Board &board);
    void drawHand(sf::RenderWindow &window, const Board &board);
    void drawAvailableMoves(sf::RenderWindow &window, const Board &board, Coordinates selectedCoords, bool dropSelected, PieceType selectedPieceTye, Player currentPlayer);
};