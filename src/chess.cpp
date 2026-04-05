#include <memory>
#include <iostream>
#include <utility>
#include <vector>
#include <format>

#include "chess.hpp"
#include "cassert"
#include "common.hpp"

// Piece Class
Piece::Piece(const PieceName &name, const Column &col, const Row &row,
             const PlayerColor &player, const std::string &imagePath) {
  assert(!imagePath.empty());
  image = LoadImage(imagePath.c_str());
  ImageResize(&image, PIECE_WIDTH, PIECE_HEIGHT);

  this->name = name;
  this->row = row;
  this->col = col;
  this->player = player;
}

Piece::~Piece() {}

const PieceName Piece::getName() const { return name; }
void Piece::setName(const PieceName &name) { this->name = name; }

const Row Piece::getRow() const { return row; }
void Piece::setRow(const Row &row) { this->row = row; }

const Column Piece::getCol() const { return col; }
void Piece::setCol(const Column &col) { this->col = col; }

const Square Piece::getSquare() const { return {col, row}; }
void Piece::setSquare(const Square& sq) { this->col = sq.col; this->row = sq.row; }

const PlayerColor Piece::getPlayerColor() const { return player; }

const Image &Piece::getImage() const { return image; }
void Piece::setImage(const std::string &imagePath) {
  assert(!imagePath.empty());
  image = LoadImage(imagePath.c_str());
  ImageResize(&image, PIECE_WIDTH, PIECE_HEIGHT);
}

// Pawn Class
Pawn::Pawn(const Column &col, const Row &row, const PlayerColor &player,
           const std::string &imagePath)
    : Piece(PieceName::pawn, col, row, player, imagePath) {}

Pawn::~Pawn() {}

// Rook Class
Rook::Rook(const Column &col, const Row &row, const PlayerColor &player,
           const std::string &imagePath)
    : Piece(PieceName::rook, col, row, player, imagePath) {}

Rook::~Rook() {}

// Knight Class
Knight::Knight(const Column &col, const Row &row, const PlayerColor &player,
               const std::string &imagePath)
    : Piece(PieceName::knight, col, row, player, imagePath) {}

Knight::~Knight() {}

// Bishop Class
Bishop::Bishop(const Column &col, const Row &row, const PlayerColor &player,
               const std::string &imagePath)
    : Piece(PieceName::bishop, col, row, player, imagePath) {}

Bishop::~Bishop() {}

// Queen Class
Queen::Queen(const Column &col, const Row &row, const PlayerColor &player,
             const std::string &imagePath)
    : Piece(PieceName::queen, col, row, player, imagePath) {}

Queen::~Queen() {}

// King Class
King::King(const Column &col, const Row &row, const PlayerColor &player,
           const std::string &imagePath)
    : Piece(PieceName::king, col, row, player, imagePath) {}

King::~King() {}

// Board Class
// private:
void Board::toggleTurn() {
  turn = (turn == PlayerColor::black) ? PlayerColor::white : PlayerColor::black;
}

void Board::endGame(const End& end) {
  switch (end) {
  case End::whiteWins:
    std::cout << "White wins!" << std::endl;
    gameEnd = PlayerColor::white;
    break;

  case End::blackWins:
    std::cout << "Black wins!" << std::endl;
    gameEnd = PlayerColor::black;
    break;

  case End::draw:
    std::cout << "Draw!" << std::endl;
    gameEnd = PlayerColor::none;
    break;

  default:
    std::cout << "Undefined end" << std::endl;
    break;
  }
  gameDone = true;
}

void Board::transformPiece(const Square& square, const PieceName& pieceName) {
  switch (pieceName) {
  case PieceName::bishop:
    cells[square.col][square.row] = std::make_unique<Bishop>(
        square.col, square.row, turn,
        std::format("{}/img/{}/bishop1.png", PROJECT_ROOT_DIR, playerColorCStr(turn)));
    break;

  case PieceName::knight:
    cells[square.col][square.row] = std::make_unique<Knight>(
        square.col, square.row, turn,
        std::format("{}/img/{}/knight1.png", PROJECT_ROOT_DIR, playerColorCStr(turn)));
    break;

  case PieceName::rook:
    cells[square.col][square.row] = std::make_unique<Rook>(
        square.col, square.row, turn,
        std::format("{}/img/{}/rook.png", PROJECT_ROOT_DIR, playerColorCStr(turn)));
    break;

  case PieceName::queen:
    cells[square.col][square.row] = std::make_unique<Queen>(
        square.col, square.row, turn,
        std::format("{}/img/{}/queen.png", PROJECT_ROOT_DIR, playerColorCStr(turn)));
    break;
  default:
    assert(0);
  }
}

