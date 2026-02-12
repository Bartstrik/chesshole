#include "chess.hpp"
#include "assert.h"

//Piece Class
Piece::Piece(const PieceName& name, const Column& col, const Row& row, const PlayerColor& player, const std::string& pieceImagePath) {
    assert(!pieceImagePath.empty());
    pieceImage = LoadImage(pieceImagePath.c_str());
    ImageResize(&pieceImage, PIECE_WIDTH, PIECE_HEIGHT);

    this->name = name;
    this->row = row;
    this->col = col;
    this->player = player;
}

Piece::~Piece() {}

const PieceName Piece::getName() {return name;}
void Piece::setName(const PieceName& name) {this->name = name;}

const Row Piece::getRow() {return row;}
void Piece::setRow(const Row& row) {this->row = row;}

const Column Piece::getCol() {return col;}
void Piece::setCol(const Column& col) {this->col = col;}

const PlayerColor Piece::getPlayer() {return player;}


//Pawn Class
Pawn::Pawn(const Column& col, const Row& row, const PlayerColor& player, const std::string& pawnImagePath) : Piece(PieceName::pawn, col, row, player, pawnImagePath) {}

Pawn::~Pawn() {}


//Board Class
Board::Board(const std::string& boardImagePath) {
    assert(!boardImagePath.empty());
    boardImage = LoadImage(boardImagePath.c_str());
    ImageResize(&boardImage, 8 * CELL_WIDTH + 2 * BOARD_PADDING_X, 8 * CELL_HEIGHT + 2 * BOARD_PADDING_Y);
}

Board::~Board() {} 

const std::string Board::getHistory() {return history;}
const PlayerColor Board::getTurn() {return turn;}
