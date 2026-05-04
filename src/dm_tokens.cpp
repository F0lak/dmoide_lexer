#include "dm_tokens.hpp"

DMToken::DMToken( DMToken::TokenType t, std::string v, uint32_t l, uint32_t c ) : type(t), value(v), line(l), column(c) {}