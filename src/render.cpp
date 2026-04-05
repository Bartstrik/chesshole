#include "render.hpp"
#include <memory>
#include "assert.h"
#include "common.hpp"
#include "raylib.h"
#include "lexer.hpp"

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
    float y = (7.0f - static_cast<float>(row)) * CELL_HEIGHT + CELL_PADDING_Y + BOARD_PADDING_Y;
    return Rectangle{x, y, PIECE_WIDTH, PIECE_HEIGHT};
}

Rectangle RectangleFromCell(const Column col, const Row row) {
    assert(col >= Column::A && col <= Column::H);
    assert(row >= Row::_1 && row <= Row::_8);

    //creating the rectangle type
    float x = static_cast<float>(col) * CELL_WIDTH + CELL_PADDING_X + BOARD_PADDING_X;
    float y = (7.0f - static_cast<float>(row)) * CELL_HEIGHT + CELL_PADDING_Y + BOARD_PADDING_Y;
    return Rectangle{x, y, PIECE_WIDTH, PIECE_HEIGHT};
}

Rectangle baseRectangleFromImage(Image image) {return Rectangle{0, 0, static_cast<float>(image.width), static_cast<float>(image.height) };}






Window::Window(const int screenWidth, const int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    InitWindow(screenWidth, screenHeight, "Chesshole");
    SetTargetFPS(60); 
}

Window::~Window() {
    UnloadTexture(texture);       
    CloseWindow();
}

void Window::initState(const gameState state) {
    switch (state) {
        case gameState::MainMenu:
            initMainMenu();
            break;

        case gameState::Analysis:
            initAnalysis();
            break;

        case gameState::PvP:
            initPvP();
            break;

        case gameState::PvE:
            initPvE();
            break;

        default:
            assert(0);
            break;
    }
}

void Window::initMainMenu() {
    state = gameState::MainMenu;
    
    for (int i = 0; i < STATES_AMOUNT - 1; i++) {
        options[i].x = screenWidth * 0.1f;
        options[i].y = i * screenHeight * 0.25f + screenHeight * 0.1f;

        options[i].width = screenWidth * 0.8f;
        options[i].height = screenHeight * 0.2f;
    }
}

void Window::initAnalysis() {

    state = gameState::Analysis;

	textBox = {screenWidth * 0.1f, screenHeight * 0.3f, screenWidth * 0.8f, screenHeight * 0.4f};
	text.reserve(MAX_INPUT_CHARS);
	letterCount = text.size();

	enterBox = {screenWidth * 0.75f, screenHeight * 0.75f, screenWidth * 0.1f, screenHeight * 0.05f};
}

void Window::initPvP() {
    //state = gameState::PvP;
}

void Window::initPvE() {
    //state = gameState::PvE;
}

void Window::updateWindow() {
    switch (state) {
        case (gameState::MainMenu):
            // checking if any of the options are pressed
            for (uint8_t i = 0; i < STATES_AMOUNT - 1; i++) {
                if (CheckCollisionPointRec(mousePoint, options[i]) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    initState(static_cast<gameState>(i + 1));
                }
            }
            break;

        case (gameState::Analysis):
			if (!ANloaded) {
				mouseOnText = CheckCollisionPointRec(GetMousePosition(), textBox);
				if (mouseOnText) {
					SetMouseCursor(MOUSE_CURSOR_IBEAM);
					int key = GetKeyPressed();
					
					//CTRL+BACKSPACE
					if (IsKeyPressed(KEY_BACKSPACE) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
						letterCount = 0;
						text.clear();
						text.reserve(MAX_INPUT_CHARS);

					//CTRL+V (paste clipboard)
					} else if (IsKeyPressed(KEY_V) && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
						std::string clip = GetClipboardText();
						if (clip.size() + letterCount <= MAX_INPUT_CHARS) {
							text.append(clip.c_str());
							letterCount += clip.size();
						}

					//backspace
					} else if (IsKeyPressed(KEY_BACKSPACE)) {
						if (letterCount > 0) {
							letterCount--;
							text.pop_back();
						}

					//normale case
					} else {
						//check for multiple keypresses
						while (key > 0) {
							if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
								text.push_back(static_cast<char>(key));
								letterCount++;
							}
							key = GetKeyPressed();
						}
					}

				} else {
					SetMouseCursor(MOUSE_CURSOR_DEFAULT);
				}

                if (CheckCollisionPointRec(mousePoint, enterBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
					loadGame();
					ANloaded = true;
				}
			} else {
				if (moveSetIt != moveSet.end()) {
					board->doMove(*moveSetIt);
					moveSetIt++;
				}

				if (board->getGameDone()) {
					endGame();
					drawWindow();
					while (1);
				}

				board->boardImage = ImageCopy(board->originalBoardImage);
				for (Column col_iter = Column::A; col_iter <= Column::H; ++col_iter) {
					for (Row row_iter = Row::_1; row_iter <= Row::_8; ++row_iter) {
						auto& piece = board->cells[col_iter][row_iter];
						if (piece != nullptr) {
							ImageDraw(&board->boardImage, piece->getImage(), baseRectangleFromImage(piece->getImage()), RectangleFromCell(piece->getCol(), piece->getRow()), WHITE);
						}
					}
				}

				texture = LoadTextureFromImage(board->boardImage);
			}
            break;

        case (gameState::PvP):
            break;

        case (gameState::PvE):
            break;

        default:
            assert(0);
            break;
    }
}

