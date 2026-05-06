#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include "dm_tokens.hpp"
#include "token_strategies.hpp"
#include "cursor_coordinates.hpp"

struct IndentationStack {
    bool is_at_line_start;
    int current_count = 0;
    int last_line_count = 0;
};

class Lexer {
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
            CurlyBrace
        };

        Lexer();
        static Lexer& instance();
        void initialize();
        void set_source(std::string new_source);
        std::string scan(const std::string& source);
        CursorCoordinate get_cursor_coordinates(int pos);
        void count_lines();
        void register_token(StrategyContext strat_context);
        std::string readable_token(DMToken token);

        IndentationStack indentation = IndentationStack();
        bool is_line_map_dirty = true;
        std::uint32_t cursor_pos = 0;
        std::string source; // The string given to the lexer
        std::vector<size_t> line_map;  //list of lines in the file, where the number stored is the cursor position at the beginning of the line.
        std::vector<DMToken> tokens;    // All of the tokens that have been generated
        int indents = 0;
        std::string current_dm_path = "";
        std::unordered_map<StrategyContext, std::unique_ptr<TokenStrategy>> strategy_lookup;
};