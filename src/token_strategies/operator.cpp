#include "token_strategies.hpp"
#include "lexer.hpp"
#include "dm_operators.hpp"
#include <string>
#include <iostream>

std::string OperatorStrategy::name() const {
    return "OperatorStrategy";
}

TokenStrategyResult OperatorStrategy::run(int pos) {
    int label_length = peek(pos);
    std::string label = lexer.source.substr(pos, label_length);

    DMToken token = DMToken(lexer.get_cursor_coordinates(pos));
    if(DMOperators::is_operator(label)){
        token.type = DMOperators::mapping.at(label);
        token.value = "OPERATOR: " + label;
    }
    else {
        token.type = DMToken::TokenType::NULL_OP;
        token.value = "NULL_OPERATOR: " + label;
    }
    if(label_length == 0){
        label_length = 1;
    }
    return TokenStrategyResult(token, label_length);
};

bool OperatorStrategy::is_escape_character(char character) {
    if(DMOperators::is_operator(character)) {
        return false;
    }
    return true;
}

ScanResult OperatorStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    return ScanResult(is_escape_character(character), 0);
}