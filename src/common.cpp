#include "common.hpp"
#include "cassert"
#include <utility>

constexpr Column operator+(const Column col, const Column num) {
    assert(col >= Column::A && col <= Column::H);
    Column ret = Column{std::to_underlying(col) + std::to_underlying(num)};

    assert(ret >= Column::A && ret <= Column::H);
    return ret;
}

constexpr Column operator-(const Column col, const Column num) {
    assert(col >= Column::A && col <= Column::H);
    Column ret = Column{std::to_underlying(col) - std::to_underlying(num)};

    assert(ret >= Column::A && ret <= Column::H);
    return ret;
}

constexpr Column operator+(const Column col, const uint8_t num) {
    assert(col >= Column::A && col <= Column::H);
    Column ret = Column{std::to_underlying(col) + num};

    assert(ret >= Column::A && ret <= Column::H);
    return ret;
}

constexpr Column operator-(const Column col, const uint8_t num) {
    assert(col >= Column::A && col <= Column::H);
    Column ret = Column{std::to_underlying(col) - num};
    
    assert(ret >= Column::A && ret <= Column::H);
    return ret;
}

constexpr Row operator+(const Row row, const Row num){
    assert(row >= Row::_1 && row <= Row::_8);
    Row ret = Row{std::to_underlying(row) + std::to_underlying(num)};

    assert(ret >= Row::_1 && ret <= Row::_8);
    return ret;
}
constexpr Row operator-(const Row row, const Row num) {
    assert(row >= Row::_1 && row <= Row::_8);
    Row ret = Row{std::to_underlying(row) - std::to_underlying(num)};

    assert(ret >= Row::_1 && ret <= Row::_8);
    return ret;
}

constexpr Row operator+(const Row row, const uint8_t num) {
    assert(row >= Row::_1 && row <= Row::_8);
    Row ret = Row{std::to_underlying(row) + num};

    assert(ret >= Row::_1 && ret <= Row::_8);
    return ret;
}
constexpr Row operator-(const Row row, const uint8_t num) {
    assert(row >= Row::_1 && row <= Row::_8);
    Row ret = Row{std::to_underlying(row) - num};

    assert(ret >= Row::_1 && ret <= Row::_8);
    return ret;
}

const char * playerColorCStr(const PlayerColor playerColor) {
    switch (playerColor) {
        case PlayerColor::white:
            return "white";
        case PlayerColor::black:
            return "black";        
        case PlayerColor::none:

        default:
            assert(false, "Invalid playerColor\n");  //not sure yet why this gives errors
            return "";
    }
}