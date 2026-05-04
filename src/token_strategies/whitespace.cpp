#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string WhitespaceStrategy::name() const {
    return "WhitespaceStrategy";
}

WhitespaceStrategy* WhitespaceStrategy::instance() {
    static WhitespaceStrategy instance;
    return &instance;
}

TokenStrategyResult WhitespaceStrategy::run(Lexer& lexer, const std::string& source, int pos) {
    char current = source[pos];
    if(current == '\r') {
        uint32_t peek_dist = peek(source, pos);
        std::cout << "we're in a carriage return\n";
        pos += peek_dist;
        std::cout << "Creating result:\n    CursorCoordinate\n";
        CursorCoordinate coords = lexer.get_cursor_coordinates(pos);
        std::cout << "  DMToken\n";
        DMToken new_token = DMToken( DMToken::TokenType::NEWLINE, "NEWLINE", coords);
        std::cout << "Returning result: " << new_token.value << "\n";
        return TokenStrategyResult(new_token, peek_dist);
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