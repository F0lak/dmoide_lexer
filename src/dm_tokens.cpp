#include "dm_tokens.hpp"
#include "cursor_coordinates.hpp"
#include <tracy/Tracy.hpp>

// Used when we know a token be instantiated but 'type' and 'value' will be assigned later
DMToken::DMToken(uint32_t p) :
    type(TokenType::PLACEHOLDER),
    category(TokenCategory::None),
    pos(p)
    {
        ZoneScoped; 
    }

// Used when the whole Token context is known at instantiation
DMToken::DMToken( DMToken::TokenType t, uint32_t p) :
    type(t),
    category(token_classes[static_cast<uint16_t>(t)]),
    pos(p)
    {
        ZoneScoped;
    }

std::string_view DMToken::name() const {
    return token_names[static_cast<uint16_t>(type)];
};