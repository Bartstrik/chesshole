# chesshole
my chess engine using raylib

# TODO
- [x] Start by making and visualizing a board with all pieces on it.
- [x] Implement piece movements
- [] Implement game string lexer
- [] Implement board method which finds the Move from the MoveDesc and the current board state 
- [] Implement rules
- [] make board.turn update every move
- [] make function which returns a random image using something like std::format("../../img/{}/{}{}.png", playerColorCStr(turn), pieceNameCStr(pieceName), somerandomnum)
- [] consider overriding the board.cells [] operators to work with column and row types
- [] set player can castle to false after rook or king move