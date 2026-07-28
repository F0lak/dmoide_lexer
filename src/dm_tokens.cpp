#include "dm_tokens.hpp"
#include "cursor_coordinates.hpp"
#include <tracy/Tracy.hpp>


// Used when the whole Token context is known at instantiation
DMToken::DMToken( DMToken::TokenType t, uint32_t p, uint8_t l) :
    type(t),
    category(token_classes[static_cast<uint16_t>(t)]),
    pos(p),
    length(l)
    {
        ZoneScoped;
    }

std::string_view DMToken::name() const {
    return token_names[static_cast<uint16_t>(type)];
}