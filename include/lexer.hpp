#pragma once
#include "ilexer_interface.hpp"
#include "cursor_coordinates.hpp"

struct IndentationStack {
    bool is_at_line_start = false;
    int current_count = 0;
    int last_line_count = 0;

    void clear() {
        is_at_line_start = false;
        current_count = 0;
        last_line_count = 0;
    }
};

struct StringStack {
    enum class Context {
        NoContext,
        Inline,
        Multiline
    };
    Context context = Context::NoContext;
    int depth = 0;

    void clear() {
        context = Context::NoContext;
        depth = 0;
    }
};

class Lexer : public ILexerInterface {
    friend class TokenStrategy;
    friend class PlaceholderStrategy;
    friend class WhitespaceStrategy;
    friend class IdentifierStrategy;
    friend class OperatorStrategy;
    friend class CommentInlineStrategy;
    friend class IndentationStrategy;
    friend class CurlyBraceStrategy;
    friend class StringStrategy;
    friend class StringMultilineStrategy;
    friend class StringEmbedStrategy;
    friend class ErrorStrategy;
    friend class CommentMultilineStrategy;
    friend class NumberStrategy;
    friend struct TokenStrategyResult;

    public:
        enum class StrategyContext {
            Default,
            Whitespace,
            Identifier,
            Operator,
            CommentInline,
            CommentMultiline,
            Number,
            Indentation,
            CurlyBrace,
            String,
            StringMultiLine,
            StringEmbed,
            Error
        };

        Lexer();

        LexerData tokenize(std::string_view source) override;

        uint32_t line_count();
        uint32_t strategy_count();

    private:
        void initialize();
        void register_error(std::string message, int pos);
        void set_source(std::string_view new_source);
        CursorCoordinate get_cursor_coordinates(int pos);
        void count_lines();
        void run_strategy(StrategyContext strat_context);
        void register_token(TokenStrategyResult result);
        std::string readable_token(DMToken token);
        
        std::unordered_map<StrategyContext, std::unique_ptr<TokenStrategy>> strategy_lookup;

        // these are reset every time tokenize() is ran
        std::string_view source; // The string given to the lexer
        IndentationStack indentation = IndentationStack();
        StringStack string_stack = StringStack();
        std::vector<DMToken> tokens;    // All of the tokens that have been generated
        std::vector<size_t> line_map;  //list of lines in the file, where the number stored is the cursor position at the beginning of the line.
        int indents = 0;
        bool is_line_map_dirty = true;
        std::uint32_t cursor_pos = 0;
};