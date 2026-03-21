#include <memory>
#include <iostream>
#include <utility>
#include <vector>

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

const PieceName Piece::getName() { return name; }
void Piece::setName(const PieceName &name) { this->name = name; }

const Row Piece::getRow() { return row; }
void Piece::setRow(const Row &row) { this->row = row; }

const Column Piece::getCol() { return col; }
void Piece::setCol(const Column &col) { this->col = col; }

const PlayerColor Piece::getPlayerColor() { return player; }

const Image &Piece::getImage() { return image; }
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
void Board::endGame(End end) {
  switch (end) {
  case End::whiteWins:
    std::cout << "White wins!" << std::endl;
    break;

  case End::blackWins:
    std::cout << "Black wins!" << std::endl;
    break;

  case End::draw:
    std::cout << "Draw!" << std::endl;
    break;

  default:
    std::cout << "Undefined end" << std::endl;
    break;
  }
}

void Board::transformPiece(Square square, PieceName pieceName) {
  switch (pieceName) {
  case PieceName::bishop:
    cells[square.col][square.row] = std::make_unique<Bishop>(
        square.col, square.row, turn,
        std::format("../../img/{}/bishop1.png", playerColorCStr(turn)));
    break;

  case PieceName::knight:
    cells[square.col][square.row] = std::make_unique<Knight>(
        square.col, square.row, turn,
        std::format("../../img/{}/knight1.png", playerColorCStr(turn)));
    break;

  case PieceName::rook:
    cells[square.col][square.row] = std::make_unique<Rook>(
        square.col, square.row, turn,
        std::format("../../img/{}/rook.png", playerColorCStr(turn)));
    break;

  case PieceName::queen:
    cells[square.col][square.row] = std::make_unique<Queen>(
        square.col, square.row, turn,
        std::format("../../img/{}/queen.png", playerColorCStr(turn)));
    break;
  default:
    assert(0);
  }
}

void Board::castle(CastleSide castleSide) {
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
    assert(cells[Column::E][row]->getName() == PieceName::king);
    assert(cells[Column::F][row] == nullptr);
    assert(cells[Column::G][row] == nullptr);
    assert(cells[Column::H][row]->getName() == PieceName::rook);

    cells[Column::F][row] = std::move(cells[Column::E][row]);
    cells[Column::G][row] = std::move(cells[Column::H][row]);
  } else {
    assert(cells[Column::A][row]->getName() == PieceName::rook);
    assert(cells[Column::C][row] == nullptr);
    assert(cells[Column::C][row] == nullptr);
    assert(cells[Column::D][row] == nullptr);
    assert(cells[Column::E][row]->getName() == PieceName::king);

    cells[Column::C][row] = std::move(cells[Column::E][row]);
    cells[Column::D][row] = std::move(cells[Column::A][row]);
  }
}

