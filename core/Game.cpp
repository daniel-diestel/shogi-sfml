#include "Game.hpp"
#include <iostream>

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

Player Game::getCurrentPlayer() const
{
    return m_current_player;
}

Coordinates Game::getSelectedBoardCoordinates() const
{
    return m_selected_board_coordinates;
}

bool Game::getDrop() const
{
    return m_make_drop;
}

PieceType Game::getDropType() const
{
    return m_selected_drop_type;
}

void Game::makeDrop(PieceType type)
{
    m_make_drop = true;
    m_selected_drop_type = type;
}

bool Game::handleClickInput(Coordinates clickCoordinates)
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

                return false;
            }

            std::vector<Move> legalMoves = MoveGenerator::generateLegalMoves(m_board, m_current_player);
            std::vector<Move> promotionOption;

            for (auto &move : legalMoves)
            {
                if (move.fromX() == m_selected_board_coordinates.x && move.fromY() == m_selected_board_coordinates.y && move.toX() == clickCoordinates.x && move.toY() == clickCoordinates.y)
                {
                    promotionOption.push_back(move);
                }
            }

            if(promotionOption.size() == 2) 
            {
                for (const auto &move : promotionOption)
                {
                    if (move.doesPromote()) 
                    {
                        m_promotion_move = move;
                    }
                    else 
                    {
                        m_normal_move = move;
                    }
                }

                m_selected_board_coordinates = {-1, -1};

                return true;
            }
            else if (!promotionOption.empty())
            {
                m_board.makeMove(promotionOption[0]);

                m_current_player = (m_current_player == Player::Sente) ? Player::Gote : Player::Sente;
            }
            else
            {
                m_selected_board_coordinates = {-1, -1};
                
                return false;
            }

            m_selected_board_coordinates = {-1, -1};
        }
    }

    return false;
}

void Game::executeNormalMove() 
{
    m_board.makeMove(m_normal_move);

    m_current_player = (m_current_player == Player::Sente) ? Player::Gote : Player::Sente;
}

void Game::executePromotionMove()
{
    m_board.makeMove(m_promotion_move);

    m_current_player = (m_current_player == Player::Sente) ? Player::Gote : Player::Sente;
}

bool Game::isCheckmate()
{
    std::vector<Move> legalMoves = MoveGenerator::generateLegalMoves(m_board, m_current_player);

    if (legalMoves.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

Player Game::getWinner()
{
    Player winner_player = (m_current_player == Player::Sente) ? Player::Gote : Player::Sente;

    return winner_player;
}