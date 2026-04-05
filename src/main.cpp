#include <assert.h>
#include <memory>
#include <string>
#include <vector>

#include "lexer.hpp"
#include "render.hpp"
#include "chess.hpp"

int main(void)
{
    Window window(500, 500);
    auto board = std::make_shared<Board>(std::format("{}/img/board.png", PROJECT_ROOT_DIR));
    window.setBoard(board);

    window.init(gameState::MainMenu);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        window.mousePoint = GetMousePosition();
        // Update
        window.updateWindow();
        // Draw
        window.drawWindow();
    }


    return 0;
}
