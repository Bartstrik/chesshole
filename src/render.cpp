#include "render.hpp"
#include <iostream>
#include "assert.h"
#include "chess.hpp"

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

Window::Window(const int& screenWidth, const int& screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

Window::~Window() {
    UnloadTexture(texture);       

    CloseWindow();
}

void Window::init() {
    InitWindow(screenWidth, screenHeight, "");

    Board board("../../img/board.png");

    Pawn pawn1(0, 0, playerColor::black, "../../img/pawn1.png");

    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("A2"), WHITE);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("B2"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("C2"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("D2"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("E2"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("F2"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("G2"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("H2"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("A7"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("B7"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("C7"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("D7"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("E7"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("F7"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("G7"), BLACK);
    ImageDraw(&board.boardImage, pawn1.pieceImage, Rectangle{0, 0, static_cast<float>(pawn1.pieceImage.width), static_cast<float>(pawn1.pieceImage.height) }, RectangleFromCell("H7"), BLACK);
    UnloadImage(pawn1.pieceImage);
    
    texture = LoadTextureFromImage(board.boardImage);
    UnloadImage(board.boardImage);

    SetTargetFPS(60);
}

void Window::drawWindow() {
    BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);

    EndDrawing();
}