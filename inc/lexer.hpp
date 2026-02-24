#pragma once

#include <vector>
#include <string>
#include "chess.hpp"

/*
    Converts an algebraic notation set of moves into a vector of moves stored as strings. For example:
    1. f3 e5 2. g4 Qh4# -> {"f3", "e5", "g4", "Qh4#"}
*/

enum class PieceName : uint8_t {
  pawn,
  rook,
  knight,
  bishop,
  queen,
  king  
};

enum class End : uint8_t {
    whiteWins,
    blackWins,
    draw
};

enum class CastleSide : uint8_t {
    kingSide,
    queenSide,
};

struct MoveDesc {
    Square from;
    Square to;

    PieceName piece;
    PieceName promotionPiece;
    
    End end;
    CastleSide castleSide;

    bool capture = false;
    bool enPassant = false;
    bool promotion = false;
    bool castle = false;
    bool check = false;
    bool checkmate = false;
    bool drawOffer = false;
    bool endOfGame = false;
    bool castle = false;
};

void parseAN(const std::string& str, std::vector<std::string>& dest);
const MoveDesc parseMove(const std::string str);
void parseMoveWithPieceKnown(MoveDesc& move, std::string::const_iterator begin, std::string::const_iterator end);
std::vector<MoveDesc> parseMoveSet(std::vector<std::string>& moveSet);

