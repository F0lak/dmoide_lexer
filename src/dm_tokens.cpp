#include "dm_tokens.hpp"
#include "cursor_coordinates.hpp"

// Used when we know a token be instantiated but 'type' and 'value' will be assigned later
DMToken::DMToken(CursorCoordinate c) {
    type = TokenType::PLACEHOLDER;
    value_index = 0;
    line = c.line;
    column = c.column;
}

// Used when the whole Token context is known at instantiation
DMToken::DMToken( DMToken::TokenType t, uint32_t v, CursorCoordinate c ) {
    type = t;
    value_index = v;
    line = c.line;
    column = c.column;
}

std::string_view DMToken::get_name() {
    return token_names[static_cast<uint16_t>(type)];
};