#include <string>

enum Player
{
    Sente,
    Gote,
    None
};

inline std::string playerToString(Player player)
{
    switch (player)
    {
    case Player::Sente:
        return "Sente";
    case Player::Gote:
        return "Gote";
    default:
        return "None";
    }
}

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

enum class GameState
{
    StartMenu,
    Playing,
    GameOver,
    PromotionChoice
};