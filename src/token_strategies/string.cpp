#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string StringStrategy::name() const {
    return "StringStrategy";
}

TokenStrategyResult StringStrategy::run(int pos) {
    int label_length = peek(pos);
    std::string label = lexer.source.substr(pos, label_length);
    return result(DMToken::TokenType::STRING, "STRING: " + label, pos, label_length);
};

bool StringStrategy::is_escape_character(char character) {
    if(character == '"'){
        return true;
    }
    return false;
}

ScanResult StringStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    return ScanResult(is_escape_character(character), 0);
}