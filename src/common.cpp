#include "common.hpp"
#include "cassert"

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