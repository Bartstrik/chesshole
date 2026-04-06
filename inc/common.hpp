#pragma once
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>

#define BOARD_WIDTH 410
#define BOARD_HEIGHT 410

#define CELL_WIDTH 50
#define CELL_HEIGHT 50

#define PIECE_WIDTH 46
#define PIECE_HEIGHT 46

#define CELL_PADDING_X ((CELL_WIDTH - PIECE_WIDTH) / 2)
#define CELL_PADDING_Y ((CELL_HEIGHT - PIECE_HEIGHT) / 2)

#define BOARD_PADDING_X ((BOARD_WIDTH - 8 * CELL_WIDTH) / 2)
#define BOARD_PADDING_Y ((BOARD_HEIGHT - 8 * CELL_HEIGHT) / 2)

enum class End : uint8_t { none, whiteWins, blackWins, draw };

enum class CastleSide : uint8_t {
	none,
	kingSide,
	queenSide,
};

enum class PlayerColor : uint8_t { none, white, black };

const char *playerColorCStr(const PlayerColor playerColor);

enum class PieceName : int8_t { none, pawn, bishop, knight, rook, queen, king };

std::ostream &operator<<(std::ostream &os, const PieceName &piece);

enum class Column : int8_t {
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	none,
};

std::ostream &operator<<(std::ostream &os, const Column &col);

enum class Row : int8_t {
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	none,
};

std::ostream &operator<<(std::ostream &os, const Row &row);

struct Square {
	Column col = Column::none;
	Row row = Row::none;

	constexpr bool operator==(auto sq) {
		return (this->col == sq.col && this->row == sq.row);
	}
};

struct Move {
	Square from;
	Square to;

	PieceName piece;
	PieceName promotionPiece;
	PieceName capturePiece;

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
};

constexpr Column &operator++(Column &col) {
	col = static_cast<Column>(std::to_underlying(col) + 1);
	return col;
}

constexpr Column &operator--(Column &col) {
	col = static_cast<Column>(std::to_underlying(col) - 1);
	return col;
}

constexpr Column &operator+=(Column &col, Column num) {
	col =
		static_cast<Column>(std::to_underlying(col) + std::to_underlying(num));
	return col;
}

constexpr Column &operator+=(Column &col, int8_t num) {
	col = static_cast<Column>(std::to_underlying(col) + num);
	return col;
}

constexpr Column operator+(Column col, Column num) {
	return static_cast<Column>(std::to_underlying(col) +
							   std::to_underlying(num));
}

constexpr Column operator-(Column col, Column num) {
	return static_cast<Column>(std::to_underlying(col) -
							   std::to_underlying(num));
}

constexpr Column operator+(Column col, int8_t num) {
	return static_cast<Column>(std::to_underlying(col) + num);
}

constexpr Column operator-(Column col, int8_t num) {
	return static_cast<Column>(std::to_underlying(col) - num);
}

constexpr Row &operator++(Row &row) {
	row = static_cast<Row>(std::to_underlying(row) + 1);
	return row;
}

constexpr Row &operator--(Row &row) {
	row = static_cast<Row>(std::to_underlying(row) - 1);
	return row;
}

constexpr Row &operator+=(Row &row, Row num) {
	row = static_cast<Row>(std::to_underlying(row) + std::to_underlying(num));
	return row;
}

constexpr Row &operator+=(Row &row, int8_t num) {
	row = static_cast<Row>(std::to_underlying(row) + num);
	return row;
}

constexpr Row operator+(Row row, Row num) {
	return static_cast<Row>(std::to_underlying(row) + std::to_underlying(num));
}

constexpr Row operator-(Row row, Row num) {
	return static_cast<Row>(std::to_underlying(row) - std::to_underlying(num));
}

constexpr Row operator+(Row row, int8_t num) {
	return static_cast<Row>(std::to_underlying(row) + num);
}

constexpr Row operator-(Row row, int8_t num) {
	return static_cast<Row>(std::to_underlying(row) - num);
}
