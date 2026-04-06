#include "common.hpp"
#include "cassert"

const char *playerColorCStr(const PlayerColor playerColor) {
	switch (playerColor) {
	case PlayerColor::white:
		return "white";
	case PlayerColor::black:
		return "black";
	case PlayerColor::none:

	default:
		assert(0);
		return "";
	}
}

std::ostream &operator<<(std::ostream &os, const PieceName &piece) {
	switch (piece) {
	case PieceName::pawn:
		os << "pawn";
		break;

	case PieceName::rook:
		os << "rook";
		break;

	case PieceName::knight:
		os << "knight";
		break;

	case PieceName::bishop:
		os << "bishop";
		break;

	case PieceName::queen:
		os << "queen";
		break;

	case PieceName::king:
		os << "king";
		break;

	case PieceName::none:
		os << "none";
		break;

	default:
		assert(0);
		break;
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, const Column &col) {
	switch (col) {
	case Column::A:
		os << "A";
		break;

	case Column::B:
		os << "B";
		break;

	case Column::C:
		os << "C";
		break;

	case Column::D:
		os << "D";
		break;

	case Column::E:
		os << "E";
		break;

	case Column::F:
		os << "F";
		break;
	case Column::G:
		os << "G";
		break;

	case Column::H:
		os << "H";
		break;

	case Column::none:
		os << "none";
		break;

	default:
		assert(0);
		break;
	}
	return os;
}

std::ostream &operator<<(std::ostream &os, const Row &row) {
	switch (row) {
	case Row::_1:
		os << "1";
		break;

	case Row::_2:
		os << "2";
		break;

	case Row::_3:
		os << "3";
		break;

	case Row::_4:
		os << "4";
		break;

	case Row::_5:
		os << "5";
		break;

	case Row::_6:
		os << "6";
		break;

	case Row::_7:
		os << "7";
		break;

	case Row::_8:
		os << "8";
		break;

	case Row::none:
		os << "none";
		break;

	default:
		assert(0);
		break;
	}
	return os;
}
