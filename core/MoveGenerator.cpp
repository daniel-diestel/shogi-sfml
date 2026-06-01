#include "MoveGenerator.hpp"

std::vector<Move> MoveGenerator::generateMoves(const Board &board, Player player)
{
    std::vector<Move> moves;

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            Piece piece = board.getPiece(x, y);
            if (piece.type() == PieceType::Empty || piece.owner() == Player::None || piece.owner() != player)
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
                default:
                    break;
                }
            }
        }
    }

    generateDropMoves(board, player, moves);

    return moves;
}

std::vector<Move> MoveGenerator::generateLegalMoves(const Board &board, Player player)
{
    std::vector<Move> myMoves = generateMoves(board, player);
    std::vector<Move> myLegalMoves;

    Player enemy = (player == Player::Sente) ? Player::Gote : Player::Sente;

    for (Move &move : myMoves)
    {
        Board testingBoard = board;

        testingBoard.makeMove(move);

        Coordinates kingCoordiantes = testingBoard.findKing(player);

        if (!isKingAttacked(testingBoard, kingCoordiantes, enemy))
        {
            myLegalMoves.push_back(move);
        }
    }

    return myLegalMoves;
}

bool MoveGenerator::isKingAttacked(const Board &board, Coordinates kingCoordinates, Player enemy)
{
    std::vector<Move> enemyMoves = generateMoves(board, enemy);

    for (Move &move : enemyMoves)
    {
        if (move.toX() == kingCoordinates.x && move.toY() == kingCoordinates.y)
        {
            return true;
        }
    }
    return false;
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

    if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner() || targetPiece.owner() == Player::None)
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

        if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner() || targetPiece.owner() == Player::None)
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

        if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner() || targetPiece.owner() == Player::None)
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

        if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner() || targetPiece.owner() == Player::None)
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

        if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner() || targetPiece.owner() == Player::None)
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

        if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner() || targetPiece.owner() == Player::None)
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

        if (targetPiece.type() != PieceType::Empty)
        {
            break;
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

            if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner() || targetPiece.owner() == Player::None)
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

            if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner() || targetPiece.owner() == Player::None)
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

            if (targetPiece.type() != PieceType::Empty)
            {
                break;
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

            if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner() || targetPiece.owner() == Player::None)
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

            if (targetPiece.type() != PieceType::Empty || targetPiece.owner() == piece.owner() || targetPiece.owner() == Player::None)
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

            if (targetPiece.type() != PieceType::Empty)
            {
                break;
            }

            forward++;
        } while (true);

        forward = 1;
    }
}

void MoveGenerator::generateDropMoves(const Board &board, Player player, std::vector<Move> &moves)
{
    std::vector<Piece> myHand = board.getHand(player);

    if (myHand.empty())
    {
        return;
    }

    std::vector<PieceType> checkedTypes;

    for (Piece piece : myHand)
    {
        if (std::find(checkedTypes.begin(), checkedTypes.end(), piece.type()) != checkedTypes.end())
        {
            continue;
        }

        checkedTypes.push_back(piece.type());

        for (int x = 0; x < 9; x++)
        {
            bool isPawnInColumn = false;

            if (piece.type() == PieceType::Pawn)
            {

                for (int y = 0; y < 9; y++)
                {
                    Piece piece = board.getPiece(x, y);

                    if (piece.owner() == player && piece.type() == PieceType::Pawn && !piece.isPromoted())
                    {
                        isPawnInColumn = true;
                        break;
                    }
                }
            }

            if (isPawnInColumn)
            {
                continue;
            }

            for (int y = 0; y < 9; y++)
            {
                if (board.getPiece(x, y).type() != PieceType::Empty)
                {
                    continue;
                }

                if (piece.type() == PieceType::Pawn || piece.type() == PieceType::Lance)
                {
                    if ((player == Player::Sente && y == 0) || (player == Player::Gote && y == 8))
                    {
                        continue;
                    }
                }
                if (piece.type() == PieceType::Knight)
                {
                    if ((player == Player::Sente && y <= 1) || (player == Player::Gote && y >= 7))
                    {
                        continue;
                    }
                }

                moves.emplace_back(x, y, piece);
            }
        }
    }
}