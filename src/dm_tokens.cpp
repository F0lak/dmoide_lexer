#include "dm_tokens.hpp"
#include "cursor_coordinates.hpp"
#include <tracy/Tracy.hpp>

// Used when we know a token be instantiated but 'type' and 'value' will be assigned later
DMToken::DMToken(uint32_t p) {
    ZoneScoped;
    type = TokenType::PLACEHOLDER;
    pos = p;
}

// Used when the whole Token context is known at instantiation
DMToken::DMToken( DMToken::TokenType t, uint32_t p) {
    ZoneScoped;
    type = t;
    pos = p;
}

std::string_view DMToken::name() {
    return token_names[static_cast<uint16_t>(type)];
};