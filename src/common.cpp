#include "common.hpp"
#include "cassert"
#include <utility>

constexpr Column operator++(const Column col) {
    return Column{std::to_underlying(col) + 1};
}

constexpr Column operator--(const Column col) {
    return Column{std::to_underlying(col) - 1};
}

constexpr Column operator+=(const Column col, const Column num) {
    return Column{std::to_underlying(col) + std::to_underlying(num)};
}

constexpr Column operator+=(const Column col, const int8_t num) {
    return Column{std::to_underlying(col) + num};
}

constexpr Column operator+(const Column col, const Column num) { 
    return Column{std::to_underlying(col) + std::to_underlying(num)};
}

constexpr Column operator-(const Column col, const Column num) {
    return Column{std::to_underlying(col) - std::to_underlying(num)};
}

constexpr Column operator+(const Column col, const int8_t num) {
    return Column{std::to_underlying(col) + num};
}

constexpr Column operator-(const Column col, const int8_t num) {
    return Column{std::to_underlying(col) - num};
}

constexpr Row operator++(const Row row) {
    return Row{std::to_underlying(row) + 1};
}

constexpr Row operator++(const Row row) {
    return Row{std::to_underlying(row) -1};
}

constexpr Row operator+=(const Row row, const Row num) {
    return Row{std::to_underlying(row) + std::to_underlying(num)};
}

constexpr Row operator+=(const Row row, const int8_t num) {
    return Row{std::to_underlying(row) + num};
}

constexpr Row operator+(const Row row, const Row num){
    return Row{std::to_underlying(row) + std::to_underlying(num)};
}

constexpr Row operator-(const Row row, const Row num) {
    return Row{std::to_underlying(row) - std::to_underlying(num)};
}

constexpr Row operator+(const Row row, const int8_t num) {
    return Row{std::to_underlying(row) + num};
}

constexpr Row operator-(const Row row, const int8_t num) {
    return Row{std::to_underlying(row) - num};
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