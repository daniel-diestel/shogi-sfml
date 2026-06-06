#pragma once

#include "Board.hpp"
#include "MoveGenerator.hpp"

class Game {
    public:
        Game();

        const Board &getBoard();

        Player getCurrentPlayer() const;
        Coordinates getSelectedBoardCoordinates() const;
        bool getDrop() const;
        PieceType getDropType() const;

        void makeDrop(PieceType type);

        void handleClickInput(Coordinates selectedCoordinates);

    private:
    Board m_board;
    Player m_current_player;

    bool m_make_drop;

    PieceType m_selected_drop_type;

    Coordinates m_selected_board_coordinates;
};