#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include "Game.hpp"
#include "Renderer.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Shogi", sf::Style::Titlebar | sf::Style::Close);

    sf::Music backgroundMusic;

    if (!backgroundMusic.openFromFile("assets/audio/Shogi_BGM.ogg"))
    {
        std::cerr << "Fehler: Musikdatei konnte nicht geladen werden!\n";
    }
    else
    {
        backgroundMusic.setLooping(true);
        backgroundMusic.setVolume(30.f);
        backgroundMusic.play();
    }

    GameState currentState = GameState::StartMenu;
    Renderer renderer;
    Game game;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            if (const auto *keyPress = event->getIf<sf::Event::KeyPressed>())
            {
                if (currentState == GameState::StartMenu || currentState == GameState::GameOver) 
                {
                    if (keyPress->code == sf::Keyboard::Key::Enter)
                    {
                        game = Game();
                        currentState = GameState::Playing;
                    }
                }
                else if (currentState == GameState::PromotionChoice) 
                {
                    if (keyPress->code == sf::Keyboard::Key::Y) 
                    {
                        game.executePromotionMove();
                        currentState = GameState::Playing;

                        if (game.isCheckmate()) 
                        {
                            currentState = GameState::GameOver;
                        }
                    }
                    else if (keyPress->code == sf::Keyboard::Key::N) 
                    {
                        game.executeNormalMove();
                        currentState = GameState::Playing;

                        if (game.isCheckmate())
                        {
                            currentState = GameState::GameOver;
                        }
                    }
                }
            }

            if (currentState == GameState::Playing) {
                if (const auto *mouseClick = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (currentState == GameState::Playing)
                    {
                        float mouseX = static_cast<float>(mouseClick->position.x);
                        float mouseY = static_cast<float>(mouseClick->position.y);

                        int boardX = static_cast<int>(std::floor((mouseX - BOARD_OFFSET_MOUSE_X) / (TILE_SIZE)));
                        int boardY = static_cast<int>(std::floor((mouseY - BOARD_OFFSET_MOUSE_Y) / (TILE_SIZE)));

                        if (boardX >= 0 && boardX < 9 && boardY >= 0 && boardY < 9)
                        {
                            Coordinates clickedCoords{boardX, boardY};

                            if (game.handleClickInput(clickedCoords)) 
                            {
                                currentState = GameState::PromotionChoice;
                            }
                        }
                        else
                        {
                            Player currentPlayer = game.getCurrentPlayer();
                            const Board &board = game.getBoard();

                            if (currentPlayer == Player::Sente)
                            {
                                std::map<PieceType, int> senteCounts;

                                for (const auto &piece : board.getHand(Player::Sente))
                                {
                                    senteCounts[piece.type()]++;
                                }

                                int indexSente = 0;

                                for (const auto &[type, count] : senteCounts)
                                {
                                    float posX = 805.f;
                                    float posY = 624.f - (indexSente * TILE_SIZE);

                                    if (mouseX >= posX && mouseX <= posX + PIECE_SIZE &&
                                        mouseY >= posY && mouseY <= posY + PIECE_SIZE)
                                    {
                                        game.makeDrop(type);
                                        break;
                                    }

                                    indexSente++;
                                }
                            }
                            else if (currentPlayer == Player::Gote)
                            {
                                std::map<PieceType, int> goteCounts;

                                for (const auto &piece : board.getHand(Player::Gote))
                                {
                                    goteCounts[piece.type()]++;
                                }

                                int indexGote = 0;
                                for (const auto &[type, count] : goteCounts)
                                {
                                    float posX = 15.f;
                                    float posY = 8.f - (indexGote * (TILE_SIZE * -1));

                                    if (mouseX >= posX && mouseX <= posX + PIECE_SIZE &&
                                        mouseY >= posY && mouseY <= posY + PIECE_SIZE)
                                    {
                                        game.makeDrop(type);
                                        break;
                                    }

                                    indexGote++;
                                }
                            }
                        }

                        if (currentState == GameState::Playing && game.isCheckmate())
                        {
                            currentState = GameState::GameOver;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color(82, 62, 47));

        renderer.draw(window, game.getBoard(), game.getSelectedBoardCoordinates(), game.getDrop(), game.getDropType(), game.getCurrentPlayer(), currentState, game.getWinner());
        
        window.display();
    }
}