#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>

std::string PlaceholderStrategy::name() const  {
    return "PlaceholderStrategy";
}

PlaceholderStrategy* PlaceholderStrategy::instance() {
    static PlaceholderStrategy instance;
    return &instance;
}

DMToken PlaceholderStrategy::run(const std::string& source, int pos) {
    return { DMToken::TokenType::PLACEHOLDER, "placeholder_value" };
};


std::string WhitespaceStrategy::name() const {
    return "WhitespaceStrategy";
}

WhitespaceStrategy* WhitespaceStrategy::instance() {
    static WhitespaceStrategy instance;
    return &instance;
}

DMToken WhitespaceStrategy::run(const std::string& source, int pos) {
    return {};
    /*
    Lexer& lexer = Lexer::instance();
    char current = source[pos];
    if(current == '\r') {
        lexer.current_context = Lexer::Context::NEWLINE;
        std::string label = peek(source);
        pos += label.length();
        DMToken new_token;
        new_token.type = DMToken::TokenType::NEWLINE;
        new_token.value = "[NEWLINE]\n";
        lexer.tokens.emplace_back(new_token);
    }
    else {
        DMToken new_token;
        new_token.type = DMToken::TokenType::WHITESPACE;
        new_token.value = "[WHITESPACE]";
        lexer.tokens.emplace_back(new_token);
    }
        */
};