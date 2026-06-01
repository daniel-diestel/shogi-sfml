#pragma once

#include "Types.hpp"

class Piece
{
public:
    Piece(PieceType type = Empty, Player owner = None, bool promoted = false);

    PieceType type() const;
    Player owner() const;
    bool isPromoted() const;

    void promote();
    void demote();
    bool canPromote();
    void setNewOwner(Player newOwner);

    bool operator==(const Piece &other) const
    {
        return this->m_type == other.m_type;
    }

private:
    PieceType m_type;
    Player m_owner;
    bool m_promoted;

    bool isPiecePromotable();
};