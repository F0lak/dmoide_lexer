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

    if(label_length == 0){
        label_length = 1;
    }
    
    return result(DMToken::TokenType::COMMENT_INLINE, "COMMENT_INLINE " + label, pos, label_length);
};

bool CommentInlineStrategy::is_escape_character(char character) {
    if(character == '\r'){
        return true;
    }
    if(character == '\n'){
        return true;
    }
    return false;
}

ScanResult CommentInlineStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    return ScanResult(is_escape_character(character), 0);
}