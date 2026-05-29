#include "Renderer.hpp"
#include <iostream>

Renderer::Renderer()
{
    if (m_font.openFromFile("assets/arial.ttf"))
    {
        m_fontLoaded = true;
    }
    else
    {
        std::cout << "Warnung: arial.ttf konnte nicht geladen werden! Figuren werden ohne Text gezeichnet.\n";
    }
}

void Renderer::draw(sf::RenderWindow &window, const Game &game)
{
    const Board &board = game.getBoard();

    drawBoard(window);
    drawPieces(window, board);
    drawHands(window, board);
}

void Renderer::drawBoard(sf::RenderWindow &window)
{
    sf::RectangleShape boardBg(sf::Vector2f(CELL_SIZE * 9, CELL_SIZE * 9));
    boardBg.setPosition({BOARD_OFFSET_X, BOARD_OFFSET_Y});
    boardBg.setFillColor(sf::Color(245, 222, 179)); // Wheat-Farbe
    boardBg.setOutlineThickness(2.f);
    boardBg.setOutlineColor(sf::Color::Black);
    window.draw(boardBg);

    for (int i = 0; i <= 9; i++)
    {
        sf::Vertex horizLine[] = {
            sf::Vertex(sf::Vector2f(BOARD_OFFSET_X, BOARD_OFFSET_Y + i * CELL_SIZE), sf::Color::Black),
            sf::Vertex(sf::Vector2f(BOARD_OFFSET_X + 9 * CELL_SIZE, BOARD_OFFSET_Y + i * CELL_SIZE), sf::Color::Black)};
        window.draw(horizLine, 2, sf::PrimitiveType::Lines);

        sf::Vertex vertLine[] = {
            sf::Vertex(sf::Vector2f(BOARD_OFFSET_X + i * CELL_SIZE, BOARD_OFFSET_Y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(BOARD_OFFSET_X + i * CELL_SIZE, BOARD_OFFSET_Y + 9 * CELL_SIZE), sf::Color::Black)};
        window.draw(vertLine, 2, sf::PrimitiveType::Lines);
    }
}

void Renderer::drawPieces(sf::RenderWindow &window, const Board &board)
{
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            Piece *piece = board.getPiece(x, y);
            if (piece == nullptr)
                continue;

            sf::Vector2f pos = getScreenPosition(x, y);

            sf::CircleShape pieceShape(CELL_SIZE / 2.f - 5.f);
            pieceShape.setPosition(pos + sf::Vector2f(5.f, 5.f));

            if (piece->owner() == Player::Black)
            {
                pieceShape.setFillColor(sf::Color(70, 130, 180));
            }
            else
            {
                pieceShape.setFillColor(sf::Color(178, 34, 34));
            }
            window.draw(pieceShape);

            if (m_fontLoaded)
            {
                sf::Text text(m_font);

                std::string label = " ";
                switch (piece->type())
                {
                case PieceType::King:
                    label = "K";
                    break;
                case PieceType::Pawn:
                    label = "P";
                    break;
                case PieceType::Rook:
                    label = "R";
                    break;
                case PieceType::Bishop:
                    label = "B";
                    break;
                case PieceType::Gold:
                    label = "G";
                    break;
                case PieceType::Silver:
                    label = "S";
                    break;
                case PieceType::Knight:
                    label = "N";
                    break;
                case PieceType::Lance:
                    label = "L";
                    break;
                }

                if (piece->isPromoted())
                    label = "+" + label;

                text.setString(label);
                text.setCharacterSize(24);
                text.setFillColor(sf::Color::White);

                sf::FloatRect textRect = text.getLocalBounds();
                text.setOrigin(sf::Vector2f(textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y / 2.0f));
                text.setPosition(pos + sf::Vector2f(CELL_SIZE / 2.0f, CELL_SIZE / 2.0f));

                window.draw(text);
            }
        }
    }
}

void Renderer::drawHands(sf::RenderWindow &window, const Board &board)
{
    const auto &blackHand = board.getHand(Player::Black);
    const auto &whiteHand = board.getHand(Player::White);

    if (m_fontLoaded)
    {
        sf::Text txt(m_font, "White Hand: " + std::to_string(whiteHand.size()), 20);
        txt.setPosition({10.f, 50.f});
        txt.setFillColor(sf::Color::Red);
        window.draw(txt);

        sf::Text txt2(m_font,"Black Hand: " + std::to_string(blackHand.size()), 20);
        txt2.setPosition({BOARD_OFFSET_X + 9 * CELL_SIZE + 20.f, BOARD_OFFSET_Y + 9 * CELL_SIZE - 40.f});
        txt2.setFillColor(sf::Color::Blue);
        window.draw(txt2);
    }
}

sf::Vector2f Renderer::getScreenPosition(int x, int y) const
{
    return {
        BOARD_OFFSET_X + x * CELL_SIZE,
        BOARD_OFFSET_Y + y * CELL_SIZE};
}