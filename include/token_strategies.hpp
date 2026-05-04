#pragma once
#include <string>
#include "dm_tokens.hpp"

class Lexer;

struct TokenStrategyResult {
    TokenStrategyResult(DMToken t, uint32_t d);
    DMToken token;
    int characters_consumed;
};

class TokenStrategy {
    public:
        virtual std::string name() const = 0;
        virtual TokenStrategyResult run(Lexer& lexer, const std::string& source, int pos) = 0;
        virtual ~TokenStrategy() = default;
    protected:
        uint32_t peek(const std::string& source, int cursor_pos);
        virtual bool is_escape_character(char c) = 0;
};

#define TOKEN_STRATEGY(StratName) \
class StratName : public TokenStrategy { \
    public: \
        std::string name() const override; \
        static StratName* instance(); \
        TokenStrategyResult run(Lexer& lexer, const std::string& source, int pos) override; \
    protected: \
        bool is_escape_character(char c) override; \
};

TOKEN_STRATEGY(PlaceholderStrategy)
TOKEN_STRATEGY(WhitespaceStrategy)
TOKEN_STRATEGY(NumberStrategy)
TOKEN_STRATEGY(IdentifierStrategy)
TOKEN_STRATEGY(OperatorStrategy)