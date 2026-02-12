#include "chess.hpp"
#include "assert.h"

//Piece Class
Piece::Piece(const pieceName& name, const uint8_t& row, const uint8_t& col, const playerColor& player, const std::string& pieceImagePath) {
    assert(!pieceImagePath.empty());
    pieceImage = LoadImage(pieceImagePath.c_str());
    ImageResize(&pieceImage, PIECE_WIDTH, PIECE_HEIGHT);

    this->name = name;
    this->row = row;
    this->col = col;
    this->player = player;
}

Piece::~Piece() {}

const pieceName Piece::getName() {return name;}
void Piece::setName(const pieceName& name) {this->name = name;}

const uint8_t Piece::getRow() {return row;}
void Piece::setRow(const uint8_t& row) {this->row = row;}

const uint8_t Piece::getCol() {return col;}
void Piece::setCol(const uint8_t& col) {this->col = col;}

const playerColor Piece::getPlayer() {return player;}


//Pawn Class
Pawn::Pawn(const uint8_t& row, const uint8_t& col, const playerColor& player, const std::string& pawnImagePath) : Piece(pieceName::pawn, row, col, player, pawnImagePath) {}

Pawn::~Pawn() {}


//Board Class
Board::Board(const std::string& boardImagePath) {
    assert(!boardImagePath.empty());
    boardImage = LoadImage(boardImagePath.c_str());
    ImageResize(&boardImage, 8 * CELL_WIDTH + 2 * BOARD_PADDING_X, 8 * CELL_HEIGHT + 2 * BOARD_PADDING_Y);
}

Board::~Board() {} 

const std::string Board::getHistory() {return history;}
const playerColor Board::getTurn() {return turn;}
