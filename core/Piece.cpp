#include "Piece.hpp"

Piece::Piece(PieceType type, Player owner, bool promoted)
 : m_type(type), m_owner(owner), m_promoted(promoted) {}

PieceType Piece::type() const {
    return m_type;
}

Player Piece::owner() const {
    return m_owner;
}

bool Piece::isPromoted() const {
    return m_promoted;
}

bool Piece::isPiecePromotable() const {
    return m_type != PieceType::King && m_type != PieceType::Gold;
}

bool Piece::canPromote() const {
    return isPiecePromotable() && !m_promoted;
}

void Piece::promote() {
    if(canPromote()) {
        m_promoted = true;
    }
}

void Piece::demote() {
    m_promoted = false;
}