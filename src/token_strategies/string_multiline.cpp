#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string StringMultilineStrategy::name() const {
    return "StringMultilineStrategy";
}

TokenStrategyResult StringMultilineStrategy::run(int pos) {
    int label_length = peek(pos+2);
    std::string label = lexer.source.substr(pos+2, label_length-2);
    if(label_length <= 0){
        label_length = 1;
    }
    return result(DMToken::TokenType::STRING, "MULTILINE STRING: " + label, pos, label_length+4);
};

bool StringMultilineStrategy::is_escape_character(char character) {
    return false;
}

ScanResult StringMultilineStrategy::scan(int cursor_pos) {
    bool terminate = false;
    char character = lexer.source[cursor_pos];
    if( character == '"' &&\
        cursor_pos + 1 < lexer.source.length() &&\
        lexer.source[cursor_pos+1] == '}')
        {
            return ScanResult(true, 2);
        }
    return ScanResult(false, 0);
}