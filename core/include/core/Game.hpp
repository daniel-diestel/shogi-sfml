#pragma once

#include <vector>
#include "Board.hpp"
#include "Move.hpp"
#include "MoveGenerator.hpp"

class Game
{

public:
    const Board &getBoard();

    Player getCurrentPlayer();

    void handleInput(int x, int y);

private:
    Board m_board;
    Player m_currentPlayer = Player::Black;

    int m_selectedX = -1;
    int m_selectedY = -1;
};