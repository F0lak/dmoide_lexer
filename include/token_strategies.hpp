#pragma once
#include <string>
#include <optional>
#include "dm_tokens.hpp"
#include "tracy/Tracy.hpp"

class Lexer;

struct TokenStrategyResult {
    TokenStrategyResult(DMToken t, uint32_t d): token(t), characters_consumed(d) {};
    DMToken token;
    int characters_consumed;
};

// The result of scanning within the peek function.
//returns whether or not the scan found a terminator and should therefore end the peek(),
//returning a Token, as well as the steps forward to consume the entire terminator
struct ScanResult {
    ScanResult(bool terminated, int steps_forward) : terminate_scan(terminated), steps(steps_forward) {};
    bool terminate_scan;
    int steps;
};

class ITokenStrategy {
    public:
        virtual ~ITokenStrategy() = default;
        virtual std::string name() const = 0;
        virtual TokenStrategyResult run(int pos) = 0;
};

template <typename Derived>
class TokenStrategy : public ITokenStrategy {
    public:
        TokenStrategy(Lexer& lexer) : lexer(lexer) {};
        virtual ~TokenStrategy() {};
        virtual std::string name() const = 0;
        // Scans over the source beginning at pos
        // Returns a TokenStrategyResult struct which contains the DMToken struct and the number of characters consumed by the token, uncluding its terminator
        virtual TokenStrategyResult run(int pos) = 0;

    protected:
        Lexer& lexer;
        // peek forward in the source string until a designated terminator is found.
        // consumes the entire substring from the given cursor_pos to the end of the terminator
        // returns a uint_32t which is the total distance travelled during the peek
        uint32_t peek(int cursor_pos, std::optional<int> max_steps = std::nullopt) {
            
            int peek_cursor_pos = cursor_pos;
            while(peek_cursor_pos < lexer.source.length()) {
                char current = lexer.source[peek_cursor_pos];
                if(current == '\\'){
                    if( peek_cursor_pos + 2 < lexer.source.length() && 
                        lexer.source[peek_cursor_pos + 1] == '\r' &&
                        lexer.source[peek_cursor_pos + 2] == '\n'){
                    
                            peek_cursor_pos += 3;
                            continue;
                        }
                    else if(peek_cursor_pos + 2 < lexer.source.length()){
                        peek_cursor_pos += 2;
                    }
                }
                
                // static_cast here lets the template use the implementation of the Derived class.
                ScanResult result = static_cast<Derived*>(this)->scan(peek_cursor_pos);
                peek_cursor_pos += result.steps;
                if(result.terminate_scan == true){
                    break;
                }
                else{
                    peek_cursor_pos++;
                }
            }

            uint32_t distance = peek_cursor_pos - cursor_pos;
            return distance;
        }

        TokenStrategyResult result(DMToken::TokenType type, std::string_view value, int pos, int length) {
            return TokenStrategyResult(new_token(type, value, pos), length);
        }

        DMToken new_token(DMToken::TokenType type, std::string_view value, int pos) {
            return DMToken(type, lexer.interner.intern_string(value), lexer.get_cursor_coordinates(pos));
        }
        
        // below are implemented on the derivative classes
};

#define TOKEN_STRATEGY(StratName) \
class StratName : public TokenStrategy<StratName> { \
    public: \
        using TokenStrategy::TokenStrategy; \
        virtual ~StratName() {}; \
        std::string name() const override; \
        TokenStrategyResult run(int pos) override; \
        ScanResult scan(int cursor_pos); \
    private: \
        bool is_escape_character(char c); \
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

class CommentMultilineStrategy : public TokenStrategy<CommentMultilineStrategy> { 
    public: 
        using TokenStrategy<CommentMultilineStrategy>::TokenStrategy;
        virtual ~CommentMultilineStrategy() {};
        std::string name() const override; 
        TokenStrategyResult run(int pos) override; 
        ScanResult scan(int cursor_pos);
    private:
        bool is_escape_character(char c);
        int stack_count = 0;
};

class NumberStrategy : public TokenStrategy<NumberStrategy> { 
    public: 
        using TokenStrategy<NumberStrategy>::TokenStrategy;
        virtual ~NumberStrategy() {};
        std::string name() const override; 
        TokenStrategyResult run(int pos) override; 
        ScanResult scan(int cursor_pos);
    private:
        bool is_escape_character(char c);
        int dot_count = 0;
};