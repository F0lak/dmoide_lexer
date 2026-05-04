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
        column_index = pos - line_map[line_index - 1];
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

        if(std::isspace(current)) {
            auto* strategy = strategy_lookup[StrategyContext::Whitespace];
            TokenStrategyResult token_result = strategy->run(*this, source, cursor_pos);
            tokens.emplace_back(token_result.token);
            cursor_pos += token_result.characters_consumed;
        }

        else if(std::isalpha(current) || current == '_'){
            auto* strategy = strategy_lookup[StrategyContext::Identifier];
            TokenStrategyResult token_result = strategy->run(*this, source, cursor_pos);
            tokens.emplace_back(token_result.token);
            cursor_pos += token_result.characters_consumed;
        }
        
        else if(DMOperators::is_operator(current)){
            std::cout << "OPERATOR " << current;
            auto* strategy = strategy_lookup[StrategyContext::Operator];
            TokenStrategyResult token_result = strategy->run(*this, source, cursor_pos);
            tokens.emplace_back(token_result.token);
            cursor_pos += token_result.characters_consumed;
        }

        else {
            cursor_pos++;
        }
    }

    CursorCoordinate cursor_coord = get_cursor_coordinates(static_cast<int>(source.length()));
    DMToken eof_token = DMToken(DMToken::TokenType::END_OF_FILE, "EOF", cursor_coord);
    tokens.emplace_back(eof_token);

    for(const auto& t : tokens) {
        result += readable_token(t);
    }
    return result;
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
