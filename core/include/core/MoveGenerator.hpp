#pragma once

#include <vector>
#include "Board.hpp"
#include "Move.hpp"
#include "Piece.hpp"
#include "Types.hpp"

class MoveGenerator
{
public:
    static std::vector<Move> generateMoves(const Board &board, Player player);

private:
    static void generatePawnMoves(const Board &board, int x, int y, Piece* piece, std::vector<Move> &moves);

};