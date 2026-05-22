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

// The result of scanning within the peek function.
//returns whether or not the scan found a terminator and should therefore end the peek(),
//returning a Token, as well as the steps forward to consume the entire terminator
struct ScanResult {
    ScanResult(bool terminated, int steps_forward);
    bool terminate_scan;
    int steps;
};

class TokenStrategy {
    public:
        TokenStrategy(Lexer& lexer);
        virtual ~TokenStrategy() = default;
        virtual std::string name() const = 0;
        // Scans over the source beginning at pos
        // Returns a TokenStrategyResult struct which contains the DMToken struct and the number of characters consumed by the token, uncluding its terminator
        virtual TokenStrategyResult run(int pos) = 0;
    protected:
        Lexer& lexer;
        // peek forward in the source string until a designated terminator is found.
        // consumes the entire substring from the given cursor_pos to the end of the terminator
        // returns a uint_32t which is the total distance travelled during the peek
        uint32_t peek(int cursor_pos, std::optional<int> max_steps = std::nullopt);
        virtual bool is_escape_character(char c) = 0;
        // Scans on and sometimes around the source string at the given cursor position.
        // Returns a ScanResult that determines whether the peek() function should end and how far fowrard to
        // step the cursor in order to tokenize the terminator properly
        virtual ScanResult scan(int cursor_pos) = 0;
        TokenStrategyResult result(DMToken::TokenType type, std::string_view value, int pos, int length);
};

#define TOKEN_STRATEGY(StratName) \
class StratName : public TokenStrategy { \
    public: \
        using TokenStrategy::TokenStrategy; \
        std::string name() const override; \
        TokenStrategyResult run(int pos) override; \
    protected: \
        bool is_escape_character(char c) override;\
        ScanResult scan(int cursor_pos) override;\
};

TOKEN_STRATEGY(PlaceholderStrategy)
TOKEN_STRATEGY(WhitespaceStrategy)
TOKEN_STRATEGY(IdentifierStrategy)
TOKEN_STRATEGY(OperatorStrategy)
TOKEN_STRATEGY(CommentInlineStrategy)
TOKEN_STRATEGY(IndentationStrategy)
TOKEN_STRATEGY(CurlyBraceStrategy)
TOKEN_STRATEGY(StringStrategy)
TOKEN_STRATEGY(StringMultilineStrategy)
TOKEN_STRATEGY(StringEmbedStrategy)
TOKEN_STRATEGY(ErrorStrategy)

#undef TOKEN_STRATEGY

class CommentMultilineStrategy : public TokenStrategy { 
    public: 
        using TokenStrategy::TokenStrategy;
        std::string name() const override; 
        TokenStrategyResult run(int pos) override; 
    protected: 
        bool is_escape_character(char c) override;
        ScanResult scan(int cursor_pos) override;
    private:
        int stack_count = 0;
};

class NumberStrategy : public TokenStrategy { 
    public: 
        using TokenStrategy::TokenStrategy;
        std::string name() const override; 
        TokenStrategyResult run(int pos) override; 
    protected: 
        bool is_escape_character(char c) override;
        ScanResult scan(int cursor_pos) override;
    private:
        int dot_count = 0;
};