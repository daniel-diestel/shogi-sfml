#include "MoveGenerator.hpp"

struct Offset
{
    int dx;
    int dy;
};

std::vector<Move> MoveGenerator::generateMoves(const Board &board, Player player)
{
    std::vector<Move> moves;

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            Piece piece = board.getPiece(x, y);
            if (piece.type() == PieceType::Empty || piece.owner() == Player::None)
            {
                continue;
            }

            if (piece.isPromoted())
            {
                switch (piece.type())
                {
                case PieceType::Pawn:
                case PieceType::Silver:
                case PieceType::Knight:
                case PieceType::Lance:
                    generateGoldMoves(board, x, y, piece, moves);
                    break;
                case PieceType::Rook:
                    generateRookMoves(board, x, y, piece, moves);
                    break;
                case PieceType::Bishop:
                    generateBishopMoves(board, x, y, piece, moves);
                    break;
                default:
                    break;
                }
            }
            else
            {
                switch (piece.type())
                {
                case PieceType::Pawn:
                    generatePawnMoves(board, x, y, piece, moves);
                    break;
                case PieceType::King:
                case PieceType::Jewel:
                    generateKingMoves(board, x, y, piece, moves);
                    break;
                case PieceType::Gold:
                    generateGoldMoves(board, x, y, piece, moves);
                    break;
                case PieceType::Silver:
                    generateSilverMoves(board, x, y, piece, moves);
                    break;
                case PieceType::Knight:
                    generateKnightMoves(board, x, y, piece, moves);
                    break;
                case PieceType::Lance:
                    generateLanceMoves(board, x, y, piece, moves);
                    break;
                case PieceType::Rook:
                    generateRookMoves(board, x, y, piece, moves);
                    break;
                case PieceType::Bishop:
                    generateBishopMoves(board, x, y, piece, moves);
                    break;
                }
            }
        }
    }

    return moves;
}

void MoveGenerator::generatePawnMoves(const Board &board, int x, int y, Piece piece, std::vector<Move> &moves)
{
    int direction = (piece.owner() == Player::Sente) ? -1 : 1;
    int targetY = y + direction;
    int targetX = x;

    if (!board.isInside(targetX, targetY))
    {
        return;
    }

    Piece targetPiece = board.getPiece(targetX, targetY);

    if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner())
    {
        return;
    }

    bool movesToPromoteZone = ((piece.owner() == Player::Sente && targetY <= 2) || (piece.owner() == Player::Gote && targetY >= 6));
    bool canPromote = piece.canPromote() && movesToPromoteZone;

    if ((piece.owner() == Player::Gote && targetY != 0) || (piece.owner() == Player::Sente && targetY != 8))
    {
        moves.emplace_back(x, y, targetX, targetY, piece, false);
    }

    if (canPromote)
    {
        moves.emplace_back(x, y, targetX, targetY, piece, true);
    }
}

void MoveGenerator::generateKingMoves(const Board &board, int x, int y, Piece piece, std::vector<Move> &moves)
{
    static const std::array<Offset, 8> possibleMoves = {{{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}}};

    for (const Offset &move : possibleMoves)
    {
        int targetX = x + move.dx;
        int targetY = y + move.dy;

        if (!board.isInside(targetX, targetY))
        {
            continue;
        }

        Piece targetPiece = board.getPiece(targetX, targetY);

        if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner())
        {
            continue;
        }

        moves.emplace_back(x, y, targetX, targetY, piece, false);
    }
}

void MoveGenerator::generateGoldMoves(const Board &board, int x, int y, Piece piece, std::vector<Move> &moves)
{
    int direction = (piece.owner() == Player::Sente) ? 1 : -1;

    // Definiert für Schwarz
    static const std::array<Offset, 6> possibleMoves = {{{0, -1}, {-1, -1}, {1, -1}, {-1, 0}, {1, 0}, {0, 1}}};

    for (const Offset &move : possibleMoves)
    {
        int targetX = x + (direction * move.dx);
        int targetY = y + (direction * move.dy);

        if (!board.isInside(targetX, targetY))
        {
            continue;
        }

        Piece targetPiece = board.getPiece(targetX, targetY);

        if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner())
        {
            continue;
        }

        moves.emplace_back(x, y, targetX, targetY, piece, false);
    }
}

void MoveGenerator::generateSilverMoves(const Board &board, int x, int y, Piece piece, std::vector<Move> &moves)
{
    int direction = (piece.owner() == Player::Sente) ? 1 : -1;

    // Definiert für Schwarz
    static const std::array<Offset, 5> possibleMoves = {{{0, -1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}}};

    for (const Offset &move : possibleMoves)
    {
        int targetX = x + (direction * move.dx);
        int targetY = y + (direction * move.dy);

        if (!board.isInside(targetX, targetY))
        {
            continue;
        }

        Piece targetPiece = board.getPiece(targetX, targetY);

        if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner())
        {
            continue;
        }

        bool movesToPromoteZone = ((piece.owner() == Player::Sente && targetY <= 2) || (piece.owner() == Player::Gote && targetY >= 6));
        bool movesFromPromoteZone = ((piece.owner() == Player::Sente && y <= 2) || (piece.owner() == Player::Gote && y >= 6));
        bool canPromote = piece.canPromote() && movesToPromoteZone || movesFromPromoteZone;

        moves.emplace_back(x, y, targetX, targetY, piece, false);

        if (canPromote)
        {
            moves.emplace_back(x, y, targetX, targetY, piece, true);
        }
    }
}

