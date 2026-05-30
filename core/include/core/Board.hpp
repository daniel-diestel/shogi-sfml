#pragma once

#include <array>
#include "Piece.hpp"

class Board {
    public:
        Board();

        bool isInside(int x, int y) const;

        Piece getPiece();

        void placePiece();
        void removePiece();

    private:
        // Board coordinates:
        // x = row      [0..8], left → right
        // y = column   [0..8], top  → bottom
        std::array<std::array<Piece,9>,9> m_board;

        void newBoard() const;
};