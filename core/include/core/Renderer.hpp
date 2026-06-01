#pragma once

#include <SFML/Graphics.hpp>
#include "Board.hpp"

class Renderer {
    public:
        Renderer();

        void draw(sf::RenderWindow &window, const Board &board);

    private:
        void drawBoard(sf::RenderWindow &window, const Board &board);
};