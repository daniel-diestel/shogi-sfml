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
        
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            delete m_board[y][x];
            m_board[y][x] = nullptr;
        }
    }
    for (Piece *p : m_blackHand)
        delete p;
    m_blackHand.clear();

    for (Piece *p : m_whiteHand)
        delete p;
    m_whiteHand.clear();

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

    return *this;
}

void Board::setupBoard()
{
    // === WEIß (Gote) - Oben auf dem Brett ===
    
    placePiece(0, 0, new Piece(PieceType::Lance, Player::White));
    placePiece(1, 0, new Piece(PieceType::Knight, Player::White));
    placePiece(2, 0, new Piece(PieceType::Silver, Player::White));
    placePiece(3, 0, new Piece(PieceType::Gold, Player::White));
    placePiece(4, 0, new Piece(PieceType::King, Player::White));
    placePiece(5, 0, new Piece(PieceType::Gold, Player::White));
    placePiece(6, 0, new Piece(PieceType::Silver, Player::White));
    placePiece(7, 0, new Piece(PieceType::Knight, Player::White));
    placePiece(8, 0, new Piece(PieceType::Lance, Player::White));

    placePiece(1, 1, new Piece(PieceType::Rook, Player::White));
    placePiece(7, 1, new Piece(PieceType::Bishop, Player::White));

    for (int x = 0; x < 9; x++)
    {
        placePiece(x, 2, new Piece(PieceType::Pawn, Player::White));
    }

    // === SCHWARZ (Sente) - Unten auf dem Brett ===

    for (int x = 0; x < 9; x++)
    {
        placePiece(x, 6, new Piece(PieceType::Pawn, Player::Black));
    }

    placePiece(1, 7, new Piece(PieceType::Bishop, Player::Black));
    placePiece(7, 7, new Piece(PieceType::Rook, Player::Black));

    placePiece(0, 8, new Piece(PieceType::Lance, Player::Black));
    placePiece(1, 8, new Piece(PieceType::Knight, Player::Black));
    placePiece(2, 8, new Piece(PieceType::Silver, Player::Black));
    placePiece(3, 8, new Piece(PieceType::Gold, Player::Black));
    placePiece(4, 8, new Piece(PieceType::King, Player::Black));
    placePiece(5, 8, new Piece(PieceType::Gold, Player::Black));
    placePiece(6, 8, new Piece(PieceType::Silver, Player::Black));
    placePiece(7, 8, new Piece(PieceType::Knight, Player::Black));
    placePiece(8, 8, new Piece(PieceType::Lance, Player::Black));
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
    Piece *movingPiece = nullptr;

    if (move.isDrop())
    {
        Player owner = move.movedPiece()->owner();
        PieceType type = move.movedPiece()->type();

        const std::vector<Piece *> &hand = getHand(owner);
        for (Piece *p : hand)
        {
            if (p->type() == type)
            {
                movingPiece = p;
                break;
            }
        }

        if (movingPiece != nullptr)
        {
            removeFromHand(owner, movingPiece);
            placePiece(move.toX(), move.toY(), movingPiece);
        }
    }
    else
    {
        movingPiece = getPiece(move.fromX(), move.fromY());

        if (movingPiece != nullptr)
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
}