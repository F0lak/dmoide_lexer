#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string StringStrategy::name() const {
    return "StringStrategy";
}

TokenStrategyResult StringStrategy::run(int pos) {
    ZoneScoped;
    // pos+1 here accounts for and skips over the opening "
    lexer.string_stack.context = StringStack::Context::Inline;
    int label_length = peek(pos+1);
    std::string_view label = lexer.source.substr(pos+1, label_length);
    if(label_length <= 0){
        label_length = 1;
    }
    switch(lexer.source[pos+1+label_length]){
        // This can be pulled into the main loop
        case '\n':
            return result(DMToken::TokenType::TOKEN_ERROR, "ERROR: unterminated string", pos, label_length);

        // th
        case '[':
            return result(DMToken::TokenType::EMBED_OPEN, "EMBED_OPEN", pos+label_length+1, label_length+2);
        default:
            return result(DMToken::TokenType::STRING_OPEN, "STRING_OPEN", pos, label_length+2); // label_length + 2 accounts for the open and closing "
    }
};

bool StringStrategy::is_escape_character(char character) {
    return true;
}

ScanResult StringStrategy::scan(int cursor_pos) {
    return ScanResult(true, 0);
}