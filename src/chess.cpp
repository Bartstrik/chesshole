#include "chess.hpp"
#include "assert.h"
#include "common.hpp"
#include <memory>

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
    originalBoardImage = LoadImage(boardImagePath.c_str());
    ImageResize(&originalBoardImage, 8 * CELL_WIDTH + 2 * BOARD_PADDING_X, 8 * CELL_HEIGHT + 2 * BOARD_PADDING_Y);
}

Board::~Board() {} 

const std::string Board::getHistory() {return history;}
const PlayerColor Board::getTurn() {return turn;}

void Board::setPieces() {
    //should make this pick a random image from the pieces folder instead of hardcoding it
    std::unique_ptr<Piece> p1 = std::make_unique<Pawn>(Column::A, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    std::unique_ptr<Piece> p2 = std::make_unique<Pawn>(Column::B, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    //pawn for now
    std::unique_ptr<Piece> rook1 = std::make_unique<Pawn>(Column::A, Row::_1, PlayerColor::white, "../../img/white/rook.png");
    std::unique_ptr<Piece> rook2 = std::make_unique<Pawn>(Column::A, Row::_8, PlayerColor::black, "../../img/black/rook.png");

    cells[static_cast<uint8_t>(p1->getCol())][static_cast<uint8_t>(p1->getRow())] = std::move(p1);
    cells[static_cast<uint8_t>(p2->getCol())][static_cast<uint8_t>(p2->getRow())] = std::move(p2);
    cells[static_cast<uint8_t>(rook1->getCol())][static_cast<uint8_t>(rook1->getRow())] = std::move(rook1);
    cells[static_cast<uint8_t>(rook2->getCol())][static_cast<uint8_t>(rook2->getRow())] = std::move(rook2);

}