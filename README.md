# chesshole
my chess engine using raylib

# TODO
1. [x] Start by making and visualizing a board with all pieces on it.
2. [x] Implement piece movements
3. [] Implement game string lexer
4. [] Implement board method which finds the Move from the MoveDesc and the current board state 
5. [] Implement rules
6. [] consider which enums should be strongly defined or weakly

# Implement board method which finds the Move from the MoveDesc and the current board state
[] implement endGame()
[] implement transformPiece()
[] implement game rules 
[] implement castling
[] make board.turn update every move
[] make function which returns a random image using something like std::format("../../img/{}/{}{}.png", playerColorCStr(turn), pieceNameCStr(pieceName), somerandomnum)
[] consider overriding the board.cells [] operators to work with column and row types
[] set player can castle to flase after check