#pragma once

#include "raylib.h"
#include <string>
#include "chess.hpp"

Rectangle RectangleFromCell(std::string& cell);

class Window {
    private:
    int screenWidth, screenHeight;
    Texture2D texture;

    public:
    Board board;

    Window(const int& screenWidth, const int& screenHeight);
    ~Window();

    void init();
    void drawWindow(); 
    void addPieces();
    void updateWindow(); //is called after board changes
};

