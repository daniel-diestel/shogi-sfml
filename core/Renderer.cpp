#include "Renderer.hpp"

Renderer::Renderer()
{
    loadFont();
    loadBoardTexture();
    loadPieceTextures();
    loadStateTextures();
}

void Renderer::loadFont()
{
    if (!m_font.openFromFile("assets/font/PixeloidSans.ttf"))
    {
        std::cerr << "Fehler: 'assets/font/PixeloidSans.ttf' konnte nicht geladen werden!" << std::endl;
    }
}

void Renderer::loadBoardTexture()
{
    if (!m_board_texture.loadFromFile("assets/board/Shogi_Board64.png"))
    {
        std::cerr << "Fehler: 'assets/board/board.png' konnte nicht geladen werden!" << std::endl;
    }
}

void Renderer::loadPieceTextures()
{
    std::vector<std::pair<std::pair<PieceType, bool>, std::string>> pieceMapping = {
        {{PieceType::Pawn, false}, "assets/pieces/HoHei(Fu)64.png"},
        {{PieceType::Pawn, true}, "assets/pieces/ToKin64.png"},

        {{PieceType::Lance, false}, "assets/pieces/KyouSha64.png"},
        {{PieceType::Lance, true}, "assets/pieces/NariKyou64.png"},

        {{PieceType::Knight, false}, "assets/pieces/KeiMa64.png"},
        {{PieceType::Knight, true}, "assets/pieces/NariKei64.png"},

        {{PieceType::Silver, false}, "assets/pieces/GinShou64.png"},
        {{PieceType::Silver, true}, "assets/pieces/NariGin64.png"},

        {{PieceType::Gold, false}, "assets/pieces/KinShou64.png"},

        {{PieceType::Bishop, false}, "assets/pieces/KakuGyou64.png"},
        {{PieceType::Bishop, true}, "assets/pieces/RyuuMa64.png"},

        {{PieceType::Rook, false}, "assets/pieces/HiSha64.png"},
        {{PieceType::Rook, true}, "assets/pieces/RyuOu64.png"},

        {{PieceType::King, false}, "assets/pieces/OuShou64.png"},
        {{PieceType::Jewel, false}, "assets/pieces/GyokuShou64.png"}};

    for (const auto &piece : pieceMapping)
    {
        const auto &key = piece.first;
        const std::string &path = piece.second;

        if (!m_pieceTextures[key].loadFromFile(path))
        {
            std::cerr << "[Renderer] Fehler: Konnte Textur aus SVG-Bitmap nicht erstellen für: " << path << std::endl;
        }
    }
}

void Renderer::loadStateTextures() 
{
    if (!m_menu_texture.loadFromFile("assets/states/Shogi_Menu.png"))
    {
        std::cerr << "Fehler: 'assets/states/Shogi_Menu.png' konnte nicht geladen werden!" << std::endl;
    }

    if (!m_game_over_texture.loadFromFile("assets/states/Shogi_Game_Over.png"))
    {
        std::cerr << "Fehler: 'assets/states/Shogi_Game_Over.png' konnte nicht geladen werden!" << std::endl;
    }

    if (!m_promotion_texture.loadFromFile("assets/states/Shogi_Promotion.png"))
    {
        std::cerr << "Fehler: 'assets/states/Shogi_Promotion.png' konnte nicht geladen werden!" << std::endl;
    }
}

void Renderer::draw(sf::RenderWindow &window, const Board &board, Coordinates selectedCoords, bool dropSelected, PieceType selectedPieceTye, Player currentPlayer, GameState currentState, Player winner)
{
    switch (currentState)
    {
    case GameState::StartMenu:
        drawStartMenuState(window);
        break;

    case GameState::Playing:
        drawPlayingState(window, board, selectedCoords, dropSelected, selectedPieceTye, currentPlayer);
        break;
    
    case GameState::PromotionChoice:
        drawPlayingState(window, board, selectedCoords, dropSelected, selectedPieceTye, currentPlayer);
        drawPromotionState(window); 
        break;

    case GameState::GameOver:
        drawPlayingState(window, board, selectedCoords, dropSelected, selectedPieceTye, currentPlayer);
        drawGameOverState(window, winner);
        break;
    }
}

void Renderer::drawBoard(sf::RenderWindow &window, const Board &board)
{
    sf::Sprite boardSprite(m_board_texture);
    boardSprite.setPosition({BOARD_POS_X, 0.f});

    window.draw(boardSprite);
}

