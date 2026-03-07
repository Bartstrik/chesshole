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
    Image image;

    public:
    Piece() = delete;
    Piece(const PieceName& name, const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath);
    virtual ~Piece();

    const PieceName getName();
    void setName(const PieceName& name);
    
    const Row getRow();
    void setRow(const Row& row);
    
    const Column getCol();
    void setCol(const Column& col);
    
    const PlayerColor getPlayer();

    const Image& getImage();
    void setImage(const std::string& imagePath);

    // getMoves expects an empty vector ref as argument, and it will add the squares the piece can move to. 
    // the vector is an argument and not a return value to prevent unnecessary copying or allocating it on the heap. 
    // this function is overriden by the child classes
    virtual void getMoves(std::vector<Square>& to); 

};

class Pawn : public Piece {
    private:
    //implement moves

    public:
    Pawn() = delete;
    Pawn(const Column& col, const Row& row, const PlayerColor& player, const std::string& imagePath);
    ~Pawn();

    void getMoves(std::vector<Square>& to) override; 
    void getCaptureMoves(std::vector<Square>& to); 
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
    bool check = false;

    void endGame(End end);
    void transformPiece(Square square, PieceName pieceName);
    void castle(CastleSide castleSide);
    void drawOffer();
    void removePiece(const Square square);

    // some function which i pass in the whole move struct and it creates a vector of references to the pieces which are able to make the move specified. 
    // vector should finalize with size 1.
    // it updates move.from 
    int32_t findMove(Move& move);



    public:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> cells{};
    Image originalBoardImage, boardImage;

    Board() = delete;
    Board(const std::string& boardImagePath);
    virtual ~Board();

    const std::string getHistory();
    const PlayerColor getTurn();
    void setPieces();
    void movePiece(const Square from, const Square to);

    //Using the MoveDesc type, current board position and the game rules, we try to determine the actual move itself.
    void doMove(Move& moveDesc);
};