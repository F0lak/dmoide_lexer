#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string StringStrategy::name() const {
    return "StringStrategy";
}

TokenStrategyResult StringStrategy::run(int pos) {
    int label_length = peek(pos+1);
    std::string label = lexer.source.substr(pos+1, label_length);
    if(label_length <= 0){
        label_length = 1;
    }
    switch(lexer.source[pos+label_length+1]){
        case '\n':
            return result(DMToken::TokenType::ERROR, "ERROR: unterminated string", pos, label_length);
        default:
            return result(DMToken::TokenType::STRING, "STRING: " + label, pos, label_length+2);
    }
};

bool StringStrategy::is_escape_character(char character) {
    switch(character){
        case '"':
        case '\n':
            return true;
        default:
            return false;
    }
}

ScanResult StringStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    return ScanResult(is_escape_character(character), 0);
}