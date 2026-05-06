#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string WhitespaceStrategy::name() const {
    return "WhitespaceStrategy";
}

TokenStrategyResult WhitespaceStrategy::run(int pos) {
    char current = lexer.source[pos];
    if(current == '\r') {
        uint32_t peek_dist = peek(pos);
        pos += peek_dist;
        CursorCoordinate coords = lexer.get_cursor_coordinates(pos);
        DMToken new_token = DMToken( DMToken::TokenType::NEWLINE, "NEWLINE", coords);
        return TokenStrategyResult(new_token, peek_dist);
    }
    if(current == ';') {
        CursorCoordinate coords = lexer.get_cursor_coordinates(pos);
        DMToken new_token = DMToken( DMToken::TokenType::NEWLINE, "NEWLINE", coords);
        return TokenStrategyResult(new_token, 1);
    }
    if(current == ' '){
        CursorCoordinate coords = lexer.get_cursor_coordinates(pos);
        DMToken new_token = DMToken( DMToken::TokenType::WHITESPACE, "SPACE", coords);
        return TokenStrategyResult(new_token, 1);
    }
    if(current == '\t'){
        CursorCoordinate coords = lexer.get_cursor_coordinates(pos);
        DMToken new_token = DMToken( DMToken::TokenType::WHITESPACE, "TAB", coords);
        return TokenStrategyResult(new_token, 1);
        }
    else {
        CursorCoordinate coords = lexer.get_cursor_coordinates(pos);
        DMToken new_token = DMToken( DMToken::TokenType::IGNORE, "IGNORE", coords);
        return TokenStrategyResult(new_token, 1);
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