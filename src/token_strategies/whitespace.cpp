#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string WhitespaceStrategy::name() const {
    return "WhitespaceStrategy";
}

TokenStrategyResult WhitespaceStrategy::run(int pos) {
    ZoneScoped;
    char current = lexer.source[pos];
    switch(current){
        case '\n':
            return result(DMToken::TokenType::NEWLINE, "NEWLINE", pos, 1);
        case ' ':
            return result(DMToken::TokenType::TOKEN_WHITESPACE, "SPACE", pos, 1);
        case '\t':
            return result(DMToken::TokenType::TOKEN_WHITESPACE, "TAB", pos, 1);
        case ';':
            return result(DMToken::TokenType::NEWLINE, "NEWLINE", pos, 1);
        default:
            return result(DMToken::TokenType::TOKEN_IGNORE, "TOKEN_IGNORE", pos, 1);
    }
};

bool WhitespaceStrategy::is_escape_character(char character) {
    return true;
}

ScanResult WhitespaceStrategy::scan(int cursor_pos) {
    return ScanResult(true, 0);
}