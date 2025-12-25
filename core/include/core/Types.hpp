#pragma once

enum class Player
{
    Black,
    White
};

enum class PieceType
{
    King,
    Gold,
    Silver,
    Knight,
    Lance,
    Pawn,
    Bishop,
    Rook
};

enum class MoveType
{
    Normal,
    Promotion,
    Drop
};
