#pragma once
#include <cstdint>

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



enum class End : uint8_t {
    none,
    whiteWins,
    blackWins,
    draw
};

enum class CastleSide : uint8_t {
    none,
    kingSide,
    queenSide,
};

enum class PlayerColor : uint8_t {
    none,
    white,
    black
};

const char * playerColorCStr(const PlayerColor playerColor);

enum class PieceName : uint8_t {
    none,
    pawn,
    bishop,
    knight,
    rook,
    queen,
    king
};

//maybe go back to weakly defined enums, so i don't have to typecast it
enum class Column : uint8_t {
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

constexpr Column operator++(const Column col);

constexpr Column operator+(const Column col, const Column num);
constexpr Column operator-(const Column col, const Column num);

constexpr Column operator+(const Column col, const uint8_t num);
constexpr Column operator-(const Column col, const uint8_t num);

enum class Row : uint8_t {
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

constexpr Row operator++(const Row row);

constexpr Row operator+(const Row row, const Row num);
constexpr Row operator-(const Row row, const Row num);

constexpr Row operator+(const Row row, const uint8_t num);
constexpr Row operator-(const Row row, const uint8_t num);


struct Square {
    Column col = Column::none;
    Row row = Row::none;
};

struct Move {
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
};