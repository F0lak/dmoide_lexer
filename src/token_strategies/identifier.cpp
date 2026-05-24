#include "token_strategies.hpp"
#include "lexer.hpp"
#include "dm_keywords.hpp"
#include <string>
#include <iostream>

std::string IdentifierStrategy::name() const {
    return "IdentifierStrategy";
}

TokenStrategyResult IdentifierStrategy::run(int pos) {
    ZoneScoped;
    int label_length = peek(pos);
    std::string_view label = lexer.source.substr(pos, label_length);

    if(DMKeywords::is_keyword(label)){
        return result(DMKeywords::mapping.at(label), label, pos, label_length);
    }
    else {
        return result(DMToken::TokenType::IDENTIFIER, label, pos, label_length);
    }
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