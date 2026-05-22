#include <string>
#include <iostream>
#include "token_strategies.hpp"
#include "lexer.hpp"

TokenStrategyResult::TokenStrategyResult(DMToken t, uint32_t d) : token(t), characters_consumed(d) {}

ScanResult::ScanResult(bool terminated, int steps_forward) : terminate_scan(terminated), steps(steps_forward) {}

TokenStrategy::TokenStrategy(Lexer& lexer) : lexer(lexer) {}

uint32_t TokenStrategy::peek(int cursor_start_pos, std::optional<int> max_steps) {
    int peek_cursor_pos = cursor_start_pos;
    while(peek_cursor_pos < lexer.source.length()) {
        char current = lexer.source[peek_cursor_pos];
        if(current == '\\'){
            if( peek_cursor_pos + 2 < lexer.source.length() && 
                lexer.source[peek_cursor_pos + 1] == '\r' &&
                lexer.source[peek_cursor_pos + 2] == '\n'){
               
                    peek_cursor_pos += 3;
                    continue;
                }
            else if(peek_cursor_pos + 2 < lexer.source.length()){
                peek_cursor_pos += 2;
            }
        }
        
        ScanResult result = scan(peek_cursor_pos);
        peek_cursor_pos += result.steps;
        if(result.terminate_scan == true){
            break;
        }
        else{
            peek_cursor_pos++;
        }
    }

    uint32_t distance = peek_cursor_pos - cursor_start_pos;
    return distance;
}

TokenStrategyResult TokenStrategy::result(DMToken::TokenType type, std::string_view value, int pos, int length) {
    CursorCoordinate coords = lexer.get_cursor_coordinates(pos);
    DMToken new_token = DMToken(type, value, coords);
    return TokenStrategyResult(new_token, length);
}