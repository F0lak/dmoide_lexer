#pragma once
#include <string>
#include <optional>
#include "dm_tokens.hpp"

class Lexer;

struct TokenStrategyResult {
    TokenStrategyResult(DMToken t, uint32_t d);
    DMToken token;
    int characters_consumed;
};

struct ScanResult {
    ScanResult(bool terminated, int steps_forward);
    bool terminate_scan;
    int steps;
};

class TokenStrategy {
    public:
        virtual std::string name() const = 0;
        virtual TokenStrategyResult run(Lexer& lexer, const std::string& source, int pos) = 0;
        virtual ~TokenStrategy() = default;
    protected:
        uint32_t peek(const std::string& source, int cursor_pos, std::optional<int> max_steps = std::nullopt);
        virtual bool is_escape_character(char c) = 0;
        virtual ScanResult scan(const std::string& source, int cursor_pos) = 0;
};

#define TOKEN_STRATEGY(StratName) \
class StratName : public TokenStrategy { \
    public: \
        std::string name() const override; \
        static StratName* instance(); \
        TokenStrategyResult run(Lexer& lexer, const std::string& source, int pos) override; \
    protected: \
        bool is_escape_character(char c) override;\
        ScanResult scan(const std::string& source, int cursor_pos) override;\
};

TOKEN_STRATEGY(PlaceholderStrategy)
TOKEN_STRATEGY(WhitespaceStrategy)
TOKEN_STRATEGY(IdentifierStrategy)
TOKEN_STRATEGY(OperatorStrategy)
TOKEN_STRATEGY(CommentInlineStrategy)

class CommentMultilineStrategy : public TokenStrategy { 
    public: 
        std::string name() const override; 
        static CommentMultilineStrategy* instance(); 
        TokenStrategyResult run(Lexer& lexer, const std::string& source, int pos) override; 
    protected: 
        bool is_escape_character(char c) override;
        ScanResult scan(const std::string& source, int cursor_pos) override;
    private:
        int stack_count = 0;
};

class NumberStrategy : public TokenStrategy { 
    public: 
        std::string name() const override; 
        static NumberStrategy* instance(); 
        TokenStrategyResult run(Lexer& lexer, const std::string& source, int pos) override; 
    protected: 
        bool is_escape_character(char c) override;
        ScanResult scan(const std::string& source, int cursor_pos) override;
    private:
        int dot_count = 0;
};