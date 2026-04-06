#pragma once

#include <array>
#include <initializer_list>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "common.hpp"
#include "raylib.h"

class Piece {
  protected:
	PieceName name;
	Row row;
	Column col;
	PlayerColor player;
	Image image;

  public:
	Piece() = delete;
	Piece(const PieceName &name, const Column &col, const Row &row,
		  const PlayerColor &player, const std::string &imagePath);
	virtual ~Piece();

	const PieceName getName() const;
	void setName(const PieceName &name);

	const Row getRow() const;
	void setRow(const Row &row);

	const Column getCol() const;
	void setCol(const Column &col);

	const Square getSquare() const;
	void setSquare(const Square &sq);

	const PlayerColor getPlayerColor() const;

	const Image &getImage() const;
	void setImage(const std::string &imagePath);
};

class Pawn : public Piece {
  private:
	// implement moves

  public:
	Pawn() = delete;
	Pawn(const Column &col, const Row &row, const PlayerColor &player,
		 const std::string &imagePath);
	~Pawn();
};

class Rook : public Piece {
  private:
	bool hasMoved = false;

  public:
	Rook() = delete;
	Rook(const Column &col, const Row &row, const PlayerColor &player,
		 const std::string &imagePath);
	~Rook();
};

class Knight : public Piece {
  private:
  public:
	Knight() = delete;
	Knight(const Column &col, const Row &row, const PlayerColor &player,
		   const std::string &imagePath);
	~Knight();
};

class Bishop : public Piece {
  private:
  public:
	Bishop() = delete;
	Bishop(const Column &col, const Row &row, const PlayerColor &player,
		   const std::string &imagePath);
	~Bishop();
};

class Queen : public Piece {
  private:
  public:
	Queen() = delete;
	Queen(const Column &col, const Row &row, const PlayerColor &player,
		  const std::string &imagePath);
	~Queen();
};

class King : public Piece {
  private:
	bool hasMoved = false;

  public:
	King() = delete;
	King(const Column &col, const Row &row, const PlayerColor &player,
		 const std::string &imagePath);
	~King();
};

template <typename T, std::size_t N> struct EnumArray {
	std::array<T, N> data{};

	template <typename E> constexpr T &operator[](E e) {
		return data[std::to_underlying(e)];
	}

	template <typename E> constexpr const T &operator[](E e) const {
		return data[std::to_underlying(e)];
	}
};

class Board {
  private:
	std::vector<Move> game{};
	std::vector<Move>::const_iterator gameIt;

	PlayerColor turn = PlayerColor::white;
	bool whiteCanCastle = true;
	bool blackCanCastle = true;
	bool check = false;
	bool gameDone = false;
	PlayerColor gameEnd = PlayerColor::none;

	void toggleTurn();
	void endGame(const End &end);
	void transformPiece(const Square &square, const PieceName &pieceName);
	void castle(const CastleSide &castleSide);
	void drawOffer() const;
	void removePiece(const Square &square);
	const Square findMove(const Move &move);

	void getPawnMoves(const std::unique_ptr<Piece> &piece,
					  std::vector<Square> &to);
	void getRookMoves(const std::unique_ptr<Piece> &piece,
					  std::vector<Square> &to);
	void getKnightMoves(const std::unique_ptr<Piece> &piece,
						std::vector<Square> &to);
	void getBishopMoves(const std::unique_ptr<Piece> &piece,
						std::vector<Square> &to);
	void getQueenMoves(const std::unique_ptr<Piece> &piece,
					   std::vector<Square> &to);
	void getKingMoves(const std::unique_ptr<Piece> &piece,
					  std::vector<Square> &to);

  public:
	EnumArray<EnumArray<std::unique_ptr<Piece>, 8>, 8> cells;
	Image originalBoardImage, boardImage;

	Board() = delete;
	Board(const std::string &boardImagePath);
	virtual ~Board();

	const std::vector<Move> getGame() const;
	void setGame(std::initializer_list<Move> iList );
	const PlayerColor getTurn() const;
	const bool getGameDone() const;
	const PlayerColor getGameEnd() const;
	void setPieces();
	void movePiece(const Square &from, const Square &to);

	// getMoves expects an empty vector ref as argument, and it will add the
	// squares the piece can move to. the vector is an argument and not a return
	// value to prevent unnecessary copying or allocating it on the heap. this
	// function is overriden by the child classes
	void getMoves(const Column &col, const Row &row, std::vector<Square> &to);
	// Using the Move type, current board position and the game rules, we try to
	// determine the actual move itself.
	void doMove(const Move &move);
	void undoMove(const Move &move);

	const bool moveIsCheck(const Square &from, const Square &to);

	void gameSkipBack();
	void gameStepBack();
	void gameStepFor();
	void gameSkipFor();

	void loadGame(const std::string& text);
};