void MoveGenerator::generateKnightMoves(const Board &board, int x, int y, Piece piece, std::vector<Move> &moves)
{
    int direction = (piece.owner() == Player::Sente) ? 1 : -1;

    // Definiert für Schwarz
    static const std::array<Offset, 2> possibleMoves = {{{-1, -2}, {1, -2}}};

    for (const Offset &move : possibleMoves)
    {
        int targetX = x + (direction * move.dx);
        int targetY = y + (direction * move.dy);

        if (!board.isInside(targetX, targetY))
        {
            continue;
        }

        Piece targetPiece = board.getPiece(targetX, targetY);

        if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner())
        {
            continue;
        }

        bool movesToPromoteZone = ((piece.owner() == Player::Sente && targetY <= 2) || (piece.owner() == Player::Gote && targetY >= 6));
        bool canPromote = piece.canPromote() && movesToPromoteZone;

        if (!((piece.owner() == Player::Sente && targetY <= 1) || (piece.owner() == Player::Gote && targetY >= 7)))
        {
            moves.emplace_back(x, y, targetX, targetY, piece, false);
        }

        if (canPromote)
        {
            moves.emplace_back(x, y, targetX, targetY, piece, true);
        }
    }
}

void MoveGenerator::generateLanceMoves(const Board &board, int x, int y, Piece piece, std::vector<Move> &moves)
{
    int direction = (piece.owner() == Player::Sente) ? -1 : 1;
    int forward = 1;

    do
    {
        int targetY = y + (forward * direction);
        int targetX = x;

        if (!board.isInside(targetX, targetY))
        {
            break;
        }

        Piece targetPiece = board.getPiece(targetX, targetY);

        if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner())
        {
            break;
        }

        bool movesToPromoteZone = ((piece.owner() == Player::Sente && targetY <= 2) || (piece.owner() == Player::Gote && targetY >= 6));
        bool canPromote = piece.canPromote() && movesToPromoteZone;

        if ((piece.owner() == Player::Sente && targetY != 0) || (piece.owner() == Player::Gote && targetY != 8))
        {
            moves.emplace_back(x, y, targetX, targetY, piece, false);
        }

        if (canPromote)
        {
            moves.emplace_back(x, y, targetX, targetY, piece, true);
        }

        forward++;
    } while (true);
}

void MoveGenerator::generateRookMoves(const Board &board, int x, int y, Piece piece, std::vector<Move> &moves)
{
    int forward = 1;

    static const std::array<Offset, 4> possibleMoves = {{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}};
    static const std::array<Offset, 4> possibleExtraMovesIfPromoted = {{{-1, -1}, {1, -1}, {-1, 1}, {1, 1}}};

    if (piece.isPromoted())
    {
        for (const Offset &move : possibleExtraMovesIfPromoted)
        {
            int targetX = x + move.dx;
            int targetY = y + move.dy;

            if (!board.isInside(targetX, targetY))
            {
                continue;
            }

            Piece targetPiece = board.getPiece(targetX, targetY);

            if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner())
            {
                continue;
            }

            moves.emplace_back(x, y, targetX, targetY, piece, false);
        }
    }

    for (const Offset &move : possibleMoves)
    {
        do
        {
            int targetX = x + (forward * move.dx);
            int targetY = y + (forward * move.dy);

            if (!board.isInside(targetX, targetY))
            {
                break;
            }
            Piece targetPiece = board.getPiece(targetX, targetY);

            if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner())
            {
                break;
            }

            bool movesToPromoteZone = ((piece.owner() == Player::Sente && targetY <= 2) || (piece.owner() == Player::Gote && targetY >= 6));
            bool movesFromPromoteZone = ((piece.owner() == Player::Sente && y <= 2) || (piece.owner() == Player::Gote && y >= 6));
            bool canPromote = piece.canPromote() && (movesToPromoteZone || movesFromPromoteZone);

            moves.emplace_back(x, y, targetX, targetY, piece, false);

            if (canPromote)
            {
                moves.emplace_back(x, y, targetX, targetY, piece, true);
            }

            forward++;
        } while (true);

        forward = 1;
    }
}

void MoveGenerator::generateBishopMoves(const Board &board, int x, int y, Piece piece, std::vector<Move> &moves)
{
    int forward = 1;

    static const std::array<Offset, 4> possibleMoves = {{{-1, -1}, {1, -1}, {-1, 1}, {1, 1}}};
    static const std::array<Offset, 4> possibleExtraMovesIfPromoted = {{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}};

    if (piece.isPromoted())
    {
        for (const Offset &move : possibleExtraMovesIfPromoted)
        {
            int targetX = x + move.dx;
            int targetY = y + move.dy;

            if (!board.isInside(targetX, targetY))
                continue;

            Piece targetPiece = board.getPiece(targetX, targetY);

            if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner())
            {
                continue;
            }

            moves.emplace_back(x, y, targetX, targetY, piece, false);
        }
    }

    for (const Offset &move : possibleMoves)
    {
        do
        {
            int targetX = x + (forward * move.dx);
            int targetY = y + (forward * move.dy);

            if (!board.isInside(targetX, targetY))
            {
                break;
            }

            Piece targetPiece = board.getPiece(targetX, targetY);

            if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner())
            {
                break;
            }

            bool movesToPromoteZone = ((piece.owner() == Player::Sente && targetY <= 2) || (piece.owner() == Player::Gote && targetY >= 6));
            bool movesFromPromoteZone = ((piece.owner() == Player::Sente && y <= 2) || (piece.owner() == Player::Gote && y >= 6));
            bool canPromote = piece.canPromote() && (movesToPromoteZone || movesFromPromoteZone);

            moves.emplace_back(x, y, targetX, targetY, piece, false);

            if (canPromote)
            {
                moves.emplace_back(x, y, targetX, targetY, piece, true);
            }

            forward++;
        } while (true);

        forward = 1;
    }
}