#include <string>
#include <iostream>
#include "token_strategies.hpp"
#include "lexer.hpp"

TokenStrategyResult::TokenStrategyResult(DMToken t, uint32_t d) : token(t), characters_consumed(d) {}

ScanResult::ScanResult(bool terminated, int steps_forward) : terminate_scan(terminated), steps(steps_forward) {}

uint32_t TokenStrategy::peek(const std::string& source, int cursor_start_pos, std::optional<int> max_steps) {
    int peek_cursor_pos = cursor_start_pos;
    while(peek_cursor_pos < source.length()) {
        char current = source[peek_cursor_pos];
        if(current == '\\'){
            if( peek_cursor_pos + 2 < source.length() && 
                source[peek_cursor_pos + 1] == '\r' &&
                source[peek_cursor_pos + 2] == '\n'){
               
                    peek_cursor_pos += 3;
                    continue;
                }
        }
        
        ScanResult result = scan(source, peek_cursor_pos);
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