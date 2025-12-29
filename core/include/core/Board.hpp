#pragma once

#include <array>
#include "Piece.hpp"

class Board {
public:
    Board();

    Piece* getPiece(int x, int y) const;
    void placePiece(int x, int y, Piece* piece);
    void removePiece(int x, int y);

    bool isInside(int x, int y) const;

private:
    // Board coordinates:
    // x = column [0..8], left → right
    // y = row    [0..8], top  → bottom
    std::array<std::array<Piece*, 9>, 9> m_board;
};