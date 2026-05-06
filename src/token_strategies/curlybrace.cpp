#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>

std::string CurlyBraceStrategy::name() const {
    return "CurlyBraceStrategy";
}

/*
    It's worth noting here that When multi line strings are supported, that this
    class should NOT handle them.

    They should be identified by the Lexer class and then passed off to their
    own TokenStrategy class
*/

TokenStrategyResult CurlyBraceStrategy::run(int pos) {
    char current = lexer.source[pos];

    if(current == '{') {
        return result(DMToken::TokenType::INDENT, "INDENT", pos, 1);
    }

    else if(current == '}'){
        return result(DMToken::TokenType::DEDENT, "DEDENT", pos, 1);
    }
};

bool CurlyBraceStrategy::is_escape_character(char character) {
    return true;
}

ScanResult CurlyBraceStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    return ScanResult(is_escape_character(character), 0);
}