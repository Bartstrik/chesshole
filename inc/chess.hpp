#pragma once

#include <array>
#include <memory>
#include <string>
#include "raylib.h"

enum class PlayerColor {
    white,
    black
};

enum class PieceName {
    pawn,
    bishop,
    knight,
    rook,
    queen,
    king
};

//maybe go back to weakly defined enums, so i don't have to typecast it
enum class Column {
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
};

enum class Row {
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8
};

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
    Pawn(const Column& col, const Row& row, const PlayerColor& player, const std::string& pawnImagePath);
    ~Pawn();
};

//maybe make functions to adjust cells/boardimage instead of having it public
class Board {
    private:
    std::string history{};
    PlayerColor turn = PlayerColor::white;

    public:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> cells{};
    Image originalBoardImage, boardImage;

    Board() = delete;
    Board(const std::string& boardImagePath);
    virtual ~Board();

    const std::string getHistory();
    const PlayerColor getTurn();
    void setPieces();
};