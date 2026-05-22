#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "dm_tokens.hpp"
#include "token_strategies.hpp"
#include "lex_errors.hpp"

struct IndentationStack {
    bool is_at_line_start;
    int current_count = 0;
    int last_line_count = 0;
};

struct StringStack {
    enum class Context {
        NoContext,
        Inline,
        Multiline
    };
    Context context = Context::NoContext;
    int depth = 0;
};

struct LexerData {
    std::string data_string = "";
    LEXError::ErrorCode error;
};

class ILexerInterface {
    public:
        virtual ~ILexerInterface() = default;

        virtual LexerData tokenize(const std::string& source) = 0;
};