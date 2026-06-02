#include "Game.hpp"

Game::Game()
{
    m_current_player = Player::Sente;
    m_selected_board_coordinates = {-1, -1};
    m_make_drop = false;
}

const Board &Game::getBoard()
{
    return m_board;
}

Player Game::getCurrentPlayer()
{
    return m_current_player;
}

void Game::makeDrop(PieceType type)
{
    m_make_drop = true;
    m_selected_drop_type = type;
}

void Game::handleClickInput(Coordinates clickCoordinates)
{
    if (m_make_drop)
    {
        std::vector<Move> legalMoves = MoveGenerator::generateLegalMoves(m_board, m_current_player);

        for (auto &move : legalMoves)
        {
            if (move.isDrop() && move.movedPiece().type() == m_selected_drop_type && move.toX() == clickCoordinates.x && move.toY() == clickCoordinates.y)
            {
                m_board.makeMove(move);

                m_current_player = (m_current_player == Player::Sente) ? Player::Gote : Player::Sente;

                break;
            }
        }

        m_make_drop = false;
    }
    else
    {
        if (m_selected_board_coordinates.x == -1 && m_selected_board_coordinates.y == -1)
        {
            Piece piece = m_board.getPiece(clickCoordinates.x, clickCoordinates.y);

            if (piece.type() != PieceType::Empty && piece.owner() == m_current_player)
            {
                m_selected_board_coordinates = {clickCoordinates.x, clickCoordinates.y};
            }
        }
        else
        {
            if (m_selected_board_coordinates.x == clickCoordinates.x && m_selected_board_coordinates.y == clickCoordinates.y)
            {
                m_selected_board_coordinates = {-1, -1};

                return;
            }

            std::vector<Move> legalMoves = MoveGenerator::generateLegalMoves(m_board, m_current_player);

            for (auto &move : legalMoves)
            {
                if (move.fromX() == m_selected_board_coordinates.x && move.fromY() == m_selected_board_coordinates.y && move.toX() == clickCoordinates.x && move.toY() == clickCoordinates.y)
                {
                    m_board.makeMove(move);

                    m_current_player = (m_current_player == Player::Sente) ? Player::Gote : Player::Sente;

                    break;
                }
            }

            m_selected_board_coordinates = {-1, -1};
        }
    }
}