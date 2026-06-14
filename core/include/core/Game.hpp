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

        bool handleClickInput(Coordinates selectedCoordinates);

        bool isCheckmate();

        Player getWinner();

        void executeNormalMove();
        void executePromotionMove();

    private : Board m_board;
        Player m_current_player;
        Move m_normal_move;
        Move m_promotion_move;

        bool m_make_drop;

        PieceType m_selected_drop_type;

        Coordinates m_selected_board_coordinates;
};