void Board::castle(const CastleSide& castleSide) {
  assert(castleSide == CastleSide::kingSide ||
         castleSide == CastleSide::queenSide);
  Row row;
  if (turn == PlayerColor::white) {
    assert(whiteCanCastle);
    row = Row::_1;
  } else {
    assert(blackCanCastle);
    row = Row::_8;
  }

  if (castleSide == CastleSide::kingSide) {
    assert(cells[Column::E][row] != nullptr);
    assert(cells[Column::E][row]->getName() == PieceName::king);
    assert(cells[Column::E][row]->getPlayerColor() == turn);
    assert(cells[Column::F][row] == nullptr);
    assert(cells[Column::G][row] == nullptr);
    assert(cells[Column::H][row] != nullptr);
    assert(cells[Column::H][row]->getName() == PieceName::rook);
    assert(cells[Column::H][row]->getPlayerColor() == turn);

    movePiece({Column::E, row}, {Column::G, row});
    movePiece({Column::H, row}, {Column::F, row});
  } else {
    assert(cells[Column::A][row] != nullptr);
    assert(cells[Column::A][row]->getName() == PieceName::rook);
    assert(cells[Column::A][row]->getPlayerColor() == turn);
    assert(cells[Column::C][row] == nullptr);
    assert(cells[Column::C][row] == nullptr);
    assert(cells[Column::D][row] == nullptr);
    assert(cells[Column::E][row] != nullptr);
    assert(cells[Column::E][row]->getName() == PieceName::king);
    assert(cells[Column::E][row]->getPlayerColor() == turn);

    movePiece({Column::E, row}, {Column::C, row});
    movePiece({Column::A, row}, {Column::D, row});
  }
}

void Board::drawOffer() const {
    // To be implemented, make some kind of notification on the side of the board
    const std::string str = std::format("{} offered a draw!", playerColorCStr(turn));
    std::cout << str.c_str() << std::endl;
}

// public:
Board::Board(const std::string &boardImagePath) {
  assert(!boardImagePath.empty());
  originalBoardImage = LoadImage(boardImagePath.c_str());
  ImageResize(&originalBoardImage, 8 * CELL_WIDTH + 2 * BOARD_PADDING_X,
              8 * CELL_HEIGHT + 2 * BOARD_PADDING_Y);
}

Board::~Board() {}

