#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>


// Inline Comment Strategy.  Continues to end of line, unless escaped
// Does not store the content of the comment, but does flag it as a comment

std::string CommentMultilineStrategy::name() const {
    return "CommentMultilineStrategy";
}

TokenStrategyResult CommentMultilineStrategy::run(int pos) {
    int label_length = peek(pos);
    std::string label = lexer.source.substr(pos, label_length);

    if(label_length == 0){
        label_length = 1;
    }

    return result(DMToken::TokenType::COMMENT_MULTILINE, "COMMENT_MULTI_LINE " + label, pos, label_length);
};

bool CommentMultilineStrategy::is_escape_character(char character) {
    return true;
}

ScanResult CommentMultilineStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    if( character == '*' &&\
        cursor_pos + 1 < lexer.source.length() &&\
        lexer.source[cursor_pos + 1] == '/' &&\
        --stack_count == 0) {
            return ScanResult(true, 2);
    }
    if( character == '/' &&\
        cursor_pos + 1 < lexer.source.length() &&\
        lexer.source[cursor_pos + 1] == '*'){
        stack_count++;
    }
    return ScanResult(false, 0);
}