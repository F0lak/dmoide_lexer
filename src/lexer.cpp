#include "lexer.hpp"
#include "dm_operators.hpp"
#include <iostream>
#include <array>
#include <format>


CursorCoordinate::CursorCoordinate(size_t l, size_t c)
    : line(static_cast<uint32_t>(l)), column(static_cast<uint32_t>(c))
    {}

Lexer::Lexer() {
}

void Lexer::set_source(std::string_view new_source) {
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

CursorCoordinate Lexer::get_cursor_coordinates(int pos) {
    ZoneScoped;
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

DMToken Lexer::new_token(DMToken::TokenType t, size_t p){
    return DMToken(t, p);
}

LexerData Lexer::tokenize(std::string_view source) {
    ZoneScoped;
    LexerData lex_data;
    std::vector<DMToken> tokens;

    { ZoneScopedN("Startup");
    set_source(source);

    std::cout << "Lexer is scanning string\n";
    std::cout << "String length is: " << source.length() << "\n";
    std::string result = "";

    tokens.reserve(10000);
    }

    while (cursor_pos < source.length()) {
        ZoneScopedN("iteration");
        char current = source[cursor_pos];
        // Escape Character '\'
        if(current == '\\'){
            ZoneScopedN("Escape Character Read");
            if( cursor_pos + 2 < source.length() && 
                source[cursor_pos + 1] == '\r' &&
                source[cursor_pos + 2] == '\n'){
            
                    cursor_pos += 3;
                    continue;
                }
            else {
                cursor_pos++;
            }
        }

        switch(lexer_state.context) {
            case LexerState::Context::StringInline:
                { ZoneScopedN("String Crawl");
                if(current == '['){
                    tokens.emplace_back((DMToken::TokenType::EMBED_OPEN, cursor_pos));
                    lexer_state.push(LexerState::Context::NoContext);
                }
                if(current == '"'){
                    tokens.emplace_back(new_token(DMToken::TokenType::STRING_CLOSE, cursor_pos));
                    lexer_state.pop();
                }
                if(current == '\n'){
                    tokens.emplace_back(new_token(DMToken::TokenType::NEWLINE, cursor_pos));
                    lexer_state.pop();
                }
                cursor_pos++;
                }
                break;

            case LexerState::Context::StringMultiline:
                { ZoneScopedN("String ML Crawl");
                if( current == '"' && cursor_pos+1 < source.size() && source[cursor_pos+1] == '}') {
                    tokens.emplace_back(new_token(DMToken::TokenType::STRING_MULTILINE_CLOSE, cursor_pos));
                    lexer_state.pop();
                    cursor_pos += 2;
                    break;
                }
                if(current == '['){
                    tokens.emplace_back(new_token(DMToken::TokenType::EMBED_OPEN, cursor_pos));
                    lexer_state.push(LexerState::Context::NoContext);
                }
                cursor_pos++;
                }
                break;

            case LexerState::Context::CommentInline:
                { ZoneScopedN("Comment Crawl");
                if(current == '\n'){
                    tokens.emplace_back(new_token(DMToken::TokenType::NEWLINE, cursor_pos));
                    lexer_state.pop();
                }
                cursor_pos++;
                }  
                break;

            case LexerState::Context::CommentMultiline:
                { ZoneScopedN("Comment ML Crawl");
                if( current == '*' && cursor_pos+1 < source.size() && source[cursor_pos+1] == '/') {
                    tokens.emplace_back(new_token(DMToken::TokenType::STRING_MULTILINE_CLOSE, cursor_pos));
                    lexer_state.pop();
                    cursor_pos += 2;
                    break;
                }
                cursor_pos++;
                }
                break;

            case LexerState::Context::Identifier:
                { ZoneScopedN("Identifier");
                if(std::isalnum(current) || current == '_') {
                    cursor_pos++;
                }
                else{
                    lexer_state.pop();
                }
                }
                break;

            default:
            
                // Indentation
                if(indentation.is_at_line_start == true && (current == ' ' || current == '\t')){
                    ZoneScopedN("Indentation");
                    tokens.emplace_back(new_token(DMToken::TokenType::INDENT, cursor_pos));
                    cursor_pos++;
                    continue;
                }

                if(current == '\n'){
                    ZoneScopedN("Newline");
                    tokens.emplace_back(new_token(DMToken::TokenType::NEWLINE, cursor_pos));
                    cursor_pos++;
                    continue;
                }

                // Strings
                if(current == '"'){
                    ZoneScopedN("String Open");
                    tokens.emplace_back(new_token(DMToken::TokenType::STRING_OPEN, cursor_pos));
                    lexer_state.push(LexerState::Context::StringInline);
                    cursor_pos++;
                    continue;
                }

                // Multiline Strings
                if(cursor_pos+1 < source.length()){
                    if( current == '{' && source[cursor_pos+1] == '"' && lexer_state.context == LexerState::Context::NoContext) {
                        ZoneScopedN("MS String Open");
                        tokens.emplace_back(new_token(DMToken::TokenType::STRING_MULTILINE_OPEN, cursor_pos));
                        lexer_state.push(LexerState::Context::StringMultiline);
                        cursor_pos += 2;
                        continue;
                    }
                }

                if(current == ']'){
                    ZoneScopedN("Embed Close");
                    tokens.emplace_back(new_token(DMToken::TokenType::EMBED_CLOSE, cursor_pos));
                    lexer_state.pop();
                    cursor_pos++;
                    continue;
                }

                // Curly Braces
                if(current == '{'){
                    ZoneScopedN("Curly Open");
                    tokens.emplace_back(new_token(DMToken::TokenType::INDENT, cursor_pos));
                    cursor_pos++;
                    continue;
                }

                if(current == '}'){
                    ZoneScopedN("Curly");
                    tokens.emplace_back(new_token(DMToken::TokenType::DEDENT, cursor_pos));
                    cursor_pos++;
                    continue;
                }

                // Identifiers and Keywords
                if(std::isalpha(current) || current == '_'){
                    ZoneScopedN("Identifier");
                    tokens.emplace_back(new_token(DMToken::TokenType::IDENTIFIER, cursor_pos));
                    lexer_state.push(LexerState::Context::Identifier);
                    cursor_pos++;
                    continue;
                }

                // Comments
                if(current == '/' && cursor_pos+1 < source.length()){
                    ZoneScopedN("Comment");
                    char next = source[cursor_pos + 1];
                    if(next == '/'){
                        tokens.emplace_back(new_token(DMToken::TokenType::COMMENT_INLINE, cursor_pos));
                        lexer_state.push(LexerState::Context::CommentInline);
                        cursor_pos+=2;
                        continue;
                    }
                    if(next == '*'){
                        tokens.emplace_back(new_token(DMToken::TokenType::COMMENT_MULTILINE, cursor_pos));
                        lexer_state.push(LexerState::Context::CommentMultiline);
                        cursor_pos+=2;
                        continue;
                    }
                    // single slashes are consumed by the operator check, which MUST follow this
                }

                // Numbers
                if(std::isdigit(current)){
                    ZoneScopedN("Operator Block")
                    uint16_t digit_count = 0;
                    while(cursor_pos+digit_count < source.size() && isdigit(source[cursor_pos+digit_count])){
                        ++digit_count;
                    }
                    tokens.emplace_back(new_token(DMToken::TokenType::NUMBER, cursor_pos));
                    cursor_pos += digit_count;
                    continue;
                }
            
                // Operators
                bool found_op = false;
                { ZoneScopedN("Operator Block");
                size_t remaining = source.size() - cursor_pos;
                const char* src_ptr = &source[cursor_pos];

                for (size_t i = 0; i < std::size(DMOperators::operators); ++i) {
                    size_t op_len = DMOperators::lengths[i]; 
                    
                    if (op_len > remaining) {
                        continue;
                    }

                    if (src_ptr[0] == DMOperators::operators[i][0]) {
                        if (op_len == 1 || std::memcmp(src_ptr, DMOperators::operators[i], op_len) == 0) {
                            tokens.emplace_back(new_token(DMOperators::operator_tokens[i], cursor_pos));
                            cursor_pos += op_len;
                            found_op = true;
                            break;
                        }
                    }
                }
                }

                if (found_op) {
                    continue;
                }

                // Nothing here to tokenize.  Move on with our life.
                else {
                    ZoneScopedN("Nothing Happened");
                    cursor_pos++;
                }
            }
        }

    tokens.emplace_back(DMToken(DMToken::TokenType::END_OF_FILE, cursor_pos)); // register this immediately since it's known to be EOF

    // compile lexer data package
    lex_data.error = LEXError::ErrorCode::LEXError_OK;
    lex_data.data_string = "No Token Data.  Call get_formatted_tokens() to build data string.";
    lex_data.line_count = line_count();
    lex_data.token_count = tokens.size();
    lex_data.tokens = std::move(tokens);

    // clear state for the next run
    indents = 0;
    cursor_pos = 0;
    indentation.clear();
    lexer_state.clear();

    // dispatch lexer data
    return lex_data;
}

uint32_t Lexer::line_count() {
    return line_map.size();
}