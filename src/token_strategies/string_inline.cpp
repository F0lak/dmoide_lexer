#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string StringStrategy::name() const {
    return "StringStrategy";
}

TokenStrategyResult StringStrategy::run(int pos) {
    ZoneScoped;
    // pos+1 here accounts for and skips over the opening "
    int label_length = peek(pos+1);
    std::string_view label = lexer.source.substr(pos+1, label_length);
    if(label_length <= 0){
        label_length = 1;
    }
    switch(lexer.source[pos+1+label_length]){
        case '\n':
            return result(DMToken::TokenType::TOKEN_ERROR, "ERROR: unterminated string", pos, label_length); // might want to append a newline here as well? maybe
        case '[':
            // special case where we need to register both the closed string and the embed open
            // because the lexer isn't aware yet that it's in an embedded expression until the embed open is registered
            lexer.register_token(result(DMToken::TokenType::STRING, label, pos, 0));
            lexer.string_stack.context = StringStack::Context::Inline;
            return result(DMToken::TokenType::EMBED_OPEN, "EMBED_OPEN", pos+label_length+1, label_length+2); // label_length + 2 accounts for the open " and the closing [
        default:
            return result(DMToken::TokenType::STRING, label, pos, label_length+2); // label_length + 2 accounts for the open and closing "
    }
};

bool StringStrategy::is_escape_character(char character) {
    switch(character){
        case '"':
        case '[':
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