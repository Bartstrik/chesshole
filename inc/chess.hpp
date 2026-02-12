#pragma once

#include <array>
#include <memory>
#include <string>
#include "render.hpp"

enum playerColor {
    white,
    black
};

enum pieceName {
    pawn,
    bishop,
    knight,
    rook,
    queen,
    king
};

class Piece {
    protected:
    pieceName name;
    uint8_t row, col;
    playerColor player;
    
    public:
    Image pieceImage;

    Piece() = delete;
    Piece(const pieceName& name, const uint8_t& row, const uint8_t& col, const playerColor& player, const std::string& pieceImagePath);
    virtual ~Piece();

    const pieceName getName();
    void setName(const pieceName& name);
    
    const uint8_t getRow();
    void setRow(const uint8_t& row);
    
    const uint8_t getCol();
    void setCol(const uint8_t& col);
    
    const playerColor getPlayer();
};

class Pawn : public Piece {
    private:
    bool hasMoved = false;
    //implement moves

    public:
    Pawn() = delete;
    Pawn(const uint8_t& row, const uint8_t& col, const playerColor& player, const std::string& pawnImagePath);
    ~Pawn();
};

//maybe make functions to adjust board/boardimage instead of having it public
class Board {
    private:
    std::string history{};
    playerColor turn = playerColor::white;

    public:
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board{};
    Image boardImage;

    Board() = delete;
    Board(const std::string& boardImagePath);
    virtual ~Board();

    const std::string getHistory();
    const playerColor getTurn();
};