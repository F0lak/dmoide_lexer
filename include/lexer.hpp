#pragma once
#include "ilexer_interface.hpp"
#include "cursor_coordinates.hpp"

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

        LexerData tokenize(const std::string& source) override;

        uint32_t line_count();
        uint32_t strategy_count();

    private:
        void initialize();
        void register_error(std::string message, int pos);
        void set_source(const std::string& new_source);
        CursorCoordinate get_cursor_coordinates(int pos);
        void count_lines();
        void run_strategy(StrategyContext strat_context);
        void register_token(TokenStrategyResult result);
        std::string readable_token(DMToken token);

        IndentationStack indentation = IndentationStack();
        StringStack string_stack = StringStack();
        std::vector<DMToken> tokens;    // All of the tokens that have been generated
        std::vector<size_t> line_map;  //list of lines in the file, where the number stored is the cursor position at the beginning of the line.
        std::unordered_map<StrategyContext, std::unique_ptr<TokenStrategy>> strategy_lookup;
        std::string source; // The string given to the lexer
        std::string current_dm_path = "";
        int indents = 0;
        bool is_line_map_dirty = true;
        std::uint32_t cursor_pos = 0;
};