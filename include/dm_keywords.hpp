#pragma once
#include <string_view>
#include <unordered_map>
#include "dm_tokens.hpp"

namespace DMKeywords {
    // We use std::string_view as the key for O(1) lookups without copies
inline const std::unordered_map<std::string_view, DMToken::TokenType> mapping = {
    // Control Flow
    {"break",    DMToken::TokenType::KW_BREAK},
    {"continue", DMToken::TokenType::KW_CONTINUE},
    {"return",   DMToken::TokenType::KW_RETURN},
    {"goto",     DMToken::TokenType::KW_GOTO},
    {"if",       DMToken::TokenType::KW_IF},
    {"else",     DMToken::TokenType::KW_ELSE},
    {"switch",   DMToken::TokenType::KW_SWITCH},
    {"case",     DMToken::TokenType::KW_CASE},
    {"default",  DMToken::TokenType::KW_DEFAULT},
    {"for",      DMToken::TokenType::KW_FOR},
    {"while",    DMToken::TokenType::KW_WHILE},
    {"do",       DMToken::TokenType::KW_DO},
    {"to",       DMToken::TokenType::KW_TO},
    {"in",       DMToken::TokenType::KW_IN},
    {"as",       DMToken::TokenType::KW_AS},

    // Variable & Data Management
    {"var",      DMToken::TokenType::KW_VAR},
    {"global",   DMToken::TokenType::KW_GLOBAL},
    {"static",   DMToken::TokenType::KW_STATIC},
    {"tmp",      DMToken::TokenType::KW_TMP},
    {"const",    DMToken::TokenType::KW_CONST},
    {"arg",      DMToken::TokenType::KW_ARG},
    {"new",      DMToken::TokenType::KW_NEW},
    {"del",      DMToken::TokenType::KW_DEL},

    // Functionality & Execution
    {"proc",     DMToken::TokenType::KW_PROC},
    {"verb",     DMToken::TokenType::KW_VERB},
    {"spawn",    DMToken::TokenType::KW_SPAWN},
    {"sleep",    DMToken::TokenType::KW_SLEEP},

    // Error Handling & Safety
    {"try",      DMToken::TokenType::KW_TRY},
    {"catch",    DMToken::TokenType::KW_CATCH},
    {"throw",    DMToken::TokenType::KW_THROW},
    {"final",    DMToken::TokenType::KW_FINAL},

    // Directives & Settings
    {"set",      DMToken::TokenType::KW_SET}
};

    // Returns the TokenType if found, otherwise returns a default (like IDENTIFIER)
    inline DMToken::TokenType get_type(std::string_view word) {
        auto it = mapping.find(word);
        if (it != mapping.end()) {
            return it->second;
        }
        return DMToken::TokenType::IDENTIFIER;
    }

    // Keeping your original boolean check just in case
    inline bool is_keyword(std::string_view word) {
        return mapping.contains(word);
    }
}