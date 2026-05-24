#include "token_strategies.hpp"
#include "lexer.hpp"
#include "dm_keywords.hpp"
#include <string>
#include <iostream>

std::string NumberStrategy::name() const {
    return "NumberStrategy";
}

TokenStrategyResult NumberStrategy::run(int pos) {
    ZoneScoped;
    int label_length = peek(pos);
    std::string_view label = lexer.source.substr(pos, label_length);

    dot_count = 0;
    return result(DMToken::TokenType::NUMBER, label, pos, label_length);
};

bool NumberStrategy::is_escape_character(char character) {
    if(std::isdigit(character)) {
        return false;
    }
    if(character == '.') {
        if(++dot_count < 2){
            return false;
        }
    }
    return true;
}

ScanResult NumberStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    return ScanResult(is_escape_character(character), 0);
}