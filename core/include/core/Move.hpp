#pragma once

#include "Piece.hpp"

class Move
{
public:
    Move(int fromX, int fromY, int toX, int toY, Piece* piece, bool promotes = false);

    Move(int toX, int toY, Piece* piece);

    int fromX() const;
    int fromY() const;
    int toX() const;
    int toY() const;
    Piece* movedPiece() const;
    bool isDrop() const;
    bool doesPromote() const;

private:
    int m_fromX;
    int m_fromY;
    int m_toX;
    int m_toY;
    Piece* m_piece;
    bool m_drop;
    bool m_promote;
};