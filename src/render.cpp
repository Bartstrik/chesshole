#include "render.hpp"
#include <iostream>
#include <memory>
#include "assert.h"
#include "common.hpp"

Rectangle RectangleFromCell(std::string cell) {
    assert(cell.size() == 2);

    uint8_t row, col;
    std::string validCols = "abcdefgh";
    std::string validRows = "12345678";
    bool correctCol = false;
    bool correctRow = false;

    cell[0] = tolower(cell[0]);
    for(uint8_t i = 0; i < validCols.size(); i++) {
        if (cell[0] == validCols[i]) {
            correctCol = true;
            col = i;
        }
    }
    assert(correctCol);

    for(uint8_t i = 0; i < validRows.size(); i++) {
        if (cell[1] == validRows[i]) {
            correctRow = true;
            row = i;
        }
    }
    assert(correctRow);

    //creating the rectangle type
    float x = static_cast<float>(col) * CELL_WIDTH + CELL_PADDING_X + BOARD_PADDING_X;
    float y = static_cast<float>(7 - row) * CELL_HEIGHT + CELL_PADDING_Y + BOARD_PADDING_Y;
    return Rectangle{x, y, PIECE_WIDTH, PIECE_HEIGHT};
}

Rectangle RectangleFromCell(const Column& col, const Row& row) {
    auto temp = static_cast<uint8_t>(col);
    assert(temp >= 0 && temp < 8);

    temp = static_cast<uint8_t>(row);
    assert(temp >= 0 && temp < 8);

    //creating the rectangle type
    float x = static_cast<float>(col) * CELL_WIDTH + CELL_PADDING_X + BOARD_PADDING_X;
    float y = (7 - static_cast<float>(row)) * CELL_HEIGHT + CELL_PADDING_Y + BOARD_PADDING_Y;
    return Rectangle{x, y, PIECE_WIDTH, PIECE_HEIGHT};
}

Rectangle baseRectangleFromImage(Image image) {return Rectangle{0, 0, static_cast<float>(image.width), static_cast<float>(image.height) };}






Window::Window(const int& screenWidth, const int& screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

Window::~Window() {
    UnloadTexture(texture);       

    CloseWindow();
}

void Window::init() {
    InitWindow(screenWidth, screenHeight, "Chesshole");
    SetTargetFPS(60); 
}

void Window::drawWindow() {
    BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);

    EndDrawing();
}

void Window::updateWindow() {
    board->boardImage = board->originalBoardImage;
    for (uint8_t col_iter = static_cast<uint8_t>(Column::A); col_iter <= static_cast<uint8_t>(Column::H); col_iter++) {
        for (uint8_t row_iter = static_cast<uint8_t>(Row::_1); row_iter <= static_cast<uint8_t>(Row::_8); row_iter++) {
            if (board->cells[col_iter][row_iter] != nullptr) {
                std::unique_ptr<Piece>& piece = board->cells[col_iter][row_iter];
                ImageDraw(&board->boardImage, piece->pieceImage, baseRectangleFromImage(piece->pieceImage), RectangleFromCell(piece->getCol(), piece->getRow()), WHITE);
            }
        }
    }

    texture = LoadTextureFromImage(board->boardImage);
}

void Window::setBoard(std::shared_ptr<Board> board) {
    this->board = board;
}