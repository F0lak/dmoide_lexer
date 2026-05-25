#pragma once
#include <string_view>
#include <unordered_map>
#include "dm_tokens.hpp"

namespace DMOperators {
    inline const std::unordered_map<std::string_view, DMToken::TokenType> mapping = {
        // Arithmetic & Assignment
        {"=",   DMToken::TokenType::OP_ASSIGN_EQUAL},
        {"+=",  DMToken::TokenType::OP_ASSIGN_ADD},
        {"-=",  DMToken::TokenType::OP_ASSIGN_SUBTRACT},
        {"*=",  DMToken::TokenType::OP_ASSIGN_MULTIPLY},
        {"/=",  DMToken::TokenType::OP_ASSIGN_DIVIDE},
        {"%=",  DMToken::TokenType::OP_ASSIGN_MOD},
        {"+",   DMToken::TokenType::OP_ADD},
        {"-",   DMToken::TokenType::OP_SUBTRACT},
        {"*",   DMToken::TokenType::OP_MULTIPLY},
        {"/",   DMToken::TokenType::OP_SLASH}, // Note: Map to OP_SLASH or OP_DIVIDE depending on context
        {"%",   DMToken::TokenType::OP_MOD},
        {"++",  DMToken::TokenType::OP_INCREMENT},
        {"--",  DMToken::TokenType::OP_DECREMENT},

        // Comparison
        {"==",  DMToken::TokenType::OP_EQUAL_TO},
        {"!=",  DMToken::TokenType::OP_NOT_EQUAL},
        {"<>",  DMToken::TokenType::OP_NOT_EQUAL}, // Alias for !=
        {"<",   DMToken::TokenType::OP_LESS_THAN},
        {">",   DMToken::TokenType::OP_GREATER_THAN},
        {"<=",  DMToken::TokenType::OP_LESS_EQUAL},
        {">=",  DMToken::TokenType::OP_GREATER_EQUAL},
        {"<=>", DMToken::TokenType::OP_SORT},

        // Logical & Bitwise
        {"&&",  DMToken::TokenType::OP_BOOLEAN_AND},
        {"||",  DMToken::TokenType::OP_BITWISE_OR}, // Note: Ensure you have OP_BOOLEAN_OR in enum
        {"!",   DMToken::TokenType::OP_BANG},
        {"&",   DMToken::TokenType::OP_BITWISE_AND},
        {"|",   DMToken::TokenType::OP_BITWISE_OR},
        {"^",   DMToken::TokenType::OP_BITWISE_XOR},
        {"~",   DMToken::TokenType::OP_TILDE},
        {"<<",  DMToken::TokenType::OP_BITSHIFT_LEFT},
        {">>",  DMToken::TokenType::OP_BITSHIFT_RIGHT},
        {"&=",  DMToken::TokenType::OP_ASSIGN_BITWISE_AND},
        {"|=",  DMToken::TokenType::OP_ASSIGN_BITWISE_NOT}, // Verify if you want OR here
        {"^=",  DMToken::TokenType::OP_ASSIGN_BITWISE_XOR},
        {"<<=", DMToken::TokenType::OP_ASSIGN_BITSHIFT_LEFT},
        {">>=", DMToken::TokenType::OP_ASSIGN_BITSHIFT_RIGHT},

        // Access & Pathing
        {".",   DMToken::TokenType::OP_DOT_ACCESS},
        {":",   DMToken::TokenType::OP_COLON_ACCESS},
        {"?",   DMToken::TokenType::OP_TERNARY_IF},
        {".?",  DMToken::TokenType::OP_NULL_COND_DOT},
        {"?.",  DMToken::TokenType::OP_NULL_COND_DOT}, // Alias usually handled by lexer
        {"/",   DMToken::TokenType::OP_SLASH},

        // Miscellaneous
        {",",   DMToken::TokenType::SEPARATOR},
        {"[",   DMToken::TokenType::OP_BRACKET_OPEN},
        {"]",   DMToken::TokenType::OP_BRACKET_CLOSE},
        {"(",   DMToken::TokenType::OP_PAREN_OPEN},
        {")",   DMToken::TokenType::OP_PAREN_CLOSE},
        {"{",   DMToken::TokenType::OP_CURLY_OPEN},
        {"}",   DMToken::TokenType::OP_CURLY_CLOSE}
    };

    // Returns the TokenType if found, otherwise returns a default (like IDENTIFIER)
    inline DMToken::TokenType get_type(std::string_view word) {
        auto it = mapping.find(word);
        if (it != mapping.end()) {
            return it->second;
        }
        return DMToken::TokenType::NULL_OP;
    }

    // Keeping your original boolean check just in case
    inline bool is_operator(std::string_view word) {
        ZoneScopedN("is_operator(string)");
        return mapping.contains(word);
    }
    inline bool is_operator(char op) {
        ZoneScopedN("is_operator(char)");
        // Create a temporary view of the single char
        return mapping.find(std::string_view(&op, 1)) != mapping.end();
    }
}