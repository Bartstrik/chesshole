
#include <format>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "cassert"
#include "chess.hpp"
#include "common.hpp"
#include "lexer.hpp"
// Piece Class
Piece::Piece(const PieceName &name, const Column &col, const Row &row, const PlayerColor &player, const std::string &imagePath) {
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
void Piece::setSquare(const Square &sq) {
	this->col = sq.col;
	this->row = sq.row;
}

const PlayerColor Piece::getPlayerColor() const { return player; }

const Image &Piece::getImage() const { return image; }
void Piece::setImage(const std::string &imagePath) {
	assert(!imagePath.empty());
	image = LoadImage(imagePath.c_str());
	ImageResize(&image, PIECE_WIDTH, PIECE_HEIGHT);
}

// Pawn Class
Pawn::Pawn(const Column &col, const Row &row, const PlayerColor &player, const std::string &imagePath)
	: Piece(PieceName::pawn, col, row, player, imagePath) {}

Pawn::~Pawn() {}

// Rook Class
Rook::Rook(const Column &col, const Row &row, const PlayerColor &player, const std::string &imagePath)
	: Piece(PieceName::rook, col, row, player, imagePath) {}

Rook::~Rook() {}

// Knight Class
Knight::Knight(const Column &col, const Row &row, const PlayerColor &player, const std::string &imagePath)
	: Piece(PieceName::knight, col, row, player, imagePath) {}

Knight::~Knight() {}

// Bishop Class
Bishop::Bishop(const Column &col, const Row &row, const PlayerColor &player, const std::string &imagePath)
	: Piece(PieceName::bishop, col, row, player, imagePath) {}

Bishop::~Bishop() {}

// Queen Class
Queen::Queen(const Column &col, const Row &row, const PlayerColor &player, const std::string &imagePath)
	: Piece(PieceName::queen, col, row, player, imagePath) {}

Queen::~Queen() {}

// King Class
King::King(const Column &col, const Row &row, const PlayerColor &player, const std::string &imagePath)
	: Piece(PieceName::king, col, row, player, imagePath) {}

King::~King() {}

// Board Class
// private:
void Board::toggleTurn() { turn = (turn == PlayerColor::black) ? PlayerColor::white : PlayerColor::black; }

void Board::endGame(const End &end) {
	gameEnd = end;
	switch (end) {
	case End::whiteWins:
		std::cout << "White wins!" << std::endl;
		return;

	case End::blackWins:
		std::cout << "Black wins!" << std::endl;
		return;

	case End::draw:
		std::cout << "Draw!" << std::endl;
		return;

	// Used for stepping back
	case End::none:
		std::cout << "Game unEnded ?!" << std::endl;
		return;

	default:
		std::cout << "Undefined end" << std::endl;
		return;
	}
}

void Board::transformPiece(const Square &square, const PieceName &pieceName) {
	switch (pieceName) {
	case PieceName::rook:
		cells[square.col][square.row] = std::make_unique<Rook>(
			square.col, square.row, turn, std::format("{}/img/{}/rook1.png", PROJECT_ROOT_DIR, playerColorCStr(turn)));
		return;

	case PieceName::knight:
		cells[square.col][square.row] = std::make_unique<Knight>(
			square.col, square.row, turn, std::format("{}/img/{}/knight1.png", PROJECT_ROOT_DIR, playerColorCStr(turn)));
		return;

	case PieceName::bishop:
		cells[square.col][square.row] = std::make_unique<Bishop>(
			square.col, square.row, turn, std::format("{}/img/{}/bishop1.png", PROJECT_ROOT_DIR, playerColorCStr(turn)));
		return;

	case PieceName::queen:
		cells[square.col][square.row] = std::make_unique<Queen>(
			square.col, square.row, turn, std::format("{}/img/{}/queen1.png", PROJECT_ROOT_DIR, playerColorCStr(turn)));
		return;

	case PieceName::king:
		cells[square.col][square.row] = std::make_unique<King>(
			square.col, square.row, turn, std::format("{}/img/{}/king1.png", PROJECT_ROOT_DIR, playerColorCStr(turn)));
		return;

	case PieceName::pawn:
		cells[square.col][square.row] = std::make_unique<Pawn>(
			square.col, square.row, turn, std::format("{}/img/{}/pawn1.png", PROJECT_ROOT_DIR, playerColorCStr(turn)));
		return;

	default:
		assert(0);
	}
}

void Board::castle(const CastleSide &castleSide) {
	assert(castleSide == CastleSide::kingSide || castleSide == CastleSide::queenSide);

	const Row row = (turn == PlayerColor::white) ? Row::_1 : Row::_8;

	switch (turn) {
		case PlayerColor::white:
		if (castleSide == CastleSide::kingSide) whiteCanCastleKingside = false;
		if (castleSide == CastleSide::queenSide) whiteCanCastleQueenside = false;
		break;

		case PlayerColor::black:
		if (castleSide == CastleSide::kingSide) blackCanCastleKingside = false;
		if (castleSide == CastleSide::queenSide) blackCanCastleQueenside = false;
		break;

		default:
		break;
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
		assert(cells[Column::B][row] == nullptr);
		assert(cells[Column::C][row] == nullptr);
		assert(cells[Column::D][row] == nullptr);
		assert(cells[Column::E][row] != nullptr);
		assert(cells[Column::E][row]->getName() == PieceName::king);
		assert(cells[Column::E][row]->getPlayerColor() == turn);

		movePiece({Column::E, row}, {Column::C, row});
		movePiece({Column::A, row}, {Column::D, row});
	}
}

void Board::unCastle(const CastleSide &castleSide) {
	assert(castleSide == CastleSide::kingSide || castleSide == CastleSide::queenSide);

	switch (turn) {
		case PlayerColor::white:
		if (castleSide == CastleSide::kingSide) whiteCanCastleKingside = true;
		if (castleSide == CastleSide::queenSide) whiteCanCastleQueenside = true;
		break;

		case PlayerColor::black:
		if (castleSide == CastleSide::kingSide) blackCanCastleKingside = true;
		if (castleSide == CastleSide::queenSide) blackCanCastleQueenside = true;
		break;

		default:
		break;
	}

	const Row row = (turn == PlayerColor::white) ? Row::_1 : Row::_8;

	if (castleSide == CastleSide::kingSide) {
		assert(cells[Column::E][row] == nullptr);
		assert(cells[Column::F][row] != nullptr);
		assert(cells[Column::F][row]->getName() == PieceName::rook);
		assert(cells[Column::F][row]->getPlayerColor() == turn);
		assert(cells[Column::G][row] != nullptr);
		assert(cells[Column::G][row]->getName() == PieceName::king);
		assert(cells[Column::G][row]->getPlayerColor() == turn);
		assert(cells[Column::H][row] == nullptr);

		movePiece({Column::G, row}, {Column::E, row});
		movePiece({Column::F, row}, {Column::H, row});
	} else {
		assert(cells[Column::A][row] == nullptr);
		assert(cells[Column::B][row] == nullptr);
		assert(cells[Column::C][row] != nullptr);
		assert(cells[Column::C][row]->getName() == PieceName::king);
		assert(cells[Column::C][row]->getPlayerColor() == turn);
		assert(cells[Column::D][row] != nullptr);
		assert(cells[Column::D][row]->getName() == PieceName::rook);
		assert(cells[Column::D][row]->getPlayerColor() == turn);
		assert(cells[Column::E][row] == nullptr);

		movePiece({Column::C, row}, {Column::E, row});
		movePiece({Column::D, row}, {Column::A, row});
	}
}

void Board::drawOffer() const {
	// To be implemented, make some kind of notification on the side of the
	// board
	const std::string str = std::format("{} offered a draw!", playerColorCStr(turn));
	std::cout << str.c_str() << std::endl;
}

// public:
Board::Board(const std::string &boardImagePath) {
	assert(!boardImagePath.empty());
	originalBoardImage = LoadImage(boardImagePath.c_str());
	ImageResize(&originalBoardImage, 8 * CELL_WIDTH + 2 * BOARD_PADDING_X, 8 * CELL_HEIGHT + 2 * BOARD_PADDING_Y);
}

Board::~Board() {}

const std::vector<Move> Board::getGame() const { return game; }

void Board::setGame(std::initializer_list<Move> iList) {
	game.assign(iList);
}

const PlayerColor Board::getTurn() const { return turn; }
const End Board::getGameEnd() const { return gameEnd; }
// should make this pick a random image from the pieces folder instead of
// hardcoding it
void Board::setPieces() {
	// white piece
	cells[Column::A][Row::_2] =
		std::make_unique<Pawn>(Column::A, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::B][Row::_2] =
		std::make_unique<Pawn>(Column::B, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::C][Row::_2] =
		std::make_unique<Pawn>(Column::C, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::D][Row::_2] =
		std::make_unique<Pawn>(Column::D, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::E][Row::_2] =
		std::make_unique<Pawn>(Column::E, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::F][Row::_2] =
		std::make_unique<Pawn>(Column::F, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::G][Row::_2] =
		std::make_unique<Pawn>(Column::G, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::H][Row::_2] =
		std::make_unique<Pawn>(Column::H, Row::_2, PlayerColor::white, std::format("{}/img/white/pawn1.png", PROJECT_ROOT_DIR));

	cells[Column::A][Row::_1] =
		std::make_unique<Rook>(Column::A, Row::_1, PlayerColor::white, std::format("{}/img/white/rook1.png", PROJECT_ROOT_DIR));
	cells[Column::B][Row::_1] = std::make_unique<Knight>(Column::B, Row::_1, PlayerColor::white,
														 std::format("{}/img/white/knight1.png", PROJECT_ROOT_DIR));
	cells[Column::C][Row::_1] = std::make_unique<Bishop>(Column::C, Row::_1, PlayerColor::white,
														 std::format("{}/img/white/bishop1.png", PROJECT_ROOT_DIR));
	cells[Column::D][Row::_1] =
		std::make_unique<Queen>(Column::D, Row::_1, PlayerColor::white, std::format("{}/img/white/queen1.png", PROJECT_ROOT_DIR));
	cells[Column::E][Row::_1] =
		std::make_unique<King>(Column::E, Row::_1, PlayerColor::white, std::format("{}/img/white/king1.png", PROJECT_ROOT_DIR));
	cells[Column::F][Row::_1] = std::make_unique<Bishop>(Column::F, Row::_1, PlayerColor::white,
														 std::format("{}/img/white/bishop1.png", PROJECT_ROOT_DIR));
	cells[Column::G][Row::_1] = std::make_unique<Knight>(Column::G, Row::_1, PlayerColor::white,
														 std::format("{}/img/white/knight1.png", PROJECT_ROOT_DIR));
	cells[Column::H][Row::_1] =
		std::make_unique<Rook>(Column::H, Row::_1, PlayerColor::white, std::format("{}/img/white/rook1.png", PROJECT_ROOT_DIR));

	// black pieces
	cells[Column::A][Row::_7] =
		std::make_unique<Pawn>(Column::A, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::B][Row::_7] =
		std::make_unique<Pawn>(Column::B, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::C][Row::_7] =
		std::make_unique<Pawn>(Column::C, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::D][Row::_7] =
		std::make_unique<Pawn>(Column::D, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::E][Row::_7] =
		std::make_unique<Pawn>(Column::E, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::F][Row::_7] =
		std::make_unique<Pawn>(Column::F, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::G][Row::_7] =
		std::make_unique<Pawn>(Column::G, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));
	cells[Column::H][Row::_7] =
		std::make_unique<Pawn>(Column::H, Row::_7, PlayerColor::black, std::format("{}/img/black/pawn1.png", PROJECT_ROOT_DIR));

	cells[Column::A][Row::_8] =
		std::make_unique<Rook>(Column::A, Row::_8, PlayerColor::black, std::format("{}/img/black/rook1.png", PROJECT_ROOT_DIR));
	cells[Column::B][Row::_8] = std::make_unique<Knight>(Column::B, Row::_8, PlayerColor::black,
														 std::format("{}/img/black/knight1.png", PROJECT_ROOT_DIR));
	cells[Column::C][Row::_8] = std::make_unique<Bishop>(Column::C, Row::_8, PlayerColor::black,
														 std::format("{}/img/black/bishop1.png", PROJECT_ROOT_DIR));
	cells[Column::D][Row::_8] =
		std::make_unique<Queen>(Column::D, Row::_8, PlayerColor::black, std::format("{}/img/black/queen1.png", PROJECT_ROOT_DIR));
	cells[Column::E][Row::_8] =
		std::make_unique<King>(Column::E, Row::_8, PlayerColor::black, std::format("{}/img/black/king1.png", PROJECT_ROOT_DIR));
	cells[Column::F][Row::_8] = std::make_unique<Bishop>(Column::F, Row::_8, PlayerColor::black,
														 std::format("{}/img/black/bishop1.png", PROJECT_ROOT_DIR));
	cells[Column::G][Row::_8] = std::make_unique<Knight>(Column::G, Row::_8, PlayerColor::black,
														 std::format("{}/img/black/knight1.png", PROJECT_ROOT_DIR));
	cells[Column::H][Row::_8] =
		std::make_unique<Rook>(Column::H, Row::_8, PlayerColor::black, std::format("{}/img/black/rook1.png", PROJECT_ROOT_DIR));
}

