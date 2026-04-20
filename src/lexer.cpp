#include "lexer.hpp"
#include <cassert>

void parseAN(const std::string &str, std::vector<std::string> &dest) {
	assert((dest.empty()));
	assert(!(str.empty()));

	// split the string into substrings and remove the ones that contain a '.'
	std::size_t len = 0;
	bool valid = true;
	std::string::const_iterator it;

	for (it = str.begin(); it != str.end(); it++) {
		if (*it == '.') {
			valid = false;
			continue;
		}

		if (*it == ' ' || *it == '\r' || *it == '\n') {
			if (valid && len != 0) {
				dest.push_back(std::string(it - len, it));
			}

			valid = true;
			len = 0;
			// while (((*it + 1) == ' ' || (*it + 1) == '\r' || (*it + 1) ==
			// '\n')) it++;
			continue;
		}
		len++;
	}
	// add last entry aswell.
	if (len != 0)
		dest.push_back(std::string(it - len, it));
	return;
}
// A move can start with either a capital letter indicating the piece or with a
// lower case column indicating a pawn move.
/* 1. e4 c6 2. d4 d5 3. f3 Nf6 4. e5 Nfd7 5. Nc3 e6 6. Bd3 c5 7. Be3 Qb6 8. Bb5
Nc6
9. Nge2 a6 10. Bxc6 bxc6 11. Na4 Qb4+ 12. Nec3 cxd4 13. Bxd4 c5 14. Be3 d4 15.
a3 Qb8 16. Bxd4 cxd4 17. Qxd4 Qxe5+ 18. Qxe5 Nxe5 19. O-O Bd7 20. Nb6 Rb8 21.
Nxd7 Nxd7 22. b4 Be7 23. Rad1 Nf6 24. Na4 O-O 25. Nc5 Bxc5+ 26. bxc5 Rbc8 27.
Rd6 Rxc5 28. Rxa6 Rxc2 29. a4 Ra2 30. a5 h6 31. Rc1 Rb8 32. Ra7 Nd5 33. a6 Rb6
34. Ra8+ Kh7 35. a7 Rba6 0-1
*/
const Move parseMove(const std::string &str) {
	assert(!(str.empty()));

	Move move{};

	// No need to actually iterate, that will be done in
	// parseMoveWithPieceKnown()
	std::string::const_iterator it = str.begin();
	std::string::const_iterator end = str.end();
	switch (*it) {
	case 'R':
		move.piece = PieceName::rook;
		parseMoveWithPieceKnown(move, it + 1, end);
		break;

	case 'N':
		move.piece = PieceName::knight;
		parseMoveWithPieceKnown(move, it + 1, end);
		break;

	case 'B':
		move.piece = PieceName::bishop;
		parseMoveWithPieceKnown(move, it + 1, end);
		break;
	case 'Q':
		move.piece = PieceName::queen;
		parseMoveWithPieceKnown(move, it + 1, end);
		break;

	case 'K':
		move.piece = PieceName::king;
		parseMoveWithPieceKnown(move, it + 1, end);
		break;

	case '(':
		// Draw offer
		move.drawOffer = true;
		break;

	case '&':
		// End of game, with draw
		move.endOfGame = true;
		move.end = End::draw;
		break;

	case '0':
		move.endOfGame = true;
		move.end = (*(it + 2) == '1') ? End::blackWins : End::draw;
		break;

	case '1':
		move.endOfGame = true;
		move.end = End::whiteWins;
		break;

	case 'O':
		// Castle
		move.castle = true;
		if (it + 3 == end) {
			move.castleSide = CastleSide::kingSide;
		} else {
			move.castleSide = CastleSide::queenSide;
		}
		break;

	default:
		// Pawn
		move.piece = PieceName::pawn;
		parseMoveWithPieceKnown(move, str.begin(), end);
		break;
	}
	return move;
}

// Note: For pawns, the entire string is expected to be passed in, for other
// pieces, the first char is omitted
void parseMoveWithPieceKnown(Move &move, std::string::const_iterator begin, std::string::const_iterator end) {
	bool toRowSet = false;
	bool toColSet = false;

	for (std::string::const_iterator it = begin; it != end; it++) {
		if (*it >= 'a' && *it <= 'h') {
			if (toColSet) {
				move.from.col = move.to.col;
			}
			switch (*it) {
			case 'a':
				move.to.col = Column::A;
				break;
			case 'b':
				move.to.col = Column::B;
				break;
			case 'c':
				move.to.col = Column::C;
				break;
			case 'd':
				move.to.col = Column::D;
				break;
			case 'e':
				move.to.col = Column::E;
				break;
			case 'f':
				move.to.col = Column::F;
				break;
			case 'g':
				move.to.col = Column::G;
				break;
			case 'h':
				move.to.col = Column::H;
				break;
			default:
				assert(0);
				break;
			}
			toColSet = true;
			continue;
		}
		if (*it >= '1' && *it <= '8') {
			if (toRowSet) {
				move.from.row = move.to.row;
			}
			switch (*it) {
			case '1':
				move.to.row = Row::_1;
				break;
			case '2':
				move.to.row = Row::_2;
				break;
			case '3':
				move.to.row = Row::_3;
				break;
			case '4':
				move.to.row = Row::_4;
				break;
			case '5':
				move.to.row = Row::_5;
				break;
			case '6':
				move.to.row = Row::_6;
				break;
			case '7':
				move.to.row = Row::_7;
				break;
			case '8':
				move.to.row = Row::_8;
				break;
			default:
				assert(0);
				break;
			}
			toRowSet = true;
			continue;
		}

		switch (*it) {
		case 'x':
			move.capture = true;
			break;

		// multiple promotion notations
		case '=':
		case '(':
		case '/':
			move.promotion = true;
			assert(it + 1 != end);
			if (*(it + 1) == 'R')
				move.promotionPiece = PieceName::rook;
			if (*(it + 1) == 'N')
				move.promotionPiece = PieceName::knight;
			if (*(it + 1) == 'B')
				move.promotionPiece = PieceName::bishop;
			if (*(it + 1) == 'Q')
				move.promotionPiece = PieceName::king;
			return;

		case '+':
			move.check = true;
			break;

		case '#':
			move.checkmate = true;
			move.check = true;
			break;
		default:
			assert(0);
			break;
		}
	}
	return;
}

void parseMoveSet(std::vector<std::string> &moveSet, std::vector<Move> &dest) {
	assert(!(moveSet.empty()));
	assert(dest.empty());

	dest.reserve(moveSet.size());
	for (auto &moveStr : moveSet) {
		assert(!(moveStr.empty()));
		dest.emplace_back(parseMove(moveStr));
	}
}
