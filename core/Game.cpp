#include "Game.hpp"

Game::Game()
{
    m_board.setupBoard();
}

const Board &Game::getBoard() const
{
    return m_board;
}

Player Game::getCurrentPlayer() const
{
    return m_currentPlayer;
}

void Game::handleInput(int x, int y)
{
    if (m_selectedX == -1)
    {
        Piece *piece = m_board.getPiece(x, y);
        if (piece != nullptr && piece->owner() == m_currentPlayer)
        {
            m_selectedX = x;
            m_selectedY = y;
        }
    }
    else
    {
        if (x == m_selectedX && y == m_selectedY)
        {
            m_selectedX = -1;
            m_selectedY = -1;

            return;
        }

        std::vector<Move> legalMoves = MoveGenerator::getLegalMoves(m_board, m_currentPlayer);

        bool moveExecuted = false;
        for (const auto &move : legalMoves)
        {
            if (move.fromX() == m_selectedX && move.fromY() == m_selectedY && move.toX() == x && move.toY() == y)
            {
                m_board.makeMove(move);

                m_currentPlayer = (m_currentPlayer == Player::Black) ? Player::White : Player::Black;

                moveExecuted = true;
                break;
            }
        }

        m_selectedX = -1;
        m_selectedY = -1;
    }
}