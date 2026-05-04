#include <string>
#include <iostream>
#include "token_strategies.hpp"

TokenStrategyResult::TokenStrategyResult(DMToken t, uint32_t d) : token(t), characters_consumed(d) {}

uint32_t TokenStrategy::peek(const std::string& source, int cursor_start_pos, std::optional<int> max_steps) {
    int peek_cursor_pos = cursor_start_pos;
    int peek_cursor_steps = 0;
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
        if(is_escape_character(current)){
            break;
        }
        else{
            peek_cursor_pos++;
            peek_cursor_steps++;
        }
    }

    uint32_t distance = peek_cursor_pos - cursor_start_pos;
    return distance;
}