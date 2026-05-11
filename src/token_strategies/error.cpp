#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>

std::string ErrorStrategy::name() const  {
    return "ErrorStrategy";
}

bool ErrorStrategy::is_escape_character(char c) {
    return true;
}

TokenStrategyResult ErrorStrategy::run(int pos) {
    // unhandled error
    return result(DMToken::TokenType::TOKEN_ERROR, "TOKEN_ERROR_-1", pos, 1);
}

ScanResult ErrorStrategy::scan(int cursor_pos) {
    return ScanResult(true, 0);
}