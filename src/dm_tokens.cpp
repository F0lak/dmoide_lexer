#include "dm_tokens.hpp"
#include "cursor_coordinates.hpp"

// Used when we know a token be instantiated but 'type' and 'value' will be assigned later
DMToken::DMToken(CursorCoordinate c) {
    type = TokenType::PLACEHOLDER;
    value = "NO_VALUE";
    line = c.line;
    column = c.column;
}

// Used when the whole Token context is known at instantiation
DMToken::DMToken( DMToken::TokenType t, std::string_view v, CursorCoordinate c ) {
    type = t;
    value = v;
    line = c.line;
    column = c.column;
}