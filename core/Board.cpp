#include "Board.hpp"

Board::Board()
{
    initializeBoard();
}

bool Board::isInside(int x, int y) const
{
    if ((x >= 0 && x <= 8) && (y >= 0 && y <= 8))
    {
        return true;
    }
    else
    {
        return false;
    }
}

Piece Board::getPiece(int x, int y) const
{
    return m_board[y][x];
}

void Board::placePiece(int x, int y, Piece piece)
{
    if (!isInside(x, y))
    {
        return;
    }
    m_board[y][x] = piece;
}

void Board::removePiece(int x, int y)
{
    if (!isInside(x, y))
    {
        return;
    }
    m_board[y][x] = Piece();
}

std::vector<Piece> Board::getHand(Player player) const
{
    if (player == Player::Sente)
    {
        return m_hand_sente;
    }
    else
    {
        return m_hand_gote;
    }
}

void Board::addToHand(int x, int y)
{
    if (!isInside(x, y))
    {
        return;
    }
    Piece captured = getPiece(x, y);

    if (captured.type() == PieceType::Empty || captured.owner() == Player::None)
    {
        return;
    }

    if (captured.owner() == Player::Gote)
    {
        m_hand_sente.push_back(Piece(captured.type(), Player::Sente));
    }
    else
    {
        m_hand_sente.push_back(Piece(captured.type(), Player::Gote));
    }
}

void Board::removeFromHand(Piece piece, Player player)
{
    if (player == Player::Sente)
    {
        auto iterator = std::find(m_hand_sente.begin(), m_hand_sente.end(), piece);

        if (iterator != m_hand_sente.end())
        {
            m_hand_sente.erase(iterator);
        }
    }
    else {
        auto iterator = std::find(m_hand_gote.begin(), m_hand_gote.end(), piece);

        if (iterator != m_hand_gote.end())
        {
            m_hand_gote.erase(iterator);
        }
    }
}

Coordinates Board::findKing(Player player)
{
    Coordinates kingCoordinates = {-1, -1};

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            Piece currentPiece = getPiece(x, y);

            if ((currentPiece.type() == PieceType::King || currentPiece.type() == PieceType::Jewel) && currentPiece.owner() == player)
            {
                kingCoordinates.x = x;
                kingCoordinates.y = y;

                return kingCoordinates;
            }
        }
    }

    return kingCoordinates;
}

void Board::makeMove(Move &move) {
    Piece movingPiece = move.movedPiece();

    if(move.isDrop()) {
        removeFromHand(movingPiece, movingPiece.owner());
        placePiece(move.toX(), move.toY(), movingPiece);
    }
    else {  
        addToHand(move.toX(), move.toY());

        removePiece(move.fromX(), move.fromY());

        if (move.doesPromote())
        {
            movingPiece.promote();
        }

        placePiece(move.toX(), move.toY(), movingPiece);
    }
}

    void Board::initializeBoard()
{
    m_board = {{
        {Piece(PieceType::Lance, Player::Gote), Piece(PieceType::Knight, Player::Gote), Piece(PieceType::Silver, Player::Gote), Piece(PieceType::Gold, Player::Gote), Piece(PieceType::King, Player::Gote), Piece(PieceType::Gold, Player::Gote), Piece(PieceType::Silver, Player::Gote), Piece(PieceType::Knight, Player::Gote), Piece(PieceType::Lance, Player::Gote)},
        {Piece(), Piece(PieceType::Rook, Player::Gote), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(PieceType::Bishop, Player::Gote), Piece()},
        {Piece(PieceType::Pawn, Player::Gote), Piece(PieceType::Pawn, Player::Gote), Piece(PieceType::Pawn, Player::Gote), Piece(PieceType::Pawn, Player::Gote), Piece(PieceType::Pawn, Player::Gote), Piece(PieceType::Pawn, Player::Gote), Piece(PieceType::Pawn, Player::Gote), Piece(PieceType::Pawn, Player::Gote), Piece(PieceType::Pawn, Player::Gote)},
        {Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
        {Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
        {Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(), Piece()},
        {Piece(PieceType::Pawn, Player::Sente), Piece(PieceType::Pawn, Player::Sente), Piece(PieceType::Pawn, Player::Sente), Piece(PieceType::Pawn, Player::Sente), Piece(PieceType::Pawn, Player::Sente), Piece(PieceType::Pawn, Player::Sente), Piece(PieceType::Pawn, Player::Sente), Piece(PieceType::Pawn, Player::Sente), Piece(PieceType::Pawn, Player::Sente)},
        {Piece(), Piece(PieceType::Rook, Player::Sente), Piece(), Piece(), Piece(), Piece(), Piece(), Piece(PieceType::Bishop, Player::Sente), Piece()},
        {Piece(PieceType::Lance, Player::Sente), Piece(PieceType::Knight, Player::Sente), Piece(PieceType::Silver, Player::Sente), Piece(PieceType::Gold, Player::Sente), Piece(PieceType::Jewel, Player::Sente), Piece(PieceType::Gold, Player::Sente), Piece(PieceType::Silver, Player::Sente), Piece(PieceType::Knight, Player::Sente), Piece(PieceType::Lance, Player::Sente)},
    }};
}