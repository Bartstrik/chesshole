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
    
    window.init();
    window.setBoard(board);
    board->setPieces();

    
    std::string gameStr = "1. e4 c6 2. d4 d5 3. f3 Nf6 4. e5 Nfd7 5. Nc3 e6 6. Bd3 c5 7. Be3 Qb6 8. Bb5 Nc6 9. Nge2 a6 10. Bxc6 bxc6 11. Na4 Qb4+ 12. Nec3 cxd4 13. Bxd4 c5 14. Be3 d4 15. a3 Qb8 16. Bxd4 cxd4 17. Qxd4 Qxe5+ 18. Qxe5 Nxe5 19. O-O Bd7 20. Nb6 Rb8 21. Nxd7 Nxd7 22. b4 Be7 23. Rad1 Nf6 24. Na4 O-O 25. Nc5 Bxc5+ 26. bxc5 Rbc8 27. Rd6 Rxc5 28. Rxa6 Rxc2 29. a4 Ra2 30. a5 h6 31. Rc1 Rb8 32. Ra7 Nd5 33. a6 Rb6 34. Ra8+ Kh7 35. a7 Rba6 0-1";
    
    //converts the gameStr in individual strings
    std::vector<std::string> moveSetStr{};
    parseAN(gameStr, moveSetStr);  
   
    //converts the vector of moves in {"f3", "e5", "g4", "Qh4#"} format into a vector of individual moves
    std::vector<Move> moveSet{};
    parseMoveSet(moveSetStr, moveSet);

    auto moveSetIt = moveSet.begin();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (moveSetIt != moveSet.end()) {
            board->doMove(*moveSetIt);
            moveSetIt++;
        }

        if (board->getGameDone()) {
            window.endGame();
            window.drawWindow();
            while (1);
        }
        // Update
        window.updateWindow();
        // Draw
        window.drawWindow();
    }


    return 0;
}
