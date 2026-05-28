#include "Board.hpp"

Board::Board()
{
    for (std::array<Piece *, 9> &row : m_board)
    {
        row.fill(nullptr);
    }
}

Board::~Board()
{
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            delete m_board[y][x];
        }
    }

    for (Piece *p : m_blackHand)
        delete p;

    for (Piece *p : m_whiteHand)
        delete p;
}

Board::Board(const Board &other)
{
    for (auto &row : m_board)
        row.fill(nullptr);

    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            if (other.m_board[y][x] != nullptr)
            {
                m_board[y][x] = new Piece(*(other.m_board[y][x]));
            }
        }
    }
    for (Piece *p : other.m_blackHand)
        m_blackHand.push_back(new Piece(*p));

    for (Piece *p : other.m_whiteHand)
        m_whiteHand.push_back(new Piece(*p));
}

Board &Board::operator=(const Board &other)
{
    if (this == &other)
        return *this;

    return *this;
}

std::pair<int, int> Board::findKing(Player player) const
{
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            Piece *p = getPiece(x, y);
            if (p != nullptr && p->owner() == player && p->type() == PieceType::King)
            {
                return {x, y};
            }
        }
    }
    return {-1, -1};
}

Piece *Board::getPiece(int x, int y) const
{
    if (!isInside(x, y))
    {
        return nullptr;
    }
    return m_board[y][x];
}

void Board::placePiece(int x, int y, Piece *piece)
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
    m_board[y][x] = nullptr;
}

bool Board::isInside(int x, int y) const
{
    return x >= 0 && x < 9 && y >= 0 && y < 9;
}

const std::vector<Piece *> &Board::getHand(Player player) const
{
    return (player == Player::Black) ? m_blackHand : m_whiteHand;
}

void Board::addToHand(Player player, Piece *piece)
{
    if (player == Player::Black)
    {
        m_blackHand.push_back(piece);
    }
    else
    {
        m_whiteHand.push_back(piece);
    }
}

void Board::removeFromHand(Player player, Piece *piece)
{
    std::vector<Piece *> &hand = (player == Player::Black) ? m_blackHand : m_whiteHand;

    auto iterator = std::find(hand.begin(), hand.end(), piece);
    if (iterator != hand.end())
    {
        hand.erase(iterator);
    }
}

void Board::makeMove(const Move &move)
{
    Piece *movingPiece = move.movedPiece();

    if (move.isDrop())
    {
        removeFromHand(movingPiece->owner(), movingPiece);
        placePiece(move.toX(), move.toY(), movingPiece);
    }
    else
    {
        Piece *targetPiece = getPiece(move.toX(), move.toY());

        if (targetPiece != nullptr)
        {
            targetPiece->setOwner(movingPiece->owner());

            targetPiece->demote();

            addToHand(movingPiece->owner(), targetPiece);
        }

        removePiece(move.fromX(), move.fromY());
        placePiece(move.toX(), move.toY(), movingPiece);

        if (move.doesPromote())
        {
            movingPiece->promote();
        }
    }
}