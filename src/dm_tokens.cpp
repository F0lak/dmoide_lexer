#include "dm_tokens.hpp"
#include "cursor_coordinates.hpp"

DMToken::DMToken( DMToken::TokenType t, std::string v, CursorCoordinate c ) {
    type = t;
    value = v;
    line = c.line;
    column = c.column;
}