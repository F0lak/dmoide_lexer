#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string StringMultilineStrategy::name() const {
    return "StringMultilineStrategy";
}

TokenStrategyResult StringMultilineStrategy::run(int pos) {
    ZoneScoped;
    int label_length = peek(pos+2);
    std::string label = "";
    if(label_length <= 1){
        label_length = 2;
    }
    switch(lexer.source[pos+label_length]){
        case '[':
            label = lexer.source.substr(pos+2, label_length-2);
            lexer.string_stack.context = StringStack::Context::Multiline;
            return result(DMToken::TokenType::EMBED_OPEN, "EMBED_OPEN", pos+label_length, -1); // label_length + 2 accounts for the open {" and the closing [
        default:
            label = lexer.source.substr(pos+2, label_length-2);
            return result(DMToken::TokenType::STRING_MULTILINE_OPEN, "MULTILINE STRING OPEN" + label, pos, label_length+2); // label_length 4 accounts for opening and closing {" "}
    }
};

bool StringMultilineStrategy::is_escape_character(char character) {
    return false;
}

ScanResult StringMultilineStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    switch (character){
        case '[':
            return ScanResult(true, 1);
        case '"':
            if(cursor_pos + 1 < lexer.source.length() &&\
            lexer.source[cursor_pos+1] == '}')
                {
                    return ScanResult(true, 2);
                }
        }
    //return ScanResult(false, 0);
    return ScanResult(false, 0);
}