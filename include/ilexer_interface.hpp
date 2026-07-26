#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "dm_tokens.hpp"
#include "lex_errors.hpp"

struct LexerData {
    std::vector<DMToken> tokens;
    std::string data_string = "";
    LEXError::ErrorCode error;
    size_t line_count = 0;
    size_t token_count = 0;
};

class ILexerInterface {
    public:
        virtual ~ILexerInterface() = default;

        virtual LexerData tokenize(std::string_view source) = 0;
};