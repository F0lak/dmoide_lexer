#pragma once
#include <string>
#include <vector>
#include "dm_tokens.hpp"
#include "token_strategies.hpp"

class Lexer {
    enum class Context {
        START_OF_FILE,
        LABEL,
        NUMBER,
        NEWLINE,
        END_OF_FILE
    };

    public:
        Lexer();
        static void initialize();
        std::vector<dm_token::DMToken> tokens;
        Context current_context = Context::START_OF_FILE;
        int indents = 0;
        std::size_t cursor_pos = 0;
        std::string buffer = "";
        std::string current_dm_path = "";
        std::string scan(const std::string& source);
        static std::array<TokenStrategy*, 5> strategy_lookup;

    private:
        std::string peek(const std::string& source);
        bool is_escape_character(const char character);
};