#pragma once

#include "raylib.h"
#include <string>
#include "chess.hpp"
#include <memory>

#define STATES_AMOUNT 4
#define MAX_INPUT_CHARS 4096

enum class gameState : uint8_t {
    MainMenu,
    ANInput,
    PvP,
    PvE,
	Analysis,
};

class Window {
    private:
    int screenWidth, screenHeight;
    Texture2D texture;
    gameState state = gameState::MainMenu;
    Rectangle options[STATES_AMOUNT - 1] = { 0 };

	//ANInput
	Rectangle textBox = { 0 };
	Rectangle enterBox = { 0 };
	std::string text = "1. e4 c6 2. d4 d5 3. f3 Nf6 4. e5 Nfd7 5. Nc3 e6 6. Bd3 c5 7. Be3 Qb6 8. Bb5 Nc6 9. Nge2 a6 10. Bxc6 bxc6 11. Na4 Qb4+ 12. Nec3 cxd4 13. Bxd4 c5 14. Be3 d4 15. a3 Qb8 16. Bxd4 cxd4 17. Qxd4 Qxe5+ 18. Qxe5 Nxe5 19. O-O Bd7 20. Nb6 Rb8 21. Nxd7 Nxd7 22. b4 Be7 23. Rad1 Nf6 24. Na4 O-O 25. Nc5 Bxc5+ 26. bxc5 Rbc8 27. Rd6 Rxc5 28. Rxa6 Rxc2 29. a4 Ra2 30. a5 h6 31. Rc1 Rb8 32. Ra7 Nd5 33. a6 Rb6 34. Ra8+ Kh7 35. a7 Rba6 0-1";

	int16_t letterCount = 0;
	bool mouseOnText = false;

    std::vector<std::string> moveSetStr{};
    std::vector<Move> moveSet{};
    std::vector<Move>::const_iterator moveSetIt;

	//Analysis
	Rectangle skipBackRec;
	Rectangle stepBackRec;
	Rectangle pauseRec;
	Rectangle stepForRec;
	Rectangle skipForRec;
	bool pause = true;

    void initMM();
	void initANInput();
    void initA();
    void initPvP();
    void initPvE();

	void updateWindowMM();
	void updateWindowANInput();
	void updateWindowA();
	void updateWindowPvP();
	void updateWindowPvE();

	void drawWindowMM();
	void drawWindowANInput();
	void drawWindowA();
	void drawWindowPvP();
	void drawWindowPvE();

    void endGame();
	void loadGame();

    public:
    std::shared_ptr<Board> board;
    Vector2 mousePoint = { 0.0f, 0.0f };

    Window(const int screenWidth, const int screenHeight);
    ~Window();

    void init(const gameState state);
    void updateWindow();
    void drawWindow();
    void setBoard(std::shared_ptr<Board> board);
};

Rectangle RectangleFromCell(std::string& cell);

Rectangle RectangleFromCell(const Column col, const Row row);
