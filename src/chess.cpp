#include "chess.hpp"
#include "cassert"
#include "common.hpp"
#include <memory>
#include <utility>
#include <print>

//Piece Class
Piece::Piece(const PieceName& name, const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath) {
    assert(!imagePath.empty());
    image = LoadImage(imagePath.c_str());
    ImageResize(&image, PIECE_WIDTH, PIECE_HEIGHT);

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

const Image& Piece::getImage() {return image;}
void Piece::setImage(const std::string& imagePath) {
    assert(!imagePath.empty());
    image = LoadImage(imagePath.c_str());
    ImageResize(&image, PIECE_WIDTH, PIECE_HEIGHT);
}


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
//private:
void Board::endGame(End end) {
    switch(end) {
        case End::whiteWins:
            std::println("White wins!");
            break;

        case End::blackWins:
            std::println("Black wins!");
            break;

        case End::draw:
            std::println("Draw!");
            break;

        default:
            std::println("Undefined end");
            break;
    }
}

void Board::transformPiece(Square square, PieceName pieceName) {
    switch(pieceName) {
        case PieceName::bishop:
            cells[std::to_underlying(square.col)][std::to_underlying(square.row)] = std::make_unique<Bishop>(std::to_underlying(square.col), std::to_underlying(square.row), turn, std::format("../../img/{}/bishop1.png", playerColorCStr(turn)));
            break;

        case PieceName::knight:
            cells[std::to_underlying(square.col)][std::to_underlying(square.row)] = std::make_unique<Knight>(std::to_underlying(square.col), std::to_underlying(square.row), turn, std::format("../../img/{}/knight1.png", playerColorCStr(turn)));
            break;

        case PieceName::rook:
            cells[std::to_underlying(square.col)][std::to_underlying(square.row)] = std::make_unique<Rook>(std::to_underlying(square.col), std::to_underlying(square.row), turn, std::format("../../img/{}/rook.png", playerColorCStr(turn)));        
            break;

        case PieceName::queen:
            cells[std::to_underlying(square.col)][std::to_underlying(square.row)] = std::make_unique<Queen>(std::to_underlying(square.col), std::to_underlying(square.row), turn, std::format("../../img/{}/queen.png", playerColorCStr(turn)));
            break;
    }
}

void Board::castle(CastleSide castleSide) {
    assert(castleSide == CastleSide::kingSide || castleSide == CastleSide::queenSide);
    Row row;
    if (turn == PlayerColor::white) {
        assert(whiteCanCastle);
        row = Row::_1;
    } else {
        assert(blackCanCastle);
        row = Row::_8;
    }

    if (castleSide == CastleSide::kingSide) {
        assert(cells[std::to_underlying(Column::E)][std::to_underlying(row)]->getName() == PieceName::king);
        assert(cells[std::to_underlying(Column::F)][std::to_underlying(row)] == nullptr);
        assert(cells[std::to_underlying(Column::G)][std::to_underlying(row)] == nullptr);
        assert(cells[std::to_underlying(Column::H)][std::to_underlying(row)]->getName() == PieceName::rook);

        cells[std::to_underlying(Column::F)][std::to_underlying(row)] = std::move(cells[std::to_underlying(Column::E)][std::to_underlying(row)]);
        cells[std::to_underlying(Column::G)][std::to_underlying(row)] = std::move(cells[std::to_underlying(Column::H)][std::to_underlying(row)]);
    } else {
        assert(cells[std::to_underlying(Column::A)][std::to_underlying(row)]->getName() == PieceName::rook);
        assert(cells[std::to_underlying(Column::C)][std::to_underlying(row)] == nullptr);
        assert(cells[std::to_underlying(Column::C)][std::to_underlying(row)] == nullptr);
        assert(cells[std::to_underlying(Column::D)][std::to_underlying(row)] == nullptr);
        assert(cells[std::to_underlying(Column::E)][std::to_underlying(row)]->getName() == PieceName::king);

        cells[std::to_underlying(Column::C)][std::to_underlying(row)] = std::move(cells[std::to_underlying(Column::E)][std::to_underlying(row)]);
        cells[std::to_underlying(Column::D)][std::to_underlying(row)] = std::move(cells[std::to_underlying(Column::A)][std::to_underlying(row)]);
    }
}

void Board::drawOffer() {
    //To be implemented, make some kind of notification on the side of the board
    std::println(std::format("{} offered a draw!", playerColorCStr(turn)));
}

int32_t Board::findMove(Move& move) {
    
}


//public:
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
    cells[std::to_underlying(Column::A)][std::to_underlying(Row::_2)] = std::make_unique<Pawn>(Column::A, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[std::to_underlying(Column::B)][std::to_underlying(Row::_2)] = std::make_unique<Pawn>(Column::B, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[std::to_underlying(Column::C)][std::to_underlying(Row::_2)] = std::make_unique<Pawn>(Column::C, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[std::to_underlying(Column::D)][std::to_underlying(Row::_2)] = std::make_unique<Pawn>(Column::D, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[std::to_underlying(Column::E)][std::to_underlying(Row::_2)] = std::make_unique<Pawn>(Column::E, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[std::to_underlying(Column::F)][std::to_underlying(Row::_2)] = std::make_unique<Pawn>(Column::F, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[std::to_underlying(Column::G)][std::to_underlying(Row::_2)] = std::make_unique<Pawn>(Column::G, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
    cells[std::to_underlying(Column::H)][std::to_underlying(Row::_2)] = std::make_unique<Pawn>(Column::H, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");

    cells[std::to_underlying(Column::A)][std::to_underlying(Row::_1)] = std::make_unique<Rook>(Column::A, Row::_1, PlayerColor::white, "../../img/white/rook1.png");
    cells[std::to_underlying(Column::B)][std::to_underlying(Row::_1)] = std::make_unique<Knight>(Column::B, Row::_1, PlayerColor::white, "../../img/white/knight1.png");
    cells[std::to_underlying(Column::C)][std::to_underlying(Row::_1)] = std::make_unique<Bishop>(Column::C, Row::_1, PlayerColor::white, "../../img/white/bishop1.png");
    cells[std::to_underlying(Column::D)][std::to_underlying(Row::_1)] = std::make_unique<Queen>(Column::D, Row::_1, PlayerColor::white, "../../img/white/queen1.png");
    cells[std::to_underlying(Column::E)][std::to_underlying(Row::_1)] = std::make_unique<King>(Column::E, Row::_1, PlayerColor::white, "../../img/white/king1.png");
    cells[std::to_underlying(Column::F)][std::to_underlying(Row::_1)] = std::make_unique<Bishop>(Column::F, Row::_1, PlayerColor::white, "../../img/white/bishop1.png");
    cells[std::to_underlying(Column::G)][std::to_underlying(Row::_1)] = std::make_unique<Knight>(Column::G, Row::_1, PlayerColor::white, "../../img/white/knight1.png");
    cells[std::to_underlying(Column::H)][std::to_underlying(Row::_1)] = std::make_unique<Rook>(Column::H, Row::_1, PlayerColor::white, "../../img/white/rook1.png");

    //black pieces
    cells[std::to_underlying(Column::A)][std::to_underlying(Row::_7)] = std::make_unique<Pawn>(Column::A, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[std::to_underlying(Column::B)][std::to_underlying(Row::_7)] = std::make_unique<Pawn>(Column::B, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[std::to_underlying(Column::C)][std::to_underlying(Row::_7)] = std::make_unique<Pawn>(Column::C, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[std::to_underlying(Column::D)][std::to_underlying(Row::_7)] = std::make_unique<Pawn>(Column::D, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[std::to_underlying(Column::E)][std::to_underlying(Row::_7)] = std::make_unique<Pawn>(Column::E, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[std::to_underlying(Column::F)][std::to_underlying(Row::_7)] = std::make_unique<Pawn>(Column::F, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[std::to_underlying(Column::G)][std::to_underlying(Row::_7)] = std::make_unique<Pawn>(Column::G, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
    cells[std::to_underlying(Column::H)][std::to_underlying(Row::_7)] = std::make_unique<Pawn>(Column::H, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");

    cells[std::to_underlying(Column::A)][std::to_underlying(Row::_8)] = std::make_unique<Rook>(Column::A, Row::_8, PlayerColor::black, "../../img/black/rook1.png");
    cells[std::to_underlying(Column::B)][std::to_underlying(Row::_8)] = std::make_unique<Knight>(Column::B, Row::_8, PlayerColor::black, "../../img/black/knight1.png");
    cells[std::to_underlying(Column::C)][std::to_underlying(Row::_8)] = std::make_unique<Bishop>(Column::C, Row::_8, PlayerColor::black, "../../img/black/bishop1.png");
    cells[std::to_underlying(Column::D)][std::to_underlying(Row::_8)] = std::make_unique<Queen>(Column::D, Row::_8, PlayerColor::black, "../../img/black/queen1.png");
    cells[std::to_underlying(Column::E)][std::to_underlying(Row::_8)] = std::make_unique<King>(Column::E, Row::_8, PlayerColor::black, "../../img/black/king1.png");
    cells[std::to_underlying(Column::F)][std::to_underlying(Row::_8)] = std::make_unique<Bishop>(Column::F, Row::_8, PlayerColor::black, "../../img/black/bishop1.png");
    cells[std::to_underlying(Column::G)][std::to_underlying(Row::_8)] = std::make_unique<Knight>(Column::G, Row::_8, PlayerColor::black, "../../img/black/knight1.png");
    cells[std::to_underlying(Column::H)][std::to_underlying(Row::_8)] = std::make_unique<Rook>(Column::H, Row::_8, PlayerColor::black, "../../img/black/rook1.png");
}

void Board::movePiece(const Square from, const Square to) {
    assert(from.col >= Column::A && from.col <= Column::H);
    assert(from.row >= Row::_1 && from.row <= Row::_8);
    assert(to.col >= Column::A && to.col <= Column::H);
    assert(to.row >= Row::_1 && to.row <= Row::_8);

    std::unique_ptr<Piece>& fromPiece = cells[std::to_underlying(from.col)][std::to_underlying(from.row)];
    std::unique_ptr<Piece>& toPiece = cells[std::to_underlying(to.col)][std::to_underlying(to.row)];

    //making sure there is a piece at the from position.
    assert(fromPiece != nullptr);

    //checking whether the color of the from piece is different from the to piece, if it exists. 
    if(toPiece != nullptr) {
        assert(fromPiece->getPlayer() != toPiece->getPlayer());
    }

    //check if the move is a valid move for the piece.
    //check if the move is allowed according to the position, e.g. don't move through pieces, dont check yourself etc.

    toPiece = std::move(fromPiece);
    toPiece->setCol(to.col);
    toPiece->setRow(to.row);
    return;
}

void Board::doMove(Move& move) {
    check = move.check;

    //if the from square is given, the to square is also always given. else they should be defined as none
    if (move.from.col >= Column::A && move.from.col <= Column::H && move.from.row >= Row::_1 && move.from.row <= Row::_8) {
        movePiece(move.from, move.to);
        return;
    }

    if (move.capture) {
        // implement game rules first
        
        int32_t ret = findMove(move);
        if (!(ret)) {
            std::println("Could not find move");
            return;
        }
        movePiece(move.from, move.to);
        return;
    }

    if (move.enPassant) {
        Square from, to = {};
        from.col = move.from.col;
        move.to.row == Row::_3 ? from.row = Row::_4 : from.row = Row::_5;

        to.col = move.to.col;
        to.row = move.to.row;

        removePiece(Square{to.col, from.row});
        movePiece(from, to);
        return;
    }

    if (move.promotion) {
        assert(move.promotionPiece != PieceName::none);
        transformPiece(move.from, move.promotionPiece);
        
        Square from, to = {};
        from.col = move.to.col;
        move.to.row == Row::_1 ? from.row = Row::_2 : from.row = Row::_7;
        to = move.to;
        movePiece(from, to);
        return;
    }

    if (move.castle) {
        assert(move.castleSide != CastleSide::none);
        castle(move.castleSide);
        return;
    }

    if (move.endOfGame) {
        assert(move.end != End::none);
        endGame(move.end);
        return;
    }

    if(move.drawOffer) {
        drawOffer();
        return;
    }
    return;
}