void Renderer::drawPieces(sf::RenderWindow &window, const Board &board)
{
    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            Piece piece = board.getPiece(x, y);

            if (piece.type() == PieceType::Empty)
            {
                continue;
            }

            auto key = std::make_pair(piece.type(), piece.isPromoted());
            sf::Sprite sprite(m_pieceTextures[key]);

            float posX = x * TILE_SIZE + BOARD_OFFSET_X;
            float posY = y * TILE_SIZE + BOARD_OFFSET_Y;

            if (piece.owner() == Player::Gote)
            {
                float halfSize = PIECE_SIZE / 2.f;
                sprite.setOrigin({halfSize, halfSize});

                sprite.setRotation(sf::degrees(180.f));

                sprite.setPosition({posX + halfSize, posY + halfSize});
            }
            else
            {
                sprite.setOrigin({0.f, 0.f});
                sprite.setPosition({posX, posY});
            }

            window.draw(sprite);
        }
    }
}

void Renderer::drawHand(sf::RenderWindow &window, const Board &board)
{
    sf::CircleShape countCircle;
    countCircle.setRadius(14.f);
    countCircle.setOrigin({14.f, 14.f});
    countCircle.setFillColor(sf::Color(230, 185, 95, 245));
    countCircle.setOutlineThickness(1.f);
    countCircle.setOutlineColor(sf::Color::Black);

    const std::vector<Piece> &handSente = board.getHand(Player::Sente);
    const std::vector<Piece> &handGote = board.getHand(Player::Gote);

    std::map<PieceType, int>
        senteCounts;

    for (const auto &piece : handSente)
    {
        senteCounts[piece.type()]++;
    }

    const float senteStartX = 805.f;
    const float senteStartY = 624.f;
    int indexSente = 0;

    for (const auto &[type, count] : senteCounts)
    {
        auto key = std::make_pair(type, false);
        sf::Sprite sprite(m_pieceTextures[key]);

        float posX = senteStartX;
        float posY = senteStartY - (indexSente * TILE_SIZE);

        sprite.setOrigin({0.f, 0.f});
        sprite.setPosition({posX, posY});

        window.draw(sprite);

        if (count > 1)
        {
            sf::Text senteText(m_font);

            senteText.setCharacterSize(16);
            senteText.setFillColor(sf::Color::Black);

            senteText.setString(std::to_string(count) + "x");
            senteText.setPosition({posX + 44.f, posY + 44.f});

            countCircle.setPosition({posX + 54.f, posY + 54.f});

            window.draw(countCircle);
            window.draw(senteText);
        }

        indexSente++;
    }

    std::map<PieceType, int> goteCounts;

    for (const auto &piece : handGote)
    {
        goteCounts[piece.type()]++;
    }

    const float goteStartX = 15.f;
    const float goteStartY = 8.f;
    int indexGote = 0;

    for (const auto &[type, count] : goteCounts)
    {
        auto key = std::make_pair(type, false);
        sf::Sprite sprite(m_pieceTextures[key]);

        float posX = goteStartX;
        float posY = goteStartY - (indexGote * (TILE_SIZE * -1));

        float halfSize = PIECE_SIZE / 2.f;
        sprite.setOrigin({halfSize, halfSize});

        sprite.setRotation(sf::degrees(180.f));

        sprite.setPosition({posX + halfSize, posY + halfSize});

        window.draw(sprite);

        if (count > 1)
        {
            sf::Text goteText(m_font);

            goteText.setCharacterSize(16);
            goteText.setFillColor(sf::Color::Black);

            goteText.setString(std::to_string(count) + "x");

            sf::FloatRect textBounds = goteText.getLocalBounds();
            goteText.setOrigin({textBounds.size.x / 2.f, textBounds.size.y / 2.f});

            goteText.setRotation(sf::degrees(180.f));

            goteText.setPosition({posX + 10.f, posY + 15.f});

            countCircle.setPosition({posX + 10.f, posY + 10.f});

            window.draw(countCircle);

            window.draw(goteText);
        }

        indexGote++;
    }
}

void Renderer::drawAvailableMoves(sf::RenderWindow &window, const Board &board, Coordinates selectedCoords, bool dropSelected, PieceType selectedPieceType, Player currentPlayer)
{
    if (selectedCoords.x == -1 && selectedCoords.y == -1 && !dropSelected)
    {
        return;
    }

    std::vector<Move> legalMoves = MoveGenerator::generateLegalMoves(board, currentPlayer);

    sf::RectangleShape moveIndicator;
    moveIndicator.setSize({72, 72});
    moveIndicator.setFillColor(sf::Color(0, 0, 0, 50));

    std::set<std::pair<int, int>> drawnFields;

    if (!dropSelected)
    {
        for (const auto &move : legalMoves)
        {
            if (move.fromX() == selectedCoords.x && move.fromY() == selectedCoords.y)
            {
                std::pair<int, int> targetPos = {move.toX(), move.toY()};

                if (drawnFields.find(targetPos) != drawnFields.end())
                {
                    continue;
                }

                drawnFields.insert(targetPos);

                float posX = move.toX() * TILE_SIZE + BOARD_OFFSET_X;
                float posY = move.toY() * TILE_SIZE + BOARD_OFFSET_Y;

                moveIndicator.setPosition({posX - 4, posY - 4});

                window.draw(moveIndicator);
            }
        }
    }
    else
    {
        for (const auto &move : legalMoves)
        {
            if (move.isDrop() && move.movedPiece().type() == selectedPieceType)
            {
                std::pair<int, int> targetPos = {move.toX(), move.toY()};

                if (drawnFields.find(targetPos) != drawnFields.end())
                {
                    continue;
                }

                drawnFields.insert(targetPos);

                float posX = move.toX() * TILE_SIZE + BOARD_OFFSET_X;
                float posY = move.toY() * TILE_SIZE + BOARD_OFFSET_Y;

                moveIndicator.setPosition({posX - 4, posY - 4});

                window.draw(moveIndicator);
            }
        }
    }
}