void Board::removePiece(const Square &square) { cells[square.col][square.row] = nullptr; }

const Square Board::findMove(Move &move) {
	// looping through the whole board and finding which piece can move to
	// move.to. should use the attributes inside the move structs, specifically
	// when the piece is known, and when the move results in a check captures
	// are only relevant for enpessant which is already covered in the doMove
	// function.

	// TODO: implement function for each piece similar to the getMoves functions
	// but which has move.to as input argument

	std::vector<Square> ret{};

	const Column colStart = (move.from.col == Column::none) ? Column::A : move.from.col;
	const Column colEnd = (move.from.col == Column::none) ? Column::H : move.from.col;

	const Row rowStart = (move.from.row == Row::none) ? Row::_1 : move.from.row;
	const Row rowEnd = (move.from.row == Row::none) ? Row::_8 : move.from.row;

	// starting with known piecename case:
	switch (move.piece) {
	case PieceName::pawn:
		for (Column col = colStart; col <= colEnd; ++col) {
			for (Row row = rowStart; row <= rowEnd; ++row) {
				auto &piece = cells[col][row];
				if (piece != nullptr && piece->getPlayerColor() == turn && piece->getName() == PieceName::pawn) {
					getPawnMoves(piece, ret);
					for (auto &entry : ret) {
						if (entry == move.to) {
							if (move.check) {
								move.from = {col, row};
								if (moveChecksOpponent(move)) {
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
				auto &piece = cells[col][row];
				if (piece != nullptr && piece->getPlayerColor() == turn && piece->getName() == PieceName::rook) {
					getRookMoves(piece, ret);
					for (auto &entry : ret) {
						if (entry == move.to) {
							if (move.check) {
								move.from = {col, row};
								if (moveChecksOpponent(move)) {
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
				auto &piece = cells[col][row];
				if (piece != nullptr && piece->getPlayerColor() == turn && piece->getName() == PieceName::knight) {
					getKnightMoves(piece, ret);
					for (auto &entry : ret) {
						if (entry == move.to) {
							if (move.check) {
								move.from = {col, row};
								if (moveChecksOpponent(move)) {
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
				auto &piece = cells[col][row];
				if (piece != nullptr && piece->getPlayerColor() == turn && piece->getName() == PieceName::bishop) {
					getBishopMoves(piece, ret);
					for (auto &entry : ret) {
						if (entry == move.to) {
							if (move.check) {
								move.from = {col, row};
								if (moveChecksOpponent(move)) {
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
				auto &piece = cells[col][row];
				if (piece != nullptr && piece->getPlayerColor() == turn && piece->getName() == PieceName::queen) {
					getQueenMoves(piece, ret);
					for (auto &entry : ret) {
						if (entry == move.to) {
							if (move.check) {
								move.from = {col, row};
								if (moveChecksOpponent(move)) {
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
				auto &piece = cells[col][row];
				if (piece != nullptr && piece->getPlayerColor() == turn && piece->getName() == PieceName::king) {
					getKingMoves(piece, ret);
					for (auto &entry : ret) {
						if (entry == move.to) {
							if (move.check) {
								move.from = {col, row};
								if (moveChecksOpponent(move)) {
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
		// Unknown piecename case:
		for (Column col = colStart; col <= colEnd; ++col) {
			for (Row row = rowStart; row <= rowEnd; ++row) {
				auto &piece = cells[col][row];
				if (piece == nullptr)
					continue;

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

					for (auto &entry : ret) {
						if (entry == move.to) {
							if (move.check) {
								move.from = {col, row};
								if (moveChecksOpponent(move)) {
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

void Board::movePiece(const Square &from, const Square &to) {
	assert(from.col >= Column::A && from.col <= Column::H);
	assert(from.row >= Row::_1 && from.row <= Row::_8);
	assert(to.col >= Column::A && to.col <= Column::H);
	assert(to.row >= Row::_1 && to.row <= Row::_8);

	auto &fromPiece = cells[from.col][from.row];
	auto &toPiece = cells[to.col][to.row];

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

// This implementation only works for simple moves.
// I need to create a Move type and fill it with the move information.
// Every move should be findable using the from and to squares except for:
// - Promotions
// - Resign
// - Draw offers + responses
//

// With the current implementation, I also don't take into account:
// - Checks
// - Castling
//
// Then:
// game.pushback(move);
// gameStepFor();
//
void Board::tryMove(const Square &from, const Square &to) {
	assert(from.col >= Column::A && from.col <= Column::H);
	assert(from.row >= Row::_1 && from.row <= Row::_8);
	assert(to.col >= Column::A && to.col <= Column::H);
	assert(to.row >= Row::_1 && to.row <= Row::_8);
	if (cells[from.col][from.row]->getPlayerColor() != turn)
		return;
	if (from == to) return;

	std::cout << playerColorCStr(turn) << " attempted move " << from << " to " << to << std::endl;

	Move move{.from = from, .to = to, .piece = cells[from.col][from.row]->getName()};
	auto &fromPiece = cells[from.col][from.row];
	auto &toPiece = cells[to.col][to.row];
	bool valid = false;

	// captures
	if (toPiece != nullptr) {
		move.capture = true;
		move.capturePiece = toPiece->getName();
	}

	// enPassant
	if (move.piece == PieceName::pawn && toPiece != nullptr && toPiece->getName() == PieceName::pawn) {
		if (to.col == from.col + 1 || to.col == from.col - 1) {
			move.enPassant = true;
		}
	}

	// promotion (To Queen for now)
	if (move.piece == PieceName::pawn && toPiece != nullptr && (to.row == Row::_1 || to.row == Row::_8)) {
		move.promotion = true;
		move.promotionPiece = PieceName::queen;
	}

	// castle
	if (move.piece == PieceName::king && to.row == from.row) {
		if ((turn == PlayerColor::white && whiteCanCastleKingside) || (turn == PlayerColor::black && blackCanCastleKingside)) {
			if (to.col >= Column::G && to.col <= Column::H) {
				if (cells[Column::F][from.row] == nullptr && cells[Column::G][from.row] == nullptr) {
					move.castle = true;
					move.castleSide = CastleSide::kingSide;
					valid = true;
				}
			}
		} else if ((turn == PlayerColor::white && whiteCanCastleQueenside) || (turn == PlayerColor::black && blackCanCastleQueenside)) {
			if (to.col >= Column::A && to.col <= Column::C) {
				if (cells[Column::B][from.row] == nullptr && cells[Column::C][from.row] == nullptr && cells[Column::D][from.row] == nullptr) {
					move.castle = true;
					move.castleSide = CastleSide::queenSide;
					valid = true;
				}
			}
		}
	}

	// make sure the player itself is not checked after move
	if (moveChecksSelf(move)) {
		std::cout << "player is in check after tried move" << std::endl;
		return;
	} else {
	}

	// check
	if (moveChecksOpponent(move)) {
		move.check = true;
	}

	std::vector<Square> ret{};
	getMoves(from.col, from.row, ret);
	for (auto& e : ret) {
		if (e == to) {
			valid = true;
		}
	}
	if (valid) {
		game.push_back(move);
		gameStepFor();
	} else {
		std::cout << "invalid move" << std::endl;
	}
}

void Board::getMoves(const Column &col, const Row &row, std::vector<Square> &to) {
	auto &piece = cells[col][row];
	if (piece == nullptr)
		return;

	switch (piece->getName()) {
	case PieceName::pawn:
		getPawnMoves(piece, to);
		return;
	case PieceName::rook:
		getRookMoves(piece, to);
		return;
	case PieceName::knight:
		getKnightMoves(piece, to);
		return;
	case PieceName::bishop:
		getBishopMoves(piece, to);
		return;
	case PieceName::queen:
		getQueenMoves(piece, to);
		return;
	case PieceName::king:
		getKingMoves(piece, to);
		return;
	default:
		assert(0);
	}
}

void Board::getPawnMoves(const std::unique_ptr<Piece> &piece, std::vector<Square> &to) {
	assert(to.empty());
	assert(piece != nullptr);
	assert(piece->getPlayerColor() == PlayerColor::white || piece->getPlayerColor() == PlayerColor::black);

	const Column col = piece->getCol();
	const Row row = piece->getRow();
	const PlayerColor color = piece->getPlayerColor();
	const int8_t colorDiff = (color == PlayerColor::white) ? 1 : -1;

	// simple move
	if (cells[col][row + colorDiff] == nullptr) {
		to.emplace_back(col, row + colorDiff);
		// double first move
		if ((color == PlayerColor::white && row == Row::_2) || (color == PlayerColor::black && row == Row::_7)) {
			if (cells[col][row + colorDiff] == nullptr)
				to.emplace_back(col, row + (int8_t)(2 * colorDiff));
		}
	}
	// captures
	if (col != Column::A) {
		auto &capturePiece = cells[col - 1][row + colorDiff];
		if (capturePiece != nullptr && capturePiece->getPlayerColor() != color) {
			to.emplace_back(col - 1, row + colorDiff);
		}
	}

	if (col != Column::H) {
		auto &capturePiece = cells[col + 1][row + colorDiff];
		if (capturePiece != nullptr && capturePiece->getPlayerColor() != color) {
			to.emplace_back(col + 1, row + colorDiff);
		}
	}
}

void Board::getRookMoves(const std::unique_ptr<Piece> &piece, std::vector<Square> &to) {
	assert(to.empty());
	assert(piece != nullptr);
	assert(piece->getPlayerColor() == PlayerColor::white || piece->getPlayerColor() == PlayerColor::black);

	Column col = piece->getCol();
	Row row = piece->getRow();
	const PlayerColor color = piece->getPlayerColor();

	do {
		++col;
		if (col > Column::H)
			break;
		if (cells[col][row] == nullptr || cells[col][row]->getPlayerColor() != color) {
			to.emplace_back(col, row);
		}

	} while (cells[col][row] == nullptr);

	col = piece->getCol();

	do {
		--col;
		if (col < Column::A)
			break;
		if (cells[col][row] == nullptr || cells[col][row]->getPlayerColor() != color) {
			to.emplace_back(col, row);
		}

	} while (cells[col][row] == nullptr);

	col = piece->getCol();

	do {
		++row;
		if (row > Row::_8)
			break;
		if (cells[col][row] == nullptr || cells[col][row]->getPlayerColor() != color) {
			to.emplace_back(col, row);
		}

	} while (cells[col][row] == nullptr);

	row = piece->getRow();

	do {
		--row;
		if (row < Row::_1)
			break;
		if (cells[col][row] == nullptr || cells[col][row]->getPlayerColor() != color) {
			to.emplace_back(col, row);
		}

	} while (cells[col][row] == nullptr);
}

void Board::getKnightMoves(const std::unique_ptr<Piece> &piece, std::vector<Square> &to) {
	assert(to.empty());
	assert(piece != nullptr);
	assert(piece->getPlayerColor() == PlayerColor::white || piece->getPlayerColor() == PlayerColor::black);

	const Column col = piece->getCol();
	const Row row = piece->getRow();
	const PlayerColor color = piece->getPlayerColor();

	for (const int8_t &colDiff : {(int8_t)-2, (int8_t)2}) {
		for (const int8_t &rowDiff : {(int8_t)-1, (int8_t)1}) {
			if (col + colDiff >= Column::A && col + colDiff <= Column::H && row + rowDiff >= Row::_1 &&
				row + rowDiff <= Row::_8) {
				if (cells[col + colDiff][row + rowDiff] == nullptr ||
					cells[col + colDiff][row + rowDiff]->getPlayerColor() != color) {
					to.emplace_back(col + colDiff, row + rowDiff);
				}
			}
		}
	}

	for (const int8_t &rowDiff : {(int8_t)-2, (int8_t)2}) {
		for (const int8_t &colDiff : {(int8_t)-1, (int8_t)1}) {
			if (col + colDiff >= Column::A && col + colDiff <= Column::H && row + rowDiff >= Row::_1 &&
				row + rowDiff <= Row::_8) {
				if (cells[col + colDiff][row + rowDiff] == nullptr ||
					cells[col + colDiff][row + rowDiff]->getPlayerColor() != color) {
					to.emplace_back(col + colDiff, row + rowDiff);
				}
			}
		}
	}
}

void Board::getBishopMoves(const std::unique_ptr<Piece> &piece, std::vector<Square> &to) {
	assert(to.empty());
	assert(piece != nullptr);
	assert(piece->getPlayerColor() == PlayerColor::white || piece->getPlayerColor() == PlayerColor::black);

	const PlayerColor color = piece->getPlayerColor();

	// not the most beautifull implementation, but it works
	for (const int8_t &colDiff : {(int8_t)-1, (int8_t)1}) {
		for (const int8_t &rowDiff : {(int8_t)-1, (int8_t)1}) {
			Column col = piece->getCol();
			Row row = piece->getRow();

			while (1) {
				col += colDiff;
				row += rowDiff;
				if (col >= Column::A && col <= Column::H && row >= Row::_1 && row <= Row::_8) {
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

void Board::getQueenMoves(const std::unique_ptr<Piece> &piece, std::vector<Square> &to) {
	assert(to.empty());
	assert(piece != nullptr);
	assert(piece->getPlayerColor() == PlayerColor::white || piece->getPlayerColor() == PlayerColor::black);

	// same as rook
	Column col = piece->getCol();
	Row row = piece->getRow();
	const PlayerColor color = piece->getPlayerColor();

	do {
		++col;
		if (col > Column::H)
			break;
		if (cells[col][row] == nullptr || cells[col][row]->getPlayerColor() != color) {
			to.emplace_back(col, row);
		}

	} while (cells[col][row] == nullptr);

	col = piece->getCol();

	do {
		--col;
		if (col < Column::A)
			break;
		if (cells[col][row] == nullptr || cells[col][row]->getPlayerColor() != color) {
			to.emplace_back(col, row);
		}

	} while (cells[col][row] == nullptr);

	col = piece->getCol();

	do {
		++row;
		if (row > Row::_8)
			break;
		if (cells[col][row] == nullptr || cells[col][row]->getPlayerColor() != color) {
			to.emplace_back(col, row);
		}

	} while (cells[col][row] == nullptr);

	row = piece->getRow();

	do {
		--row;
		if (row < Row::_1)
			break;
		if (cells[col][row] == nullptr || cells[col][row]->getPlayerColor() != color) {
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
				if (col >= Column::A && col <= Column::H && row >= Row::_1 && row <= Row::_8) {
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

void Board::getKingMoves(const std::unique_ptr<Piece> &piece, std::vector<Square> &to) {
	assert(to.empty());
	assert(piece != nullptr);
	assert(piece->getPlayerColor() == PlayerColor::white || piece->getPlayerColor() == PlayerColor::black);

	const Column col = piece->getCol();
	const Row row = piece->getRow();
	const PlayerColor color = piece->getPlayerColor();

	for (const int8_t &colDiff : {(int8_t)-1, (int8_t)0, (int8_t)1}) {
		for (const int8_t &rowDiff : {(int8_t)-1, (int8_t)0, (int8_t)1}) {
			if (colDiff == 0 && rowDiff == 0)
				continue;
			if (col + colDiff >= Column::A && col + colDiff <= Column::H && row + rowDiff >= Row::_1 &&
				row + rowDiff <= Row::_8) {
				if (cells[col + colDiff][row + rowDiff] == nullptr ||
					cells[col + colDiff][row + rowDiff]->getPlayerColor() != color)
					to.emplace_back(col + colDiff, row + rowDiff);
			}
		}
	}
}

void Board::doMove(Move &move) {
	if (move.capture) {
		move.capturePiece = cells[move.to.col][move.to.row]->getName();
	}


	if (move.enPassant) {
		move.from.col = move.from.col;
		move.from.row = (move.to.row == Row::_3) ? Row::_4 : Row::_5;

		removePiece(Square{move.to.col, move.from.row});
		movePiece(move.from, move.to);
		toggleTurn();
		return;
	}

	// missing case where promotion is combined with capture
	if (move.promotion) {
		assert(move.promotionPiece != PieceName::none);
		transformPiece(move.from, move.promotionPiece);

		move.from.col = move.to.col;
		move.from.row = (move.to.row == Row::_1) ? Row::_2 : Row::_7;
		movePiece(move.from, move.to);
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

	//if from square is not known, find the possible move.
	if (!(move.from.col >= Column::A && move.from.col <= Column::H && move.from.row >= Row::_1 && move.from.row <= Row::_8)) {
		move.from = findMove(move);
	}
	auto &fromPiece = cells[move.from.col][move.from.row];

	if (fromPiece->getName() == PieceName::king) {
		switch (turn) {
			case PlayerColor::white:
				whiteCanCastleKingside = false;
				whiteCanCastleQueenside = false;
				break;
			case PlayerColor::black:
				blackCanCastleKingside = false;
				blackCanCastleQueenside = false;
				break;
			default:
				assert(0);
				break;
		}
	}

	if (fromPiece->getName() == PieceName::rook) {
		switch (turn) {
			case PlayerColor::white:
				if (move.from.col == Column::A && move.from.row == Row::_1) whiteCanCastleQueenside = false;
				if (move.from.col == Column::H && move.from.row == Row::_1) whiteCanCastleKingside = false;
				break;
			case PlayerColor::black:
				if (move.from.col == Column::A && move.from.row == Row::_8) blackCanCastleQueenside = false;
				if (move.from.col == Column::H && move.from.row == Row::_8) blackCanCastleKingside = false;
				break;
			default:
				assert(0);
				break;
		}
	}
				
	// base case
	movePiece(move.from, move.to);
	toggleTurn();
	return;
}

void Board::undoMove(Move &move) {
	//std::cout << "Attempting to undo move : piece = " << move.piece;
	//std::cout << ", From col = " << move.from.col << ", row = " << move.from.row;
	//std::cout << ", To col = " << move.to.col << ", row = " << move.to.row << std::endl;

	if (move.enPassant) {

		transformPiece(Square{move.to.col, move.from.row}, PieceName::pawn);
		movePiece(move.to, move.from);
		if (move.capture)
			transformPiece(move.to, move.capturePiece);
		toggleTurn();
		return;
	}

	// missing case where promotion is combined with capture
	if (move.promotion) {
		assert(move.promotionPiece != PieceName::none);
		transformPiece(move.to, PieceName::pawn);

		movePiece(move.to, move.from);
		if (move.capture)
			transformPiece(move.to, move.capturePiece);
		toggleTurn();
		return;
	}

	if (move.castle) {
		assert(move.castleSide != CastleSide::none);
		toggleTurn();
		unCastle(move.castleSide);
		return;
	}

	if (move.endOfGame) {
		assert(move.end != End::none);
		endGame(End::none);
		return;
	}

	if (move.drawOffer) {
		drawOffer();
		return;
	}

	//if from square is not known, find the possible move.
	if (!(move.from.col >= Column::A && move.from.col <= Column::H && move.from.row >= Row::_1 && move.from.row <= Row::_8)) {
		move.from = findMove(move);
	}
	auto &toPiece = cells[move.to.col][move.to.row];

	if (toPiece != nullptr && toPiece->getName() == PieceName::king) {
		switch (turn) {
			case PlayerColor::white:
				whiteCanCastleKingside = true;						//this is gonna cause bugs
				whiteCanCastleQueenside = true;
				break;
			case PlayerColor::black:
				blackCanCastleKingside = true;
				blackCanCastleQueenside = true;
				break;
			default:
				assert(0);
				break;
		}
	}

	if (toPiece != nullptr && toPiece->getName() == PieceName::rook) {
		switch (turn) {
			case PlayerColor::white:
				if (move.from.col == Column::A && move.from.row == Row::_1) whiteCanCastleQueenside = true;
				if (move.from.col == Column::H && move.from.row == Row::_1) whiteCanCastleKingside = true;
				break;
			case PlayerColor::black:
				if (move.from.col == Column::A && move.from.row == Row::_8) blackCanCastleQueenside = true;
				if (move.from.col == Column::H && move.from.row == Row::_8) blackCanCastleKingside = true;
				break;
			default:
				assert(0);
				break;
		}
	}
				
	// base case
	movePiece(move.to, move.from);
	if (move.capture)
		transformPiece(move.to, move.capturePiece);
	toggleTurn();
	return;
}

const bool Board::moveChecksSelf(const Move &move) {
	return moveChecks(move, turn);
}

const bool Board::moveChecksOpponent(const Move &move) {
	switch (turn) {
		case PlayerColor::white:
			return moveChecks(move, PlayerColor::black);
		case PlayerColor::black:
			return moveChecks(move, PlayerColor::white);
		default:
			assert(0);
			return false;
	}
}

const bool Board::moveChecks(const Move &move, const PlayerColor player) {
	game.push_back(move);
	gameStepFor();

	Square king{};
	for (Column col = Column::A; col <= Column::H; ++col) {
		for (Row row = Row::_1; row <= Row::_8; ++row) {
			auto &piece = cells[col][row];
			if (piece != nullptr && piece->getName() == PieceName::king && piece->getPlayerColor() == player) {
				king = Square{col, row};
			}
		}
	}
	assert(king.col != Column::none && king.row != Row::none);

	bool f = false;
	std::vector<Square> ret{};
	for (Column col = Column::A; col <= Column::H; ++col) {
		for (Row row = Row::_1; row <= Row::_8; ++row) {
			auto &piece = cells[col][row];
			if (piece == nullptr)
				continue;
			if (piece->getPlayerColor() == player)
				continue;

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
			}

			for (auto &e : ret) {
				if (e == king) {
					f = true;
				}
			}
			ret.clear();
		}
	}

	gameStepBack();
	game.pop_back();
	return f;
}

void Board::gameSkipBack() {
	while (game.begin() + gameIt != game.begin()) {
		gameIt--;
		undoMove(game[gameIt]);
	}
}

void Board::gameStepBack() {
	if (game.begin() + gameIt != game.begin()) {
		gameIt--;
		undoMove(game[gameIt]);
	}
}

void Board::gameStepFor() {
	if (game.begin() + gameIt != game.end()) {
		doMove(game[gameIt]);
		gameIt++;
	}
}

void Board::gameSkipFor() {
	while (game.begin() + gameIt != game.end()) {
		doMove(game[gameIt]);
		gameIt++;
	}
}

void Board::loadGame(const std::string &text) {
	std::vector<std::string> moveSetStr{};
	// converts the gameStr in individual strings
	parseAN(text, moveSetStr);

	// converts the vector of moves in {"f3", "e5", "g4", "Qh4#"} format into a
	// vector of individual moves and load into game
	parseMoveSet(moveSetStr, game);
}
