#pragma once

#include "Types.hpp"

class Piece
{
public:
    Piece(PieceType type, Player owner, bool promoted = false);

    PieceType type() const;
    Player owner() const;
    bool isPromoted() const;

    void promote();
    void demote();
    bool canPromote();

private:
    PieceType m_type;
    Player m_owner;
    bool m_promoted;

    bool isPiecePromotable();
};