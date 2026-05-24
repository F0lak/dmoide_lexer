#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "dm_tokens.hpp"
#include "token_strategies.hpp"
#include "lex_errors.hpp"

struct LexerData {
    std::string data_string = "";
    LEXError::ErrorCode error;
    int line_count = 0;
    int token_count = 0;
};

class ILexerInterface {
    public:
        virtual ~ILexerInterface() = default;

        virtual LexerData tokenize(std::string_view source) = 0;
        virtual std::string get_formatted_tokens() = 0;

        virtual uint32_t get_token_value_count() = 0;
};