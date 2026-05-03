#include "lexer.hpp"
#include <iostream>
#include <array>

std::array<TokenStrategy*, 5> Lexer::strategy_lookup;

CursorCoordinate::CursorCoordinate(size_t l, size_t c) : line(l), column(c) {}

Lexer::Lexer() {
    std::cout << "Lexer Constructor\n";
    this->initialize();
    std::cout << "Lexer Initialized\n";
}

void Lexer::initialize() {
    strategy_lookup.fill(PlaceholderStrategy::instance());
}

void Lexer::set_source(std::string new_source) {
    source = std::move(new_source);
    is_line_map_dirty = true;
}

void Lexer::count_lines() {
    line_map.clear();
    line_map.push_back(0);

    // scan the source text
    for(int scan_pos = 0; scan_pos < source.size(); ++scan_pos) {

        // line break found
        if(source[scan_pos] == '\n') {
            line_map.push_back(scan_pos + 1);
        }

        // special character found (in this case 'z', for the test case.)
        else if (source[scan_pos] == 'z') {
            CursorCoordinate coordinate = get_cursor_coordinates(scan_pos + 1);
            std::cout << "Character z found at line " << coordinate.line << " column: " << coordinate.column << "\n";
        }
    }
    is_line_map_dirty = false;
}

CursorCoordinate Lexer::get_cursor_coordinates(int pos) {
  //  if(is_line_map_dirty) {
    //    count_lines();
    //}
    auto it = std::upper_bound(line_map.begin(), line_map.end(), pos);

    size_t line_index = std::distance(line_map.begin(), it);
    size_t column_index = pos - line_map[line_index - 1];

    CursorCoordinate coordinates = { line_index, column_index };
    return coordinates;
}

bool Lexer::is_escape_character(const char character)
{
    switch(current_context){
        case Context::LABEL :
            if(std::isspace(character)){
                return true;
            }
            if(std::ispunct(character)){
                if(character == '_'){
                    return false;
                }
                return true;
            }
            return false;

        case Context::NEWLINE :
            if(character == '\r'){
                return false;
            }
            if(character == '\n'){
                return true;
            }
            return true;

        case Context::NUMBER :
            if(std::isdigit(character)){
                return false;
            }
            if(character == '.'){
                return false;
            }
            return true;
            
    }
    return true;
}

std::string Lexer::peek(const std::string& source) {
    std::string peeked_value = "";
    size_t peek_cursor_pos = cursor_pos;
    while(peek_cursor_pos < source.length()) {
        char current = source[peek_cursor_pos];
        if(is_escape_character(current)){
            std::cout << "Breaking peek on character: " << current << "\n";
            break;
        }
        else{
            peeked_value += source[peek_cursor_pos];
            peek_cursor_pos++;
        }
    }
    std::cout << "returning peek: " << peeked_value << "\n";
    return peeked_value;
}

std::string Lexer::scan(const std::string& source) {
    std::cout << "Scanning String\n";
    std::string result = "";
    /*
    while (cursor_pos < source.length()) {
        char current = source[cursor_pos];

        if(std::isspace(current)) {
        }

        if(std::isalpha(current)) {
            current_context = Context::LABEL;
            std::string label = peek(source);
            cursor_pos += label.length();
            Token new_token;
            new_token.type = Token::Type::LABEL;
            new_token.value = "[LABEL " + label + "]";
            tokens.emplace_back(new_token);
        }

        if(std::isdigit(current)){
            current_context = Context::NUMBER;
            std::string label = peek(source);
            cursor_pos += label.length();
            Token new_token;
            new_token.type = Token::Type::NUMBER;
            new_token.value = "[NUMBER " + label + "]";
            tokens.emplace_back(new_token);
        }
        else {
          cursor_pos++;
        }
    }

    for(const auto& t : tokens) {
        result += t.value;
    }
        */
    return result;
}
