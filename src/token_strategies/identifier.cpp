#include "token_strategies.hpp"
#include "lexer.hpp"
#include "dm_keywords.hpp"
#include <string>
#include <iostream>

std::string IdentifierStrategy::name() const {
    return "IdentifierStrategy";
}

TokenStrategyResult IdentifierStrategy::run(int pos) {
    int label_length = peek(pos);
    std::string label = lexer.source.substr(pos, label_length);

    DMToken token = DMToken(lexer.get_cursor_coordinates(pos));
    if(DMKeywords::is_keyword(label)){
        token.type = DMKeywords::mapping.at(label);
        token.value = "KEYWORD: " + label;
    }
    else {
        token.type = DMToken::TokenType::IDENTIFIER;
        token.value = "IDENTIFIER: " + label;
    }

    return TokenStrategyResult(token, label_length);
};

bool IdentifierStrategy::is_escape_character(char character) {
    if(std::isalpha(character)) {
        return false;
    }
    if(std::isdigit(character)) {
        return false;
    }
    if(character == '_') {
        return false;
    }
    return true;
}

ScanResult IdentifierStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    return ScanResult(is_escape_character(character), 0);
}