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

    if(label_length == 0){
        label_length = 1;
    }

    if(DMOperators::is_operator(label)){
        return result(DMOperators::mapping.at(label), "OPERATOR: " + label, pos, label_length);
    }
    else {
        return result(DMToken::TokenType::NULL_OP, "NULL_OPERATOR: " + label, pos, label_length);
    }
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