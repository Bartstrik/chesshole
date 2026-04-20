#include <assert.h>
#include <memory>

#include "chess.hpp"
#include "raylib.h"
#include "render.hpp"

int main(void) {

	SetTraceLogLevel(LOG_ERROR);

	Window window(600, 600);
	auto board = std::make_shared<Board>(std::format("{}/img/board.png", PROJECT_ROOT_DIR));
	window.setBoard(board);

	window.init(gameState::MainMenu);

	while (!WindowShouldClose()) // Detect window close button or ESC key
	{
		window.mousePoint = GetMousePosition();
		// Update
		window.updateWindow();
		// Draw
		window.drawWindow();
	}

	return 0;
}
