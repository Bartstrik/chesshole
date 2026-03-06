#pragma once

#include <vector>
#include <string>
#include "chess.hpp"
#include "common.hpp"

/*
    Converts an algebraic notation set of moves into a vector of moves stored as strings. For example:
    1. f3 e5 2. g4 Qh4# -> {"f3", "e5", "g4", "Qh4#"}
*/

void parseAN(const std::string& str, std::vector<std::string>& dest);
const Move parseMove(const std::string str);
void parseMoveWithPieceKnown(Move& move, std::string::const_iterator begin, std::string::const_iterator end);
std::vector<Move> parseMoveSet(std::vector<std::string>& moveSet);