void Board::drawOffer() {
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

const std::string Board::getHistory() { return history; }
const PlayerColor Board::getTurn() { return turn; }

// should make this pick a random image from the pieces folder instead of
// hardcoding it
void Board::setPieces() {
  // white piece
  cells[Column::A][Row::_2] = std::make_unique<Pawn>(
      Column::A, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
  cells[Column::B][Row::_2] = std::make_unique<Pawn>(
      Column::B, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
  cells[Column::C][Row::_2] = std::make_unique<Pawn>(
      Column::C, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
  cells[Column::D][Row::_2] = std::make_unique<Pawn>(
      Column::D, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
  cells[Column::E][Row::_2] = std::make_unique<Pawn>(
      Column::E, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
  cells[Column::F][Row::_2] = std::make_unique<Pawn>(
      Column::F, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
  cells[Column::G][Row::_2] = std::make_unique<Pawn>(
      Column::G, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");
  cells[Column::H][Row::_2] = std::make_unique<Pawn>(
      Column::H, Row::_2, PlayerColor::white, "../../img/white/pawn1.png");

  cells[Column::A][Row::_1] = std::make_unique<Rook>(
      Column::A, Row::_1, PlayerColor::white, "../../img/white/rook1.png");
  cells[Column::B][Row::_1] = std::make_unique<Knight>(
      Column::B, Row::_1, PlayerColor::white, "../../img/white/knight1.png");
  cells[Column::C][Row::_1] = std::make_unique<Bishop>(
      Column::C, Row::_1, PlayerColor::white, "../../img/white/bishop1.png");
  cells[Column::D][Row::_1] = std::make_unique<Queen>(
      Column::D, Row::_1, PlayerColor::white, "../../img/white/queen1.png");
  cells[Column::E][Row::_1] = std::make_unique<King>(
      Column::E, Row::_1, PlayerColor::white, "../../img/white/king1.png");
  cells[Column::F][Row::_1] = std::make_unique<Bishop>(
      Column::F, Row::_1, PlayerColor::white, "../../img/white/bishop1.png");
  cells[Column::G][Row::_1] = std::make_unique<Knight>(
      Column::G, Row::_1, PlayerColor::white, "../../img/white/knight1.png");
  cells[Column::H][Row::_1] = std::make_unique<Rook>(
      Column::H, Row::_1, PlayerColor::white, "../../img/white/rook1.png");

  // black pieces
  cells[Column::A][Row::_7] = std::make_unique<Pawn>(
      Column::A, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
  cells[Column::B][Row::_7] = std::make_unique<Pawn>(
      Column::B, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
  cells[Column::C][Row::_7] = std::make_unique<Pawn>(
      Column::C, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
  cells[Column::D][Row::_7] = std::make_unique<Pawn>(
      Column::D, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
  cells[Column::E][Row::_7] = std::make_unique<Pawn>(
      Column::E, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
  cells[Column::F][Row::_7] = std::make_unique<Pawn>(
      Column::F, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
  cells[Column::G][Row::_7] = std::make_unique<Pawn>(
      Column::G, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");
  cells[Column::H][Row::_7] = std::make_unique<Pawn>(
      Column::H, Row::_7, PlayerColor::black, "../../img/black/pawn1.png");

  cells[Column::A][Row::_8] = std::make_unique<Rook>(
      Column::A, Row::_8, PlayerColor::black, "../../img/black/rook1.png");
  cells[Column::B][Row::_8] = std::make_unique<Knight>(
      Column::B, Row::_8, PlayerColor::black, "../../img/black/knight1.png");
  cells[Column::C][Row::_8] = std::make_unique<Bishop>(
      Column::C, Row::_8, PlayerColor::black, "../../img/black/bishop1.png");
  cells[Column::D][Row::_8] = std::make_unique<Queen>(
      Column::D, Row::_8, PlayerColor::black, "../../img/black/queen1.png");
  cells[Column::E][Row::_8] = std::make_unique<King>(
      Column::E, Row::_8, PlayerColor::black, "../../img/black/king1.png");
  cells[Column::F][Row::_8] = std::make_unique<Bishop>(
      Column::F, Row::_8, PlayerColor::black, "../../img/black/bishop1.png");
  cells[Column::G][Row::_8] = std::make_unique<Knight>(
      Column::G, Row::_8, PlayerColor::black, "../../img/black/knight1.png");
  cells[Column::H][Row::_8] = std::make_unique<Rook>(
      Column::H, Row::_8, PlayerColor::black, "../../img/black/rook1.png");
}

const Square Board::findMove(const Move &move) {
    //looping through the whole board and finding which piece can move to move.to.
    //should use the attributes inside the move structs, specifically when the piece is known, and when the move results in a check
    //captures are only relevant for enpessant which is already covered in the doMove function.
    
    //TODO: implement function for each piece similar to the getMoves functions but which has move.to as input argument

  std::vector<Square> ret{};
  
  //starting with known piecename case:
  switch (move.piece) {
    case PieceName::pawn:
      for (Column col = Column::A; col <= Column::H; ++col) {
        for (Row row = Row::_1; row <= Row::_8; ++row) {
          std::unique_ptr<Piece>& piece = cells[col][row];
          if (piece->getPlayerColor() == turn && piece->getName() == PieceName::pawn) {
            getPawnMoves(piece, ret);
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(entry, move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            assert(0);
          }
        }
      }
      break;
 
    case PieceName::rook:
      for (Column col = Column::A; col <= Column::H; ++col) {
        for (Row row = Row::_1; row <= Row::_8; ++row) {
          std::unique_ptr<Piece>& piece = cells[col][row];
          if (piece->getPlayerColor() == turn && piece->getName() == PieceName::rook) {
            getRookMoves(piece, ret);
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(entry, move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            assert(0);
          }
        }
      }
      break;
    
    case PieceName::knight:
      for (Column col = Column::A; col <= Column::H; ++col) {
        for (Row row = Row::_1; row <= Row::_8; ++row) {
          std::unique_ptr<Piece>& piece = cells[col][row];
          if (piece->getPlayerColor() == turn && piece->getName() == PieceName::knight) {
            getKnightMoves(piece, ret);
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(entry, move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            assert(0);
          }
        }
      }
      break;
      
     case PieceName::bishop:
      for (Column col = Column::A; col <= Column::H; ++col) {
        for (Row row = Row::_1; row <= Row::_8; ++row) {
          std::unique_ptr<Piece>& piece = cells[col][row];
          if (piece->getPlayerColor() == turn && piece->getName() == PieceName::bishop) {
            getBishopMoves(piece, ret);
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(entry, move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            assert(0);
          }
        }
      } 
      break;

    case PieceName::queen:
      for (Column col = Column::A; col <= Column::H; ++col) {
        for (Row row = Row::_1; row <= Row::_8; ++row) {
          std::unique_ptr<Piece>& piece = cells[col][row];
          if (piece->getPlayerColor() == turn && piece->getName() == PieceName::queen) {
            getQueenMoves(piece, ret);
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(entry, move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            assert(0);
          }
        }
      }
      break;

    case PieceName::king:
      for (Column col = Column::A; col <= Column::H; ++col) {
        for (Row row = Row::_1; row <= Row::_8; ++row) {
          std::unique_ptr<Piece>& piece = cells[col][row];
          if (piece->getPlayerColor() == turn && piece->getName() == PieceName::king) {
            getKingMoves(piece, ret);
            for (auto& entry : ret) {
                if (entry == move.to) {
                    if (move.check) {
                        if(moveIsCheck(entry, move.to)) {
                            return Square{col, row};
                        }
                    } else {
                        return Square{col, row};
                    }
                }
            }
            assert(0);
          }
        }
      }
      break;

    default:
      //Unknown piecename case:
      for (Column col = Column::A; col <= Column::H; ++col) {
          for (Row row = Row::_1; row <= Row::_8; ++row) {
            std::unique_ptr<Piece>& piece = cells[col][row];
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
                        if(moveIsCheck(entry, move.to)) {
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

void Board::movePiece(const Square from, const Square to) {
  assert(from.col >= Column::A && from.col <= Column::H);
  assert(from.row >= Row::_1 && from.row <= Row::_8);
  assert(to.col >= Column::A && to.col <= Column::H);
  assert(to.row >= Row::_1 && to.row <= Row::_8);

  std::unique_ptr<Piece> &fromPiece = cells[from.col][from.row];
  std::unique_ptr<Piece> &toPiece = cells[to.col][to.row];

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

void Board::getMoves(const Column col, const Row row, std::vector<Square> &to) {
  std::unique_ptr<Piece> &piece = cells[col][row];
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

void Board::getPawnMoves(std::unique_ptr<Piece> &piece,
                         std::vector<Square> &to) {
  assert(to.empty());
  assert(piece != nullptr);
  assert(piece->getPlayerColor() == PlayerColor::white ||
         piece->getPlayerColor() == PlayerColor::black);

  Column col = piece->getCol();
  Row row = piece->getRow();
  PlayerColor color = piece->getPlayerColor();
  int8_t colorDiff;

  colorDiff = 1 ? color == PlayerColor::white : colorDiff = -1;

  // simple move
  if (cells[col][row + colorDiff] == nullptr) {
    to.emplace_back(Square{col, row + colorDiff});
    // double first move
    if ((color == PlayerColor::white && row == Row::_2) ||
        (color == PlayerColor::black && row == Row::_7)) {
      if (cells[col][row + colorDiff] == nullptr)
        to.emplace_back(Square{col, row + (int8_t)(2 * colorDiff)});
    }
  }
  // captures
  if (col != Column::A &&
      cells[col - (int8_t)1][row + colorDiff]->getPlayerColor() != color)
    to.emplace_back(Square{col - 1, row + colorDiff});
  if (col != Column::H &&
      cells[col + 1][row + colorDiff]->getPlayerColor() != color)
    to.emplace_back(Square{col + 1, row + colorDiff});
}

void Board::getRookMoves(std::unique_ptr<Piece> &piece,
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
      to.emplace_back(Square{col, row});
    }

  } while (cells[col][row] == nullptr);

  col = piece->getCol();
  ;
  do {
    --col;
    if (col < Column::A)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(Square{col, row});
    }

  } while (cells[col][row] == nullptr);

  do {
    ++row;
    if (row > Row::_8)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(Square{col, row});
    }

  } while (cells[col][row] == nullptr);

  row = piece->getRow();
  do {
    --row;
    if (row < Row::_1)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(Square{col, row});
    }

  } while (cells[col][row] == nullptr);
}

void Board::getKnightMoves(std::unique_ptr<Piece> &piece,
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

void Board::getBishopMoves(std::unique_ptr<Piece> &piece,
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

void Board::getQueenMoves(std::unique_ptr<Piece> &piece,
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
      to.emplace_back(Square{col, row});
    }

  } while (cells[col][row] == nullptr);

  col = piece->getCol();
  ;
  do {
    --col;
    if (col < Column::A)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(Square{col, row});
    }

  } while (cells[col][row] == nullptr);

  do {
    ++row;
    if (row > Row::_8)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(Square{col, row});
    }

  } while (cells[col][row] == nullptr);

  row = piece->getRow();
  do {
    --row;
    if (row < Row::_1)
      break;
    if (cells[col][row] == nullptr ||
        cells[col][row]->getPlayerColor() != color) {
      to.emplace_back(Square{col, row});
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

void Board::getKingMoves(std::unique_ptr<Piece> &piece,
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
  check = move.check;

  // if the from square is given, the to square is also always given. else they
  // should be defined as none
  if (move.from.col >= Column::A && move.from.col <= Column::H &&
      move.from.row >= Row::_1 && move.from.row <= Row::_8) {
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

  if (move.drawOffer) {
    drawOffer();
    return;
  }

  //base case 
  const Square from = findMove(move);
  movePiece(from, move.to);

  return;
}

bool Board::moveIsCheck(const Square from, const Square to) {
    std::unique_ptr<Piece> tempPiece{};
    if (cells[to.col][to.row] != nullptr) tempPiece = std::move(cells[to.col][to.row]);

    Square king{};
    for (Column col = Column::A; col <= Column::H; ++col) {
        for (Row row = Row::_1; row <= Row::_8; ++row) {
            
            if (cells[col][row]->getName() == PieceName::king && cells[col][row]->getPlayerColor() != turn) {
                king = Square{col, row};
            }
        }
    } 


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
                if (e == king) return true;
            }
        }
    }

    if (tempPiece != nullptr) cells[to.col][to.row] = std::move(tempPiece);
    return false;
}
