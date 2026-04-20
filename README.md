# chesshole
My attempt at a simple chess application using raylib.

Currently, only the analysis option is implemented, which allows the user to input a game in algebraic notation and watch the game unfold.
Playing a PvP or PvE game is not yet implemented.

Beware that this code has neither been optimized semantically nor for performance. I have been procrastinating this and plan to work on this after the basic gamemodes(Analysis, PvP, PvE) are finished.

# Instalation

To try out chesshole, simply clone the project (using --recursive to also get the raylib submodule) and build the project using cmake or whatever build tool you prefer.

# TODO
 - [x] Analysis: Implement the ability to step forward/backwards, skip to start/end
 - [x] Analysis: Implement pause/play feature
 - [] Analysis: Scan for edge case failures (for example, I'm pretty sure that  a pawn capture leading to a promotion would fail currently.)
 - [] General: Add option to go back to main menu
 - [] PvP: implement PvP game
 - [] PvE: implement PvE game
 - [] PvE: implement parellized position analyzer
 
