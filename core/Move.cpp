#include "Move.hpp"

// Move
Move::Move(int fromX, int fromY, int toX, int toY, Piece *piece, bool promotes)
    : m_fromX(fromX), m_fromY(fromY), m_toX(toX), m_toY(toY),
      m_piece(piece), m_drop(false), m_promote(promotes) {}

// Drop
Move::Move(int toX, int toY, Piece *piece)
    : m_fromX(-1), m_fromY(-1), m_toX(toX), m_toY(toY),
      m_piece(piece), m_drop(true), m_promote(false) {}

int Move::fromX() const { 
    return m_fromX; 
}

int Move::fromY() const { 
    return m_fromY; 
}

int Move::toX() const { 
    return m_toX; 
}

int Move::toY() const { 
    return m_toY; 
}

Piece* Move::movedPiece() const { 
    return m_piece; 
}

bool Move::isDrop() const { 
    return m_drop; 
}

bool Move::doesPromote() const { 
    return m_promote; 
}