const std::string Board::getHistory() const { return history; }
const PlayerColor Board::getTurn() const { return turn; }
const bool Board::getGameDone() const { return gameDone; }
const PlayerColor Board::getGameEnd() const { return gameEnd; }
// should make this pick a random image from the pieces folder instead of
// hardcoding it
void Board::setPieces() {
  // white piece
  cells[Column::A][Row::_2] = std::make_unique<Pawn>(
      Column::A, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::B][Row::_2] = std::make_unique<Pawn>(
      Column::B, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::C][Row::_2] = std::make_unique<Pawn>(
      Column::C, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::D][Row::_2] = std::make_unique<Pawn>(
      Column::D, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::E][Row::_2] = std::make_unique<Pawn>(
      Column::E, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::F][Row::_2] = std::make_unique<Pawn>(
      Column::F, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::G][Row::_2] = std::make_unique<Pawn>(
      Column::G, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::H][Row::_2] = std::make_unique<Pawn>(
      Column::H, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));

  cells[Column::A][Row::_1] = std::make_unique<Rook>(
      Column::A, Row::_1, PlayerColor::white, std::format("{}/img/white/rook1.png", PROJECT_ROOT_DIR));
  cells[Column::B][Row::_1] = std::make_unique<Knight>(
      Column::B, Row::_1, PlayerColor::white, std::format("{}/img/white/knight1.png", PROJECT_ROOT_DIR));
  cells[Column::C][Row::_1] = std::make_unique<Bishop>(
      Column::C, Row::_1, PlayerColor::white, std::format("{}/img/white/bishop1.png", PROJECT_ROOT_DIR));
  cells[Column::D][Row::_1] = std::make_unique<Queen>(
      Column::D, Row::_1, PlayerColor::white, std::format("{}/img/white/queen1.png", PROJECT_ROOT_DIR));
  cells[Column::E][Row::_1] = std::make_unique<King>(
      Column::E, Row::_1, PlayerColor::white, std::format("{}/img/white/king1.png", PROJECT_ROOT_DIR));
  cells[Column::F][Row::_1] = std::make_unique<Bishop>(
      Column::F, Row::_1, PlayerColor::white, std::format("{}/img/white/bishop1.png", PROJECT_ROOT_DIR));
  cells[Column::G][Row::_1] = std::make_unique<Knight>(
      Column::G, Row::_1, PlayerColor::white, std::format("{}/img/white/knight1.png", PROJECT_ROOT_DIR));
  cells[Column::H][Row::_1] = std::make_unique<Rook>(
      Column::H, Row::_1, PlayerColor::white, std::format("{}/img/white/rook1.png", PROJECT_ROOT_DIR));

  // black pieces
  cells[Column::A][Row::_7] = std::make_unique<Pawn>(
      Column::A, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::B][Row::_7] = std::make_unique<Pawn>(
      Column::B, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::C][Row::_7] = std::make_unique<Pawn>(
      Column::C, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::D][Row::_7] = std::make_unique<Pawn>(
      Column::D, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::E][Row::_7] = std::make_unique<Pawn>(
      Column::E, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::F][Row::_7] = std::make_unique<Pawn>(
      Column::F, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::G][Row::_7] = std::make_unique<Pawn>(
      Column::G, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
  cells[Column::H][Row::_7] = std::make_unique<Pawn>(
      Column::H, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));

  cells[Column::A][Row::_8] = std::make_unique<Rook>(
      Column::A, Row::_8, PlayerColor::black, std::format("{}/img/black/rook1.png", PROJECT_ROOT_DIR));
  cells[Column::B][Row::_8] = std::make_unique<Knight>(
      Column::B, Row::_8, PlayerColor::black, std::format("{}/img/black/knight1.png", PROJECT_ROOT_DIR));
  cells[Column::C][Row::_8] = std::make_unique<Bishop>(
      Column::C, Row::_8, PlayerColor::black, std::format("{}/img/black/bishop1.png", PROJECT_ROOT_DIR));
  cells[Column::D][Row::_8] = std::make_unique<Queen>(
      Column::D, Row::_8, PlayerColor::black, std::format("{}/img/black/queen1.png", PROJECT_ROOT_DIR));
  cells[Column::E][Row::_8] = std::make_unique<King>(
      Column::E, Row::_8, PlayerColor::black, std::format("{}/img/black/king1.png", PROJECT_ROOT_DIR));
  cells[Column::F][Row::_8] = std::make_unique<Bishop>(
      Column::F, Row::_8, PlayerColor::black, std::format("{}/img/black/bishop1.png", PROJECT_ROOT_DIR));
  cells[Column::G][Row::_8] = std::make_unique<Knight>(
      Column::G, Row::_8, PlayerColor::black, std::format("{}/img/black/knight1.png", PROJECT_ROOT_DIR));
  cells[Column::H][Row::_8] = std::make_unique<Rook>(
      Column::H, Row::_8, PlayerColor::black, std::format("{}/img/black/rook1.png", PROJECT_ROOT_DIR));
}

void Board::removePiece(const Square& square) {
    cells[square.col][square.row] = nullptr;
}

