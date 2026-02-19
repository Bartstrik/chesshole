#pragma once

#include "raylib.h"
#include <string>
#include "chess.hpp"
#include <memory>

Rectangle RectangleFromCell(std::string& cell);

Rectangle RectangleFromCell(const Column col, const Row row);


class Window {
    private:
    int screenWidth, screenHeight;
    Texture2D texture;

    public:
    std::shared_ptr<Board> board;

    Window(const int screenWidth, const int screenHeight);
    ~Window();

    void init();
    void drawWindow(); 
    void updateWindow(); //is called after board changes
    void setBoard(std::shared_ptr<Board> board);
};

