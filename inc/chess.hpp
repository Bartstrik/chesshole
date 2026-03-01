#pragma once

#include <array>
#include <memory>
#include <string>
#include "raylib.h"
#include "lexer.hpp"
#include "common.hpp"

class Piece {
    protected:
    PieceName name;
    Row row;
    Column col;
    PlayerColor player;
    
    public:
    Image pieceImage;

    Piece() = delete;
    Piece(const PieceName& name, const Column& col, const Row& row, const PlayerColor& player, const std::string& pieceImagePath);
    virtual ~Piece();

    const PieceName getName();
    void setName(const PieceName& name);
    
    const Row getRow();
    void setRow(const Row& row);
    
    const Column getCol();
    void setCol(const Column& col);
    
    const PlayerColor getPlayer();
};

class Pawn : public Piece {
    private:
    bool hasMoved = false;
    //implement moves

    public:
    Pawn() = delete;
    Pawn(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath);
    ~Pawn();
};

class Rook : public Piece {
    private:
    //implement moves

    public:
    Rook() = delete;
    Rook(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath);
    ~Rook();
};

class Knight : public Piece {
    private:
    //implement moves

    public:
    Knight() = delete;
    Knight(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath);
    ~Knight();
};

class Bishop : public Piece {
    private:
    //implement moves

    public:
    Bishop() = delete;
    Bishop(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath);
    ~Bishop();
};

class Queen : public Piece {
    private:
    //implement moves

    public:
    Queen() = delete;
    Queen(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath);
    ~Queen();
};

class King : public Piece {
    private:
    //implement moves

    public:
    King() = delete;
    King(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath);
    ~King();
};

//maybe make functions to adjust cells/boardimage instead of having it public
class Board {
    private:
    std::string history{};
    PlayerColor turn = PlayerColor::white;
    bool whiteCanCastle = true;
    bool blackCanCastle = true;

    public:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> cells{};
    Image originalBoardImage, boardImage;

    Board() = delete;
    Board(const std::string& boardImagePath);
    virtual ~Board();

    const std::string getHistory();
    const PlayerColor getTurn();
    void setPieces();
    int movePiece(const Move move);

    //Using the MoveDesc type, current board position and the game rules, we try to determine the actual move itself.
    const Move findMove(const MoveDesc moveDesc);
};