const Square Board::findMove(const Move &move) {
    //looping through the whole board and finding which piece can move to move.to.
    //should use the attributes inside the move structs, specifically when the piece is known, and when the move results in a check
    //captures are only relevant for enpessant which is already covered in the doMove function.
    
    //TODO: implement function for each piece similar to the getMoves functions but which has move.to as input argument

  std::vector<Square> ret{};
  
  const Column colStart = (move.from.col == Column::none) ? Column::A : move.from.col;
  const Column colEnd = (move.from.col == Column::none) ? Column::H : move.from.col;
  
  const Row rowStart = (move.from.row == Row::none) ? Row::_1 : move.from.row;
  const Row rowEnd = (move.from.row == Row::none) ? Row::_8 : move.from.row;

  //starting with known piecename case:
  switch (move.piece) {
    case PieceName::pawn:
      for (Column col = colStart; col <= colEnd; ++col) {
        for (Row row = rowStart; row <= rowEnd; ++row) {
          auto& piece = cells[col][row];
          if (piece != nullptr && piece->getPlayerColor() == turn && piece->getName() == PieceName::pawn) {
            getPawnMoves(piece, ret);
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(piece->getSquare(), move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            ret.clear();
          }
        }
      }
      assert(0);
      break;
 
    case PieceName::rook:
      for (Column col = colStart; col <= colEnd; ++col) {
        for (Row row = rowStart; row <= rowEnd; ++row) {
          auto& piece = cells[col][row];
          if (piece != nullptr && piece->getPlayerColor() == turn && piece->getName() == PieceName::rook) {
            getRookMoves(piece, ret);
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(piece->getSquare(), move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            ret.clear();
          }
        }
      }
      assert(0);
      break;

    
    case PieceName::knight:
      for (Column col = colStart; col <= colEnd; ++col) {
        for (Row row = rowStart; row <= rowEnd; ++row) {
          auto& piece = cells[col][row];
          if (piece != nullptr && piece->getPlayerColor() == turn && piece->getName() == PieceName::knight) {
            getKnightMoves(piece, ret);
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(piece->getSquare(), move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            ret.clear();
          }
        }
      }
      assert(0);
      break;
      
    case PieceName::bishop:
      for (Column col = colStart; col <= colEnd; ++col) {
        for (Row row = rowStart; row <= rowEnd; ++row) {
          auto& piece = cells[col][row];
          if (piece != nullptr && piece->getPlayerColor() == turn && piece->getName() == PieceName::bishop) {
            getBishopMoves(piece, ret);
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(piece->getSquare(), move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            ret.clear();
          }
        }
      } 
      assert(0);
      break;

    case PieceName::queen:
      for (Column col = colStart; col <= colEnd; ++col) {
        for (Row row = rowStart; row <= rowEnd; ++row) {
          auto& piece = cells[col][row];
          if (piece != nullptr && piece->getPlayerColor() == turn && piece->getName() == PieceName::queen) {
            getQueenMoves(piece, ret);
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(piece->getSquare(), move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            ret.clear();
          }
        }
      }
      assert(0);
      break;

    case PieceName::king:
      for (Column col = colStart; col <= colEnd; ++col) {
        for (Row row = rowStart; row <= rowEnd; ++row) {
          auto& piece = cells[col][row];
          if (piece != nullptr && piece->getPlayerColor() == turn && piece->getName() == PieceName::king) {
            getKingMoves(piece, ret);
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(piece->getSquare(), move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            ret.clear();
          }
        }
      }
      assert(0);
      break;

    default:
      //Unknown piecename case:
      for (Column col = colStart; col <= colEnd; ++col) {
        for (Row row = rowStart; row <= rowEnd; ++row) {
            auto& piece = cells[col][row];
            if (piece == nullptr) continue;

            if (piece->getPlayerColor() == turn) {
              switch (piece->getName()) { 
                case PieceName::pawn:
                  getPawnMoves(piece, ret);
                  break;

                case PieceName::rook:
                  getRookMoves(piece, ret);
                  break;

                case PieceName::knight:
                  getKnightMoves(piece, ret);
                  break;

                case PieceName::bishop:
                  getBishopMoves(piece, ret);
                  break;

                 case PieceName::queen:
                  getQueenMoves(piece, ret);
                  break;

                case PieceName::king:
                  getKingMoves(piece, ret);
                  break;

                default:
                  assert(0);
                  break;

            }
              
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(piece->getSquare(), move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            ret.clear();
          }
        }
      }
  }
  assert(0);
  return Square{Column::none, Row::none};
}

void Board::movePiece(const Square& from, const Square& to) {
  assert(from.col >= Column::A && from.col <= Column::H);
  assert(from.row >= Row::_1 && from.row <= Row::_8);
  assert(to.col >= Column::A && to.col <= Column::H);
  assert(to.row >= Row::_1 && to.row <= Row::_8);

  auto& fromPiece = cells[from.col][from.row];
  auto& toPiece = cells[to.col][to.row];

  // making sure there is a piece at the from position.
  assert(fromPiece != nullptr);

  // checking whether the color of the from piece is different from the to
  // piece, if it exists.
  if (toPiece != nullptr) {
    assert(fromPiece->getPlayerColor() != toPiece->getPlayerColor());
  }

  // check if the move is a valid move for the piece.
  // check if the move is allowed according to the position, e.g. don't move
  // through pieces, dont check yourself etc.

  toPiece = std::move(fromPiece);
  toPiece->setCol(to.col);
  toPiece->setRow(to.row);


  return;
}

void Board::getMoves(const Column& col, const Row& row, std::vector<Square> &to) {
  auto& piece = cells[col][row];
  if (piece == nullptr) return;

  switch (piece->getName()) {
  case PieceName::pawn:
    getPawnMoves(piece, to);
    break;
  case PieceName::rook:
    getRookMoves(piece, to);
    break;
  case PieceName::knight:
    getKnightMoves(piece, to);
    break;
  case PieceName::bishop:
    getBishopMoves(piece, to);
    break;
  case PieceName::queen:
    getQueenMoves(piece, to);
    break;
  case PieceName::king:
    getKingMoves(piece, to);
    break;
  default:
    assert(0);
  }
}

void Board::getPawnMoves(const std::unique_ptr<Piece> &piece,
                         std::vector<Square> &to) {
  assert(to.empty());
  assert(piece != nullptr);
  assert(piece->getPlayerColor() == PlayerColor::white ||
         piece->getPlayerColor() == PlayerColor::black);

  const Column col = piece->getCol();
  const Row row = piece->getRow();
  const PlayerColor color = piece->getPlayerColor();
  const int8_t colorDiff = (color == PlayerColor::white) ? 1 : -1;

  // simple move
  if (cells[col][row + colorDiff] == nullptr) {
    to.emplace_back(col, row + colorDiff);
    // double first move
    if ((color == PlayerColor::white && row == Row::_2) ||
        (color == PlayerColor::black && row == Row::_7)) {
      if (cells[col][row + colorDiff] == nullptr)
        to.emplace_back(col, row + (int8_t)(2 * colorDiff));
    }
  }
  // captures
  if (col != Column::A) {
      auto& capturePiece = cells[col - 1][row + colorDiff];
      if (capturePiece != nullptr && capturePiece->getPlayerColor() != color) {
          to.emplace_back(col - 1, row + colorDiff);
      }
  }
  
  if (col != Column::H) {
      auto& capturePiece = cells[col + 1][row + colorDiff];
      if (capturePiece != nullptr && capturePiece->getPlayerColor() != color) {
          to.emplace_back(col + 1, row + colorDiff);
      }
  }
}

void Board::getRookMoves(const std::unique_ptr<Piece> &piece,
                         std::vector<Square> &to) {
  assert(to.empty());
  assert(piece != nullptr);
  assert(piece->getPlayerColor() == PlayerColor::white ||
         piece->getPlayerColor() == PlayerColor::black);

  Column col = piece->getCol();
  Row row = piece->getRow();
  const PlayerColor color = piece->getPlayerColor();

  do {
    ++col;
    if (col > Column::H)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(col, row);
    }

  } while (cells[col][row] == nullptr);

  col = piece->getCol();
  
  do {
    --col;
    if (col < Column::A)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(col, row);
    }

  } while (cells[col][row] == nullptr);

  col = piece->getCol();

  do {
    ++row;
    if (row > Row::_8)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(col, row);
    }

  } while (cells[col][row] == nullptr);

  row = piece->getRow();

  do {
    --row;
    if (row < Row::_1)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(col, row);
    }

  } while (cells[col][row] == nullptr);
}

void Board::getKnightMoves(const std::unique_ptr<Piece> &piece,
                           std::vector<Square> &to) {
  assert(to.empty());
  assert(piece != nullptr);
  assert(piece->getPlayerColor() == PlayerColor::white ||
         piece->getPlayerColor() == PlayerColor::black);

  const Column col = piece->getCol();
  const Row row = piece->getRow();
  const PlayerColor color = piece->getPlayerColor();

  for (const int8_t &colDiff : {(int8_t)-2, (int8_t)2}) {
    for (const int8_t &rowDiff : {(int8_t)-1, (int8_t)1}) {
      if (col + colDiff >= Column::A && col + colDiff <= Column::H &&
          row + rowDiff >= Row::_1 && row + rowDiff <= Row::_8) {
        if (cells[col + colDiff][row + rowDiff] == nullptr ||
            cells[col + colDiff][row + rowDiff]->getPlayerColor() != color) {
          to.emplace_back(col + colDiff, row + rowDiff);
        }
      }
    }
  }

  for (const int8_t &rowDiff : {(int8_t)-2, (int8_t)2}) {
    for (const int8_t &colDiff : {(int8_t)-1, (int8_t)1}) {
      if (col + colDiff >= Column::A && col + colDiff <= Column::H &&
          row + rowDiff >= Row::_1 && row + rowDiff <= Row::_8) {
        if (cells[col + colDiff][row + rowDiff] == nullptr ||
            cells[col + colDiff][row + rowDiff]->getPlayerColor() != color) {
          to.emplace_back(col + colDiff, row + rowDiff);
        }
      }
    }
  }
}

void Board::getBishopMoves(const std::unique_ptr<Piece> &piece,
                           std::vector<Square> &to) {
  assert(to.empty());
  assert(piece != nullptr);
  assert(piece->getPlayerColor() == PlayerColor::white ||
         piece->getPlayerColor() == PlayerColor::black);

  const PlayerColor color = piece->getPlayerColor();

  // not the most beautifull implementation, but it works
  for (const int8_t &colDiff : {(int8_t)-1, (int8_t)1}) {
    for (const int8_t &rowDiff : {(int8_t)-1, (int8_t)1}) {
      Column col = piece->getCol();
      Row row = piece->getRow();

      while (1) {
        col += colDiff;
        row += rowDiff;
        if (col >= Column::A && col <= Column::H && row >= Row::_1 &&
            row <= Row::_8) {
          if (cells[col][row] == nullptr) {
            to.emplace_back(col, row);
          } else {
            if (cells[col][row]->getPlayerColor() != color) {
              to.emplace_back(col, row);
            }
            break;
          }
        } else {
          break;
        }
      }
    }
  }
}

void Board::getQueenMoves(const std::unique_ptr<Piece> &piece,
                          std::vector<Square> &to) {
  assert(to.empty());
  assert(piece != nullptr);
  assert(piece->getPlayerColor() == PlayerColor::white ||
         piece->getPlayerColor() == PlayerColor::black);

  // same as rook
  Column col = piece->getCol();
  Row row = piece->getRow();
  const PlayerColor color = piece->getPlayerColor();

  do {
    ++col;
    if (col > Column::H)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(col, row);
    }

  } while (cells[col][row] == nullptr);

  col = piece->getCol();

  do {
    --col;
    if (col < Column::A)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(col, row);
    }

  } while (cells[col][row] == nullptr);
  
  col = piece->getCol();

  do {
    ++row;
    if (row > Row::_8)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(col, row);
    }

  } while (cells[col][row] == nullptr);

  row = piece->getRow();
  
  do {
    --row;
    if (row < Row::_1)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(col, row);
    }

  } while (cells[col][row] == nullptr);

  // same as bishop
  for (const int8_t &colDiff : {(int8_t)-1, (int8_t)1}) {
    for (const int8_t &rowDiff : {(int8_t)-1, (int8_t)1}) {
      col = piece->getCol();
      row = piece->getRow();

      while (1) {
        col += colDiff;
        row += rowDiff;
        if (col >= Column::A && col <= Column::H && row >= Row::_1 &&
            row <= Row::_8) {
          if (cells[col][row] == nullptr) {
            to.emplace_back(col, row);
          } else {
            if (cells[col][row]->getPlayerColor() != color) {
              to.emplace_back(col, row);
            }
            break;
          }
        } else {
          break;
        }
      }
    }
  }
}