void Window::drawWindow() {
    BeginDrawing();
    switch (state) {
        case (gameState::MainMenu):
            ClearBackground(RAYWHITE);

            // Draw Rectangles
            for (int i = 0; i < STATES_AMOUNT - 1; i++) {
                DrawRectangleRec(options[i], GRAY);
            }

            DrawText("Main Menu", screenWidth * 0.4f, screenHeight * 0.9f, 20, BLACK);
			DrawText("Analysis", screenWidth * 0.4f, screenHeight * 0.175f, 20, BLACK);
            DrawText("PvP", screenWidth * 0.45f, screenHeight * 0.425f, 20, BLACK);
            DrawText("PvE", screenWidth * 0.45f, screenHeight * 0.675f, 20, BLACK);

            break;

        case (gameState::Analysis):
            ClearBackground(RAYWHITE);
			if (!ANloaded) {
				DrawText("Please insert the game in algebraic notations below", screenWidth * 0.1f, screenHeight * 0.2f, 20, GRAY);
				DrawRectangleRec(textBox, LIGHTGRAY);
				if (mouseOnText) {
					DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), RED);
				} else {
					DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), DARKGRAY);
				}
				DrawText(text.c_str(), static_cast<int>(textBox.x + 5), static_cast<int>(textBox.y + 8), 40, MAROON);
				DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), screenWidth * 0.1f, screenHeight * 0.8f, 20, GRAY);

				//Enter button
				DrawRectangleRec(enterBox, LIGHTGRAY);
				DrawText("Enter", screenWidth * 0.75f, screenHeight * 0.75f, 20, DARKGRAY);
			} else {
            	DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);
			}
			break;

        case (gameState::PvP):
            break;

        case (gameState::PvE):
            break;

        default:
            assert(0);
            break;
    }
    EndDrawing();
}


void Window::endGame() {
    switch (board->getGameEnd()) {
        case PlayerColor::white:
            texture = LoadTextureFromImage(LoadImage(std::format("{}/img/end/whiteWins.png", PROJECT_ROOT_DIR).c_str()));
            break;

        case PlayerColor::black:
            texture = LoadTextureFromImage(LoadImage(std::format("{}/img/end/blackWins.png", PROJECT_ROOT_DIR).c_str()));
            break;

        case PlayerColor::none:
            texture = LoadTextureFromImage(LoadImage(std::format("{}/img/end/draw.png", PROJECT_ROOT_DIR).c_str()));
            break;

        default:
            assert(0);
            break;
    } 
}

void Window::setBoard(std::shared_ptr<Board> board) {
    this->board = board;
}

void Window::loadGame() {
    board->setPieces();
    
    // converts the gameStr in individual strings
    parseAN(text, moveSetStr);  
   
    // converts the vector of moves in {"f3", "e5", "g4", "Qh4#"} format into a vector of individual moves
    parseMoveSet(moveSetStr, moveSet);

    moveSetIt = moveSet.begin();
}
