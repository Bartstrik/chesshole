#include "chess.hpp"
#include "assert.h"
#include "common.hpp"
#include <memory>
#include <utility>

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
Pawn::Pawn(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath) : Piece(PieceName::pawn, col, row, player, imagePath) {}

Pawn::~Pawn() {}

//Rook Class
Rook::Rook(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath) : Piece(PieceName::rook, col, row, player, imagePath) {}

Rook::~Rook() {}

//Knight Class
Knight::Knight(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath) : Piece(PieceName::knight, col, row, player, imagePath) {}

Knight::~Knight() {}

//Bishop Class
Bishop::Bishop(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath) : Piece(PieceName::bishop, col, row, player, imagePath) {}

Bishop::~Bishop() {}

//Queen Class
Queen::Queen(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath) : Piece(PieceName::queen, col, row, player, imagePath) {}

Queen::~Queen() {}

//King Class
King::King(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath) : Piece(PieceName::king, col, row, player, imagePath) {}

King::~King() {}

//Board Class
Board::Board(const std::string& boardImagePath) {
    assert(!boardImagePath.empty());
    originalBoardImage = LoadImage(boardImagePath.c_str());
    ImageResize(&originalBoardImage, 8 * CELL_WIDTH + 2 * BOARD_PADDING_X, 8 * CELL_HEIGHT + 2 * BOARD_PADDING_Y);
}

Board::~Board() {} 

const std::string Board::getHistory() {return history;}
const PlayerColor Board::getTurn() {return turn;}

