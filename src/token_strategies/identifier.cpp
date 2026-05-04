#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string IdentifierStrategy::name() const {
    return "IdentifierStrategy";
}

IdentifierStrategy* IdentifierStrategy::instance() {
    static IdentifierStrategy instance;
    return &instance;
}

TokenStrategyResult IdentifierStrategy::run(Lexer& lexer, const std::string& source, int pos) {
    int label_length = peek(source, pos);
    std::string label = source.substr(pos, label_length);
    
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