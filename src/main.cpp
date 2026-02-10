#include "raylib.h"
#include <iostream>
#include <assert.h>
#include <string>
#include <locale>

#define CELL_WIDTH 50
#define CELL_HEIGHT 50

#define PIECE_WIDTH 40
#define PIECE_HEIGHT 40

#define CELL_PADDING_X ((CELL_WIDTH - PIECE_WIDTH) / 2)
#define CELL_PADDING_Y ((CELL_HEIGHT - PIECE_HEIGHT) / 2)




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
    float x = static_cast<float>(col) * CELL_WIDTH + CELL_PADDING_X;
    float y = static_cast<float>(7 - row) * CELL_HEIGHT + CELL_PADDING_Y;
    return Rectangle{x, y, PIECE_WIDTH, PIECE_HEIGHT};
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - image drawing");

    Image board = LoadImage("../../img/board.png");
    ImageResize(&board, 8*CELL_WIDTH, 8*CELL_HEIGHT);

    Image pawn1 = LoadImage("../../img/pawn1.png");
    ImageResize(&pawn1, PIECE_WIDTH, PIECE_HEIGHT);
    std::cout << "resized pawn width = " << pawn1.width << ", height = " << pawn1.height << std::endl;

    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("A2"), WHITE);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("B2"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("C2"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("D2"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("E2"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("F2"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("G2"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("H2"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("A7"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("B7"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("C7"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("D7"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("E7"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("F7"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("G7"), BLACK);
    ImageDraw(&board, pawn1, Rectangle{0, 0, static_cast<float>(pawn1.width), static_cast<float>(pawn1.height) }, RectangleFromCell("H7"), BLACK);
    UnloadImage(pawn1);
    
    Texture2D texture = LoadTextureFromImage(board);
    UnloadImage(board);

    SetTargetFPS(60);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        
        // Draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);

        EndDrawing();
    }

    UnloadTexture(texture);       

    CloseWindow();

    return 0;
}