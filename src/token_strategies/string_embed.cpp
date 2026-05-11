#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string StringEmbedStrategy::name() const {
    return "StringEmbedStrategy";
}

TokenStrategyResult StringEmbedStrategy::run(int pos) {
    switch(lexer.source[pos]){
        case '[':
            return result(DMToken::TokenType::EMBED_OPEN, "EMBED_OPEN", pos, 1);
        case ']':
            return result(DMToken::TokenType::EMBED_CLOSE, "EMBED_CLOSE", pos, 1);
        default:
            return result(DMToken::TokenType::TOKEN_ERROR, "TOKEN_ERROR_11", pos, 1);
    }
};

bool StringEmbedStrategy::is_escape_character(char character) {
    return false;
}

ScanResult StringEmbedStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    return ScanResult(is_escape_character(character), 0);
}