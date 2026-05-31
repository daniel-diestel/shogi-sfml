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