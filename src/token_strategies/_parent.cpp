#include <string>
#include <iostream>
#include "token_strategies.hpp"

TokenStrategyResult::TokenStrategyResult(DMToken t, uint32_t d) : token(t), characters_consumed(d) {}

uint32_t TokenStrategy::peek(const std::string& source, int cursor_start_pos) {
    int peek_cursor_pos = cursor_start_pos;
    while(peek_cursor_pos < source.length()) {
        char current = source[peek_cursor_pos];
        if(is_escape_character(current)){
            std::cout << "Breaking peek on character: " << current << "\n";
            break;
        }
        else{
            peek_cursor_pos++;
        }
    }

    uint32_t distance = peek_cursor_pos - cursor_start_pos;
    std::cout << "peek returning with length " << distance << " at pos " << peek_cursor_pos << " and distance of " << distance << "\n";
    return distance;
}