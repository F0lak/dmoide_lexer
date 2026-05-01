#include "lexer.hpp"
#include <iostream>


bool lexer::Lexer::is_escape_character(const char character)
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

std::string lexer::Lexer::peek(const std::string& source) {
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

std::string lexer::Lexer::scan(const std::string &source) {
    std::cout << "Scanning String\n";
    std::string result = "";
    while (cursor_pos < source.length()) {
        char current = source[cursor_pos];

        if(std::isspace(current)) {
            if(current == '\r') {
                current_context = Context::NEWLINE;
                std::string label = peek(source);
                cursor_pos += label.length();
                Token new_token;
                new_token.type = Token::Type::NEWLINE;
                new_token.value = "[NEWLINE]\n";
                tokens.emplace_back(new_token);
            }
            else {
                Token new_token;
                new_token.type = Token::Type::WHITESPACE;
                new_token.value = "[WHITESPACE]";
                tokens.emplace_back(new_token);
            }
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
    return result;
}
