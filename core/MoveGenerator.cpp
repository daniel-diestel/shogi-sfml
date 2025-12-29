#include "MoveGenerator.hpp"
#include "Board.hpp"

std::vector<Move> MoveGenerator::generateMoves(const Board &board, Player player)
{
    std::vector<Move> moves;

    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            Piece *piece = board.getPiece(x, y);
            if (piece == nullptr)
                continue;
            if (piece->owner() != player)
                continue;

            if (piece->type() == PieceType::Pawn)
            {
                generatePawnMoves(board, x, y, piece, moves);
            }

            // Hier später andere Pieces hinzufügen
        }
    }
    return moves;
}

void MoveGenerator::generatePawnMoves(const Board &board, int x, int y, Piece* piece, std::vector<Move> &moves)
{
    int direction = (piece->owner() == Player::Black) ? -1 : 1;
    int targetY = y + direction;
    int targetX = x;

    if (!board.isInside(targetX, targetY))
        return;

    Piece *targetPiece = board.getPiece(targetX, targetY);
    if (targetPiece != nullptr && targetPiece->owner() == piece->owner())
        return;

    bool canPromote = piece->canPromote() && ((piece->owner() == Player::Black && targetY <= 2) ||
                                              (piece->owner() == Player::White && targetY >= 6));

    moves.emplace_back(x, y, targetX, targetY, piece, false);

    if (canPromote)
    {
        moves.emplace_back(x, y, targetX, targetY, piece, true);
    }
}