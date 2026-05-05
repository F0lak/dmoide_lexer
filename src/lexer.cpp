#include "lexer.hpp"
#include "dm_operators.hpp"
#include <iostream>
#include <array>
#include <format>


CursorCoordinate::CursorCoordinate(size_t l, size_t c)
    : line(static_cast<uint32_t>(l)), column(static_cast<uint32_t>(c))
    {}

Lexer::Lexer() {
    std::cout << "Lexer Constructor\n";
    this->initialize();
    std::cout << "Lexer Initialized\n";
}


void Lexer::set_source(std::string new_source) {
    source = std::move(new_source);
    is_line_map_dirty = true;
    count_lines();
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
    }
    is_line_map_dirty = false;
}

std::unordered_map<Lexer::StrategyContext, TokenStrategy*> Lexer::strategy_lookup;

CursorCoordinate Lexer::get_cursor_coordinates(int pos) {
    auto it = std::upper_bound(line_map.begin(), line_map.end(), pos);
    size_t line_index = std::distance(line_map.begin(), it);
    size_t column_index = pos;
    if(line_index > 0){
        column_index = pos - line_map[line_index - 1] + 1;
    }
    CursorCoordinate coordinates = { line_index, column_index };

  //  std::cout << "Returning Coordinates Struct: line " << line_index << " column " << column_index << "\n";
    return coordinates;
}

std::string Lexer::scan(const std::string& source) {
    std::cout << "Lexer is scanning string\n";
    std::cout << "String length is: " << source.length() << "\n";
    std::cout << "Cursor Pos is: " << cursor_pos << "\n";
    std::string result = "";
    while (cursor_pos < source.length()) {
        char current = source[cursor_pos];

        // Escape Character '\'
        if(current == '\\'){
            if( cursor_pos + 2 < source.length() && 
                source[cursor_pos + 1] == '\r' &&
                source[cursor_pos + 2] == '\n'){
               
                    cursor_pos += 3;
                    continue;
                }

            if( cursor_pos + 1 < source.length() &&
                std::isalpha(source[cursor_pos + 1])){
                    // Will need to change this to Path strategy when that's implemented
                    register_token(StrategyContext::Operator);
                    continue;
                }
            
            CursorCoordinate cursor_coord = get_cursor_coordinates(static_cast<int>(source.length()));
            DMToken error_token = DMToken(DMToken::TokenType::ERROR, "ERROR: Stray \\", cursor_coord);
            tokens.emplace_back(error_token);
            cursor_pos++;
            continue;
        }

        // Whitespace
        if(std::isspace(current)) {
            register_token(StrategyContext::Whitespace);
            continue;
        }

        // Identifiers and Keywords
        if(std::isalpha(current) || current == '_'){
            register_token(StrategyContext::Identifier);
            continue;
        }

        // Comments
        if(current == '/'){
            char next = source[cursor_pos + 1];
            if(next == '/'){
                register_token(StrategyContext::CommentInline);
                continue;
            }
            if(next == '*'){
                register_token(StrategyContext::CommentMultiline);
                continue;
            }
        }
       
        // Operators
        if(DMOperators::is_operator(current)){
            register_token(StrategyContext::Operator);
            continue;
        }

        // Numbers
        if(std::isdigit(current)){
            register_token(StrategyContext::Number);
            continue;
        }

        else {
            cursor_pos++;
        }
    }

    CursorCoordinate cursor_coord = get_cursor_coordinates(static_cast<int>(source.length()));
    DMToken eof_token = DMToken(DMToken::TokenType::END_OF_FILE, "EOF", cursor_coord);
    tokens.emplace_back(eof_token); // register this immediately since it's known to be EOF

    for(const auto& t : tokens) {
        result += readable_token(t);
    }
    return result;
}

// Handles registering tokens to the tokens list and handles special cases (ie: IGNORE)
void Lexer::register_token(StrategyContext strat_context) {
    auto* strategy = strategy_lookup[strat_context];
    TokenStrategyResult result = strategy->run(*this, source, cursor_pos);

    cursor_pos += result.characters_consumed;

    switch(result.token.type) {
        case DMToken::TokenType::IGNORE:
        case DMToken::TokenType::WHITESPACE:
            return;
    }

    tokens.emplace_back(result.token);
}

std::string Lexer::readable_token(DMToken token) {
    if(token.type == DMToken::TokenType::IGNORE){
        return "";
    }
    if(token.type == DMToken::TokenType::NEWLINE){
        return "\n";
    }
    return std::format("[{} L{} C{}]\n", token.value, token.line, token.column);
}
