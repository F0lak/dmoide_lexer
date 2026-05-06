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