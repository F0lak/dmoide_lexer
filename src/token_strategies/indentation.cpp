#include "token_strategies.hpp"
#include "lexer.hpp"
#include "dm_keywords.hpp"
#include <string>
#include <iostream>

std::string IndentationStrategy::name() const {
    return "IndentationStrategy";
}

TokenStrategyResult IndentationStrategy::run(int pos) {
    ZoneScoped;
    int indent_count = peek(pos);
    DMToken indent_token = new_token( DMToken::TokenType::INDENT, "INDENT", pos);

    if( lexer.source.length() > pos && \
        !isspace(lexer.source[pos+1]))
        {    
            lexer.tokens.emplace_back(indent_token);
            
            int difference =  lexer.indentation.last_line_count - lexer.indentation.current_count;
            if(difference > 0){
                for (int i = difference; i > 0; --i){
                    pos++;
                    DMToken dedent_token = new_token(DMToken::TokenType::DEDENT, "DEDENT", pos); // more easy optimization opportunities
                    lexer.tokens.emplace_back(dedent_token);
                }
            }
            lexer.indentation.last_line_count = lexer.indentation.current_count;
            lexer.indentation.current_count = 0;
            DMToken discard_token = new_token(DMToken::TokenType::TOKEN_IGNORE, "TOKEN_IGNORE", pos);
            return TokenStrategyResult(discard_token, 1);
        }

    lexer.indentation.current_count++;
    return TokenStrategyResult(indent_token, 1);
};

bool IndentationStrategy::is_escape_character(char character) {
    return (!isspace(character));
}

ScanResult IndentationStrategy::scan(int cursor_pos) {
    char character = lexer.source[cursor_pos];
    return ScanResult(is_escape_character(character), 0);
}
