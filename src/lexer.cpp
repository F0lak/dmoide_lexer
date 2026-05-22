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

void Lexer::set_source(const std::string& new_source) {
    source = new_source; //std::move(new_source);
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

std::unordered_map<Lexer::StrategyContext, std::unique_ptr<TokenStrategy>> strategy_lookup;

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

std::string Lexer::tokenize(const std::string& source) {
    set_source(source);

    std::cout << "Lexer is scanning string\n";
    std::cout << "String length is: " << source.length() << "\n";
    std::string result = "";
    cursor_pos = 0;
    

    uint32_t last_pos = 42; // We'll start this in a random position to kick start the loop.
    while (cursor_pos < source.length()) {
    /*
        if(cursor_pos == last_pos){
            throw std::runtime_error("Lexer stuck at position " + std::to_string(cursor_pos));
            //register_error("Internal Lexer Error: Stuck", cursor_pos);
            cursor_pos++;
        }
        last_pos = cursor_pos;
        */
        char current = source[cursor_pos];

        if (cursor_pos == 0) {
        std::cout << "LEXER INTERNAL CHECK AT 0: '" << current << "' (ASCII: " << (int)current << ")\n";
        }

        std::string fstring = std::format("Cursor Pos is: {} | '{}'.\n", cursor_pos, current);

        // Escape Character '\'
        if(current == '\\'){
            std::cout << "[" << __FILE__ << ":" << __LINE__ << " in " << __func__ << "] Debug trace.\n";
            if( cursor_pos + 2 < source.length() && 
                source[cursor_pos + 1] == '\r' &&
                source[cursor_pos + 2] == '\n'){
               
                    cursor_pos += 3;
                    continue;
                }

            if( cursor_pos + 1 < source.length() &&
                std::isalpha(source[cursor_pos + 1])){
                    // Will need to change this to Path strategy when that's implemented
                    run_strategy(StrategyContext::Operator);
                    continue;
                }
            
            CursorCoordinate cursor_coord = get_cursor_coordinates(static_cast<int>(source.length()));
            DMToken error_token = DMToken(DMToken::TokenType::TOKEN_ERROR, "ERROR: Stray \\", cursor_coord);
            tokens.emplace_back(error_token);
            cursor_pos++;
            continue;
        }

        // Indentation
        if(indentation.is_at_line_start == true && (current == ' ' || current == '\t')){
            std::cout << "[" << __FILE__ << ":" << __LINE__ << " in " << __func__ << "] Debug trace.\n";
            run_strategy(StrategyContext::Indentation);
            continue;
        }

        // Multiline Strings
        if(cursor_pos+1 < source.length() && current == '{' && source[cursor_pos+1] == '"'){
            std::cout << "[" << __FILE__ << ":" << __LINE__ << " in " << __func__ << "] Debug trace.\n";
            run_strategy(StrategyContext::StringMultiLine);
            continue;
        }

        // Strings
        if(current == '"'){
            run_strategy(StrategyContext::String);
            std::cout << "[" << __FILE__ << ":" << __LINE__ << " in " << __func__ << "] Debug trace.\n";
            continue;
        }
        if(string_stack.depth > 0 && current == ']'){
            std::cout << "[" << __FILE__ << ":" << __LINE__ << " in " << __func__ << "] Debug trace.\n";
            run_strategy(StrategyContext::StringEmbed);
            switch(string_stack.context){
                case StringStack::Context::Inline:
                    run_strategy(StrategyContext::String);
                    break;
                case StringStack::Context::Multiline:
                    run_strategy(StrategyContext::StringMultiLine);
                    break;
                default:
                    register_error("sting_stack has No Context: " + std::to_string(static_cast<int>(string_stack.context)), cursor_pos);
                    break;
            }
            if(string_stack.depth == 0){
                string_stack.context = StringStack::Context::NoContext;
                }
            continue;
        }

        // Curly Braces
        if((current == '{' || current == '}')){
            std::cout << "[" << __FILE__ << ":" << __LINE__ << " in " << __func__ << "] Debug trace.\n";
            run_strategy(StrategyContext::CurlyBrace);
            continue;
        }

        // Whitespace
        if(std::isspace(current)) {
            std::cout << "[" << __FILE__ << ":" << __LINE__ << " in " << __func__ << "] Debug trace.\n";
            run_strategy(StrategyContext::Whitespace);
            continue;
        }

        // Identifiers and Keywords
        if(std::isalpha(current) || current == '_'){
            std::cout << "[" << __FILE__ << ":" << __LINE__ << " in " << __func__ << "] Debug trace.\n";
            run_strategy(StrategyContext::Identifier);
            continue;
        }

        // Comments
        if(current == '/'){
            std::cout << "[" << __FILE__ << ":" << __LINE__ << " in " << __func__ << "] Debug trace.\n";
            char next = source[cursor_pos + 1];
            if(next == '/'){
                run_strategy(StrategyContext::CommentInline);
                continue;
            }
            if(next == '*'){
                run_strategy(StrategyContext::CommentMultiline);
                continue;
            }
        }
       
        // Operators
        if(DMOperators::is_operator(current)){
            std::cout << "[" << __FILE__ << ":" << __LINE__ << " in " << __func__ << "] Debug trace.\n";
            run_strategy(StrategyContext::Operator);
            continue;
        }

        // Numbers
        if(std::isdigit(current)){
            std::cout << "[" << __FILE__ << ":" << __LINE__ << " in " << __func__ << "] Debug trace.\n";
            run_strategy(StrategyContext::Number);
            continue;
        }

        // Nothing here to tokenize.  Move on with our life.
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

// Runs a strategy for the given context
void Lexer::run_strategy(StrategyContext strat_context){
    TokenStrategy* strategy = strategy_lookup[strat_context].get();
    TokenStrategyResult result = strategy->run(cursor_pos);
    register_token(result);
}

// Handles registering tokens to the tokens list and handles special cases (ie: TOKEN_IGNORE)
void Lexer::register_token(TokenStrategyResult result) {
    std::string msg = std::format("Token Type {}, Characters Consumed {}\n", static_cast<int>(result.token.type), result.characters_consumed);
    std::cout << msg;
    cursor_pos += result.characters_consumed;

    switch(result.token.type) {
        case DMToken::TokenType::TOKEN_IGNORE:
            return;

        case DMToken::TokenType::TOKEN_WHITESPACE:
            if(indentation.is_at_line_start == true){
                result.token.type = DMToken::TokenType::INDENT;
            }
            break;

        case DMToken::TokenType::INDENT:
        case DMToken::TokenType::DEDENT:
            break;

        case DMToken::TokenType::EMBED_OPEN:
            string_stack.depth++;
            break;
        case DMToken::TokenType::EMBED_CLOSE:
            string_stack.depth--;
            break;
            
        case DMToken::TokenType::NEWLINE:
            indentation.is_at_line_start = true;
            break;

        default:
            indentation.is_at_line_start = false;
    }

    tokens.emplace_back(result.token);
}

std::string Lexer::readable_token(DMToken token) {
    if(token.type == DMToken::TokenType::TOKEN_IGNORE){
        return "";
    }

    std::string result = std::format("[{} L{} C{}]\n", token.value, token.line, token.column);
    
  //  std::cout << result;
    //std::cin.get();
    return result;
}

void Lexer::register_error(std::string message, int pos){
    CursorCoordinate coords = get_cursor_coordinates(pos);
    DMToken new_token = DMToken(DMToken::TokenType::TOKEN_ERROR, "TOKEN_ERROR: " + message, coords);
    tokens.emplace_back(new_token);
    cursor_pos++;
}
