#include <string>
#include <iostream>
#include "token_strategies.hpp"
#include "lexer.hpp"

TokenStrategyResult::TokenStrategyResult(DMToken t, uint32_t d) : token(t), characters_consumed(d) {}

TerminatorResult::TerminatorResult(bool f, int s) : found(f), size(s) {}

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
        
        TerminatorResult termination = is_terminated(source, peek_cursor_pos);
        peek_cursor_pos += termination.size;
        if(termination.found == true){
            break;
        }
        else{
            peek_cursor_pos++;
        }
    }

    uint32_t distance = peek_cursor_pos - cursor_start_pos;
    return distance;
}