void Board::getKingMoves(const std::unique_ptr<Piece> &piece,
                         std::vector<Square> &to) {
  assert(to.empty());
  assert(piece != nullptr);
  assert(piece->getPlayerColor() == PlayerColor::white ||
         piece->getPlayerColor() == PlayerColor::black);

  const Column col = piece->getCol();
  const Row row = piece->getRow();
  const PlayerColor color = piece->getPlayerColor();

  for (const int8_t &colDiff : {(int8_t)-1, (int8_t)0, (int8_t)1}) {
    for (const int8_t &rowDiff : {(int8_t)-1, (int8_t)0, (int8_t)1}) {
      if (colDiff == 0 && rowDiff == 0)
        continue;
      if (col + colDiff >= Column::A && col + colDiff <= Column::H &&
          row + rowDiff >= Row::_1 && row + rowDiff <= Row::_8) {
        if (cells[col + colDiff][row + rowDiff] == nullptr ||
            cells[col + colDiff][row + rowDiff]->getPlayerColor() != color)
          to.emplace_back(col + colDiff, row + rowDiff);
      }
    }
  }
}

void Board::doMove(const Move &move) {
  std::cout << "Attempting to do move : piece = " << move.piece;
  std::cout << ", From col = " << move.from.col << ", row = " << move.from.row;
  std::cout << ", To col = " << move.to.col << ", row = " << move.to.row << std::endl;
  // if the from square is given, the to square is also always given. else they
  // should be defined as none
  if (move.from.col >= Column::A && move.from.col <= Column::H &&
      move.from.row >= Row::_1 && move.from.row <= Row::_8) {
    movePiece(move.from, move.to);
    toggleTurn();
    return;
  }

  if (move.enPassant) {
    Square from, to = {};
    from.col = move.from.col;
    from.row = (move.to.row == Row::_3) ? Row::_4 : Row::_5;

    to.col = move.to.col;
    to.row = move.to.row;

    removePiece(Square{to.col, from.row});
    movePiece(from, to);
    toggleTurn();
    return;
  }

  if (move.promotion) {
    assert(move.promotionPiece != PieceName::none);
    transformPiece(move.from, move.promotionPiece);

    Square from, to = {};
    from.col = move.to.col;
    from.row = (move.to.row == Row::_1) ? Row::_2 : Row::_7;
    to = move.to;
    movePiece(from, to);
    toggleTurn();
    return;
  }

  if (move.castle) {
    assert(move.castleSide != CastleSide::none);
    castle(move.castleSide);
    toggleTurn();
    return;
  }

  if (move.endOfGame) {
    assert(move.end != End::none);
    endGame(move.end);
    return;
  }

  if (move.drawOffer) {
    drawOffer();
    return;
  }

  //base case 
  const Square from = findMove(move);
  movePiece(from, move.to);
  toggleTurn();
  return;
}

