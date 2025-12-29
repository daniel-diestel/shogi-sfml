#include "Board.hpp"

Board::Board() {
    for (std::array<Piece*, 9>& row : m_board) {
        row.fill(nullptr);
    }
}

Piece* Board::getPiece(int x, int y) const {
    if(!isInside(x, y)) {
        return nullptr;
    }
    return m_board[y][x];
}

void Board::placePiece(int x, int y, Piece* piece) {
    if (!isInside(x, y)) {
        return;
    }
    m_board[y][x] = piece;
}

void Board::removePiece(int x, int y) {
    if (!isInside(x, y)) {
        return;
    }
    m_board[y][x] = nullptr;
}

bool Board::isInside(int x, int y) const
{
    return x >= 0 && x < 9 && y >= 0 && y < 9;
}