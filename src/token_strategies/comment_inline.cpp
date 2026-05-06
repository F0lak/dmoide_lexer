#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>


// Inline Comment Strategy.  Continues to end of line, unless escaped
// Does not store the content of the comment, but does flag it as a comment

std::string CommentInlineStrategy::name() const {
    return "CommentInlineStrategy";
}

TokenStrategyResult CommentInlineStrategy::run(int pos) {
    int label_length = peek(pos);
    std::string label = lexer.source.substr(pos, label_length);

    DMToken token = DMToken(DMToken::TokenType::COMMENT_INLINE, "COMMENT_INLINE " + label, lexer.get_cursor_coordinates(pos));

    if(label_length == 0){
        label_length = 1;
    }
    return TokenStrategyResult(token, label_length);
};

bool CommentInlineStrategy::is_escape_character(char character) {
    if(character == '\r'){
        return true;
    }
    return false;
}

ScanResult CommentInlineStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    return ScanResult(is_escape_character(character), 0);
}