#include <assert.h>
#include "render.hpp"
#include "chess.hpp"
#include <memory>

int main(void)
{
    Window window(800, 800);
    auto board = std::make_shared<Board>("../../img/board.png");

    
    window.init();
    window.setBoard(board);
    board->setPieces();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        window.updateWindow();
        // Draw
        window.drawWindow();
    }


    return 0;
}