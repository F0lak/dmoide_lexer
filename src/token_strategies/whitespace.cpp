#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string WhitespaceStrategy::name() const {
    return "WhitespaceStrategy";
}

TokenStrategyResult WhitespaceStrategy::run(int pos) {
    char current = lexer.source[pos];
    switch(current){
        case '\r': {
            uint32_t peek_dist = peek(pos);
            pos += peek_dist;
            return result(DMToken::TokenType::NEWLINE, "NEWLINE", pos, peek_dist);
        }
        case ';':
            return result(DMToken::TokenType::NEWLINE, "NEWLINE", pos, 1);
        case ' ':
            return result(DMToken::TokenType::WHITESPACE, "SPACE", pos, 1);
        case '\t':
            return result(DMToken::TokenType::WHITESPACE, "TAB", pos, 1);
        default:
            return result(DMToken::TokenType::IGNORE, "IGNORE", pos, 1);
    }
};

bool WhitespaceStrategy::is_escape_character(char character) {
    if(character == '\r'){
        return false;
    }
    if(character == '\n'){
        return true;
    }
    return true;
}

ScanResult WhitespaceStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    return ScanResult(is_escape_character(character), 0);
}