void Renderer::drawStartMenuState(sf::RenderWindow &window)
{
    sf::Sprite menuSprite(m_menu_texture);
    menuSprite.setPosition({0.f, 0.f});

    window.draw(menuSprite);

    sf::Text blinkText(m_font);
    blinkText.setString("PRESS 'ENTER' TO START A NEW GAME");
    blinkText.setCharacterSize(35);
    blinkText.setFillColor(sf::Color::White);

    sf::FloatRect textBoundBlink = blinkText.getLocalBounds();

    blinkText.setOrigin({textBoundBlink.position.x + textBoundBlink.size.x / 2.0f, textBoundBlink.position.y + textBoundBlink.size.y / 2.0f});

    blinkText.setPosition({WINDOW_WIDTH / 2, 600});

    float elapsedSeconds = m_blink_clock.getElapsedTime().asSeconds();

    float sineWave = std::sin(elapsedSeconds * 5.0f);

    std::uint8_t alpha = static_cast<std::uint8_t>(100.0f + (sineWave + 1.0f) * 77.5f);

    blinkText.setFillColor(sf::Color(255, 255, 255, alpha));

    window.draw(blinkText);
}

void Renderer::drawPlayingState(sf::RenderWindow &window, const Board &board, Coordinates selectedCoords, bool dropSelected, PieceType selectedPieceTye, Player currentPlayer)
{
    drawBoard(window, board);
    drawPieces(window, board);
    drawHand(window, board);
    drawAvailableMoves(window, board, selectedCoords, dropSelected, selectedPieceTye, currentPlayer);
}

void Renderer::drawPromotionState(sf::RenderWindow &window) 
{
    sf::Sprite promotionSprite(m_promotion_texture);
    promotionSprite.setPosition({0.f, 0.f});

    window.draw(promotionSprite);
}

void Renderer::drawGameOverState(sf::RenderWindow &window, Player winner)
{
    sf::RectangleShape overlay;
    overlay.setSize({WINDOW_WIDTH, WINDOW_HEIGHT});
    overlay.setFillColor(sf::Color(0, 0, 0, 170));
    overlay.setPosition({0.f, 0.f});

    window.draw(overlay);

    sf::Sprite gameOverSprite(m_game_over_texture);
    gameOverSprite.setPosition({0.f, 0.f});

    window.draw(gameOverSprite);

    sf::Text winnerText(m_font);
    winnerText.setString(playerToString(winner) + " won!");
    winnerText.setCharacterSize(35);
    winnerText.setFillColor(sf::Color::White);

    sf::FloatRect textBoundWinner = winnerText.getLocalBounds();

    winnerText.setOrigin({textBoundWinner.position.x + textBoundWinner.size.x / 2.0f, textBoundWinner.position.y + textBoundWinner.size.y / 2.0f});

    winnerText.setPosition({WINDOW_WIDTH/2, 400});

    window.draw(winnerText);

    sf::Text blinkText(m_font);
    blinkText.setString("PRESS 'ENTER' TO START A NEW GAME");
    blinkText.setCharacterSize(35);
    blinkText.setFillColor(sf::Color::White);

    sf::FloatRect textBoundBlink = blinkText.getLocalBounds();

    blinkText.setOrigin({textBoundBlink.position.x + textBoundBlink.size.x / 2.0f, textBoundBlink.position.y + textBoundBlink.size.y / 2.0f});

    blinkText.setPosition({WINDOW_WIDTH / 2, 600});

    float elapsedSeconds = m_blink_clock.getElapsedTime().asSeconds();

    float sineWave = std::sin(elapsedSeconds * 5.0f);

    std::uint8_t alpha = static_cast<std::uint8_t>(100.0f + (sineWave + 1.0f) * 77.5f);

    blinkText.setFillColor(sf::Color(255, 255, 255, alpha));

    window.draw(blinkText);
}