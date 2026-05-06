#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>

std::string PlaceholderStrategy::name() const  {
    return "PlaceholderStrategy";
}

bool PlaceholderStrategy::is_escape_character(char c) {
    return true;
}

TokenStrategyResult PlaceholderStrategy::run(int pos) {
    return result(DMToken::TokenType::PLACEHOLDER, "PLACEHOLDER", pos, 1);
}

ScanResult PlaceholderStrategy::scan(int cursor_pos) {
    return ScanResult(true, 0);
}