enum Player
{
    Sente, // First
    Gote,   // Second
    None
};

enum PieceType
{
    King,
    Jewel,
    Rook,
    Bishop,
    Gold,
    Silver,
    Knight,
    Lance,
    Pawn,
    Empty
};

struct Offset
{
    int dx;
    int dy;
};

struct Coordinates
{
    int x;
    int y;
};