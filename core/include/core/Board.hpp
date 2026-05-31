#pragma once

#include <array>
#include <vector>
#include "Piece.hpp"

class Board
{
public:
    Board();

    bool isInside(int x, int y) const;

    Piece getPiece(int x, int y) const;

    void placePiece(int x, int y, Piece piece);
    void removePiece(int x, int y);

    void addToHand(int x, int y);

private:
    // Board coordinates:
    // x = row      [0..8], left → right
    // y = column   [0..8], top  → bottom
    std::array<std::array<Piece, 9>, 9> m_board;

    std::vector<Piece> m_hand_sente;
    std::vector<Piece> m_hand_gote;

    void initializeBoard();
};