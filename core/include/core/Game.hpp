#pragma once

#include "Board.hpp"
#include "MoveGenerator.hpp"

class Game {
    public:
        const Board &getBoard();

        Player getCurrentPlayer();

        void makeDrop(PieceType type);

        void handleClickInput(Coordinates selectedCoordinates, PieceType type = PieceType::Empty);

    private:
    Board m_board;
    Player m_current_player;

    bool m_make_drop = false;

    PieceType m_selected_drop_type;

    Coordinates m_selected_board_coordinates = {-1, -1};
};