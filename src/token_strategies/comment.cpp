#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string CommentStrategy::name() const {
    return "CommentStrategy";
}

CommentStrategy* CommentStrategy::instance() {
    static CommentStrategy instance;
    return &instance;
}

TokenStrategyResult CommentStrategy::run(Lexer& lexer, const std::string& source, int pos) {
    char current = source[pos];
    if(current == '/') {
        // we're not dealing with comments tonight...
    }
};

bool CommentStrategy::is_escape_character(char character) {
    if(character == '\r'){
        return false;
    }
    if(character == '\n'){
        return true;
    }
    return true;
}