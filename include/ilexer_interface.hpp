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
};

class ILexerInterface {
    public:
        virtual ~ILexerInterface() = default;

        virtual LexerData tokenize(const std::string& source) = 0;
};