const bool Board::moveIsCheck(const Square& from, const Square& to) {
    std::unique_ptr<Piece> tempPiece{};
    if (cells[to.col][to.row] != nullptr) tempPiece = std::move(cells[to.col][to.row]);
    // cells[to.col][to.row] = std::move(cells[from.col][from.row]);
    movePiece(from, to);

    Square king{};
    for (Column col = Column::A; col <= Column::H; ++col) {
        for (Row row = Row::_1; row <= Row::_8; ++row) {
            auto& piece = cells[col][row];
            if (piece != nullptr && piece->getName() == PieceName::king && piece->getPlayerColor() != turn) {
                king = Square{col, row};
            }
        }
    } 
    assert (king.col != Column::none && king.row != Row::none);

    std::vector<Square> ret{};
    for (Column col = Column::A; col <= Column::H; ++col) {
        for (Row row = Row::_1; row <= Row::_8; ++row) {
            auto& piece = cells[col][row];
            if (piece == nullptr) continue;
            if (piece->getPlayerColor() != turn) continue;
            
            switch(piece->getName()) {
                case PieceName::pawn:
                getPawnMoves(piece, ret);
                break;

                case PieceName::rook:
                getRookMoves(piece, ret);
                break;

                case PieceName::knight:
                getKnightMoves(piece, ret);
                break;

                case PieceName::bishop:
                getBishopMoves(piece, ret);
                break;

                case PieceName::queen:
                getQueenMoves(piece, ret);
                break;

                case PieceName::king:
                getKingMoves(piece, ret);
                break;

                default:
                assert(0);
            }

            for (auto& e : ret) {
                if (e == king) {
                    movePiece(to, from);
                    if (tempPiece != nullptr) cells[to.col][to.row] = std::move(tempPiece);
                    return true;
                }
            }
            ret.clear();
        }
    }


    //cells[from.col][from.row] = std::move(cells[to.col][to.row]);
    movePiece(to, from);
    if (tempPiece != nullptr) cells[to.col][to.row] = std::move(tempPiece);
    return false;
}