//should make this pick a random image from the pieces folder instead of hardcoding it
void Board::setPieces() {
    //white piece
    cells[static_cast<std::size_t>(Column::A)][static_cast<std::size_t>(Row::_2)] = std::make_unique<Pawn>(Column::A, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[static_cast<std::size_t>(Column::B)][static_cast<std::size_t>(Row::_2)] = std::make_unique<Pawn>(Column::B, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[static_cast<std::size_t>(Column::C)][static_cast<std::size_t>(Row::_2)] = std::make_unique<Pawn>(Column::C, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[static_cast<std::size_t>(Column::D)][static_cast<std::size_t>(Row::_2)] = std::make_unique<Pawn>(Column::D, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[static_cast<std::size_t>(Column::E)][static_cast<std::size_t>(Row::_2)] = std::make_unique<Pawn>(Column::E, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[static_cast<std::size_t>(Column::F)][static_cast<std::size_t>(Row::_2)] = std::make_unique<Pawn>(Column::F, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[static_cast<std::size_t>(Column::G)][static_cast<std::size_t>(Row::_2)] = std::make_unique<Pawn>(Column::G, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[static_cast<std::size_t>(Column::H)][static_cast<std::size_t>(Row::_2)] = std::make_unique<Pawn>(Column::H, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");

    cells[static_cast<std::size_t>(Column::A)][static_cast<std::size_t>(Row::_1)] = std::make_unique<Rook>(Column::A, Row::_1, PlayerColor::white, "../../img/white/rook1.png");
    cells[static_cast<std::size_t>(Column::B)][static_cast<std::size_t>(Row::_1)] = std::make_unique<Knight>(Column::B, Row::_1, PlayerColor::white, "../../img/white/knight1.png");
    cells[static_cast<std::size_t>(Column::C)][static_cast<std::size_t>(Row::_1)] = std::make_unique<Bishop>(Column::C, Row::_1, PlayerColor::white, "../../img/white/bishop1.png");
    cells[static_cast<std::size_t>(Column::D)][static_cast<std::size_t>(Row::_1)] = std::make_unique<Queen>(Column::D, Row::_1, PlayerColor::white, "../../img/white/queen1.png");
    cells[static_cast<std::size_t>(Column::E)][static_cast<std::size_t>(Row::_1)] = std::make_unique<King>(Column::E, Row::_1, PlayerColor::white, "../../img/white/king1.png");
    cells[static_cast<std::size_t>(Column::F)][static_cast<std::size_t>(Row::_1)] = std::make_unique<Bishop>(Column::F, Row::_1, PlayerColor::white, "../../img/white/bishop1.png");
    cells[static_cast<std::size_t>(Column::G)][static_cast<std::size_t>(Row::_1)] = std::make_unique<Knight>(Column::G, Row::_1, PlayerColor::white, "../../img/white/knight1.png");
    cells[static_cast<std::size_t>(Column::H)][static_cast<std::size_t>(Row::_1)] = std::make_unique<Rook>(Column::H, Row::_1, PlayerColor::white, "../../img/white/rook1.png");

    //black pieces
    cells[static_cast<std::size_t>(Column::A)][static_cast<std::size_t>(Row::_7)] = std::make_unique<Pawn>(Column::A, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[static_cast<std::size_t>(Column::B)][static_cast<std::size_t>(Row::_7)] = std::make_unique<Pawn>(Column::B, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[static_cast<std::size_t>(Column::C)][static_cast<std::size_t>(Row::_7)] = std::make_unique<Pawn>(Column::C, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[static_cast<std::size_t>(Column::D)][static_cast<std::size_t>(Row::_7)] = std::make_unique<Pawn>(Column::D, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[static_cast<std::size_t>(Column::E)][static_cast<std::size_t>(Row::_7)] = std::make_unique<Pawn>(Column::E, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[static_cast<std::size_t>(Column::F)][static_cast<std::size_t>(Row::_7)] = std::make_unique<Pawn>(Column::F, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[static_cast<std::size_t>(Column::G)][static_cast<std::size_t>(Row::_7)] = std::make_unique<Pawn>(Column::G, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[static_cast<std::size_t>(Column::H)][static_cast<std::size_t>(Row::_7)] = std::make_unique<Pawn>(Column::H, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");

    cells[static_cast<std::size_t>(Column::A)][static_cast<std::size_t>(Row::_8)] = std::make_unique<Rook>(Column::A, Row::_8, PlayerColor::black, "../../img/black/rook1.png");
    cells[static_cast<std::size_t>(Column::B)][static_cast<std::size_t>(Row::_8)] = std::make_unique<Knight>(Column::B, Row::_8, PlayerColor::black, "../../img/black/knight1.png");
    cells[static_cast<std::size_t>(Column::C)][static_cast<std::size_t>(Row::_8)] = std::make_unique<Bishop>(Column::C, Row::_8, PlayerColor::black, "../../img/black/bishop1.png");
    cells[static_cast<std::size_t>(Column::D)][static_cast<std::size_t>(Row::_8)] = std::make_unique<Queen>(Column::D, Row::_8, PlayerColor::black, "../../img/black/queen1.png");
    cells[static_cast<std::size_t>(Column::E)][static_cast<std::size_t>(Row::_8)] = std::make_unique<King>(Column::E, Row::_8, PlayerColor::black, "../../img/black/king1.png");
    cells[static_cast<std::size_t>(Column::F)][static_cast<std::size_t>(Row::_8)] = std::make_unique<Bishop>(Column::F, Row::_8, PlayerColor::black, "../../img/black/bishop1.png");
    cells[static_cast<std::size_t>(Column::G)][static_cast<std::size_t>(Row::_8)] = std::make_unique<Knight>(Column::G, Row::_8, PlayerColor::black, "../../img/black/knight1.png");
    cells[static_cast<std::size_t>(Column::H)][static_cast<std::size_t>(Row::_8)] = std::make_unique<Rook>(Column::H, Row::_8, PlayerColor::black, "../../img/black/rook1.png");
}

int Board::movePiece(const Move move) {
    assert(move.from.col >= Column::A && move.from.col <= Column::H);
    assert(move.from.row >= Row::_1 && move.from.row <= Row::_8);
    assert(move.to.col >= Column::A && move.to.col <= Column::H);
    assert(move.to.row >= Row::_1 && move.to.row <= Row::_8);

    std::unique_ptr<Piece>& fromPiece = cells[static_cast<std::size_t>(move.from.col)][static_cast<std::size_t>(move.from.row)];
    std::unique_ptr<Piece>& toPiece = cells[static_cast<std::size_t>(move.to.col)][static_cast<std::size_t>(move.to.row)];

    //making sure there is a piece at the from position.
    assert(fromPiece != nullptr);

    //checking whether the color of the from piece is different from the to piece, if it exists. 
    if(toPiece != nullptr) {
        assert(fromPiece->getPlayer() != toPiece->getPlayer());
    }

    //check if the move is a valid move for the piece.
    //check if the move is allowed according to the position, e.g. don't move through pieces, dont check yourself etc.

    toPiece = std::move(fromPiece);
    toPiece->setCol(move.to.col);
    toPiece->setRow(move.to.row);
    return 0;
}

const Move Board::findMove(const MoveDesc moveDesc) {
    Move move{};




    
    return move;
}
