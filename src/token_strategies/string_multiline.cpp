#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string StringMultilineStrategy::name() const {
    return "StringMultilineStrategy";
}

TokenStrategyResult StringMultilineStrategy::run(int pos) {
    int label_length = peek(pos+2);
    std::string label = "";
    if(label_length <= 0){
        label_length = 1;
    }
    switch(lexer.source[pos+2+label_length]){
        case '[':
            label = lexer.source.substr(pos+2, label_length);
            // special case where we need to register both the closed string and the embed open
            // because the lexer isn't aware yet that it's in an embedded expression until the embed open is registered
            lexer.register_token(result(DMToken::TokenType::STRING_MULTILINE, "MULTILINE STRING: " + label, pos, label_length+1)); // +2 to account for open {"
            lexer.string_stack.context = StringStack::Context::Multiline;
            return result(DMToken::TokenType::EMBED_OPEN, "EMBED_OPEN", pos+label_length, 1); // label_length + 2 accounts for the open {" and the closing [
        default:
            label = lexer.source.substr(pos+2, label_length-2);
            return result(DMToken::TokenType::STRING_MULTILINE, "MULTILINE STRING: " + label, pos, label_length+4); // label_length 4 accounts for opening and closing {" "}
    }
};

bool StringMultilineStrategy::is_escape_character(char character) {
    if(character == '['){
        return true;
    }
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
    return ScanResult(is_escape_character(character), 0);
}