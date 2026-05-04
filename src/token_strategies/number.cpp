#include "token_strategies.hpp"
#include "lexer.hpp"
#include "dm_keywords.hpp"
#include <string>
#include <iostream>

std::string NumberStrategy::name() const {
    return "NumberStrategy";
}

NumberStrategy* NumberStrategy::instance() {
    static NumberStrategy instance;
    return &instance;
}

TokenStrategyResult NumberStrategy::run(Lexer& lexer, const std::string& source, int pos) {
    int label_length = peek(source, pos);
    std::string label = source.substr(pos, label_length);

    DMToken token = DMToken(DMToken::TokenType::NUMBER, "NUMBER: " + label, lexer.get_cursor_coordinates(pos));

    return TokenStrategyResult(token, label_length);
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

TerminatorResult NumberStrategy::is_terminated(const std::string& source, int cursor_pos) {
    char character = source[cursor_pos];
    return TerminatorResult(is_escape_character(character), 0);
}