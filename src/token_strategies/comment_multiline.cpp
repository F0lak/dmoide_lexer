#include "token_strategies.hpp"
#include "lexer.hpp"
#include <string>
#include <iostream>


// Inline Comment Strategy.  Continues to end of line, unless escaped
// Does not store the content of the comment, but does flag it as a comment

std::string CommentMultilineStrategy::name() const {
    return "CommentMultilineStrategy";
}

CommentMultilineStrategy* CommentMultilineStrategy::instance() {
    static CommentMultilineStrategy instance;
    return &instance;
}

TokenStrategyResult CommentMultilineStrategy::run(Lexer& lexer, const std::string& source, int pos) {
    int label_length = peek(source, pos);
    std::string label = source.substr(pos, label_length);

    DMToken token = DMToken(DMToken::TokenType::COMMENT_MULTILINE, "COMMENT_MULTILINE " + label, lexer.get_cursor_coordinates(pos));

    if(label_length == 0){
        label_length = 1;
    }
    return TokenStrategyResult(token, label_length);
};

bool CommentMultilineStrategy::is_escape_character(char character) {
    return true;
}

ScanResult CommentMultilineStrategy::scan(const std::string& source, int cursor_pos) {
    char character = source[cursor_pos];
    if( character == '*' &&\
        cursor_pos + 1 < source.length() &&\
        source[cursor_pos + 1] == '/' &&\
        --stack_count == 0) {
            return ScanResult(true, 2);
    }
    if( character == '/' &&\
        cursor_pos + 1 < source.length() &&\
        source[cursor_pos + 1] == '*'){
        stack_count++;
    }
    return ScanResult(false, 0);
}