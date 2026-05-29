#pragma once

#include <vector>
#include "Board.hpp"
#include "Move.hpp"
#include "MoveGenerator.hpp"

class Game
{

public:
    Game();
    const Board &getBoard() const;

    Player getCurrentPlayer() const;

    void handleInput(int x, int y);

private:
    Board m_board;
    Player m_currentPlayer = Player::Black;

    int m_selectedX = -1;
    int m_selectedY = -1;
};