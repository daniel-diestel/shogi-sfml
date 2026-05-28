#pragma once

#include <array>
#include <vector>
#include <algorithm>
#include "Piece.hpp"
#include "Move.hpp"

class Board
{
public:
    Board();
    
    ~Board();
    Board(const Board &other);

    Board &operator=(const Board &other);

    std::pair<int, int> findKing(Player player) const;

    Piece *getPiece(int x, int y) const;
    void placePiece(int x, int y, Piece *piece);
    void removePiece(int x, int y);

    bool isInside(int x, int y) const;

    const std::vector<Piece *> &getHand(Player player) const;
    void addToHand(Player player, Piece *piece);
    void removeFromHand(Player player, Piece *piece);

    void makeMove(const Move &move);

private:
    // Board coordinates:
    // x = column [0..8], left → right
    // y = row    [0..8], top  → bottom
    std::array<std::array<Piece *, 9>, 9> m_board;

    std::vector<Piece *> m_blackHand;
    std::vector<Piece *> m_whiteHand;
};