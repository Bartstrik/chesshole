#pragma once

#include "common.hpp"
#include <string>
#include <vector>

/*
	Converts an algebraic notation set of moves into a vector of moves stored as
   strings. For example:
	1. f3 e5 2. g4 Qh4# -> {"f3", "e5", "g4", "Qh4#"}
*/

void parseAN(const std::string &str, std::vector<std::string> &dest);

const Move parseMove(const std::string &str);

void parseMoveWithPieceKnown(Move &move, std::string::const_iterator begin,
							 std::string::const_iterator end);

// converts the vector of moves in {"f3", "e5", "g4", "Qh4#"} format into a
// vector of individual moves

void parseMoveSet(std::vector<std::string> &moveSet, std::vector<Move> &dest);
