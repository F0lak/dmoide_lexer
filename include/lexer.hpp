#pragma once
#include <string>
#include <vector>
#include "dm_tokens.hpp"
#include "token_strategies.hpp"

struct CursorCoordinate {
    CursorCoordinate(size_t l, size_t c);
    size_t line;
    size_t column;
};

class Lexer {
    public:
        enum class Context {
            START_OF_FILE,
            LABEL,
            NUMBER,
            NEWLINE,
            END_OF_FILE
        };

        Lexer();
        static Lexer& instance();
        static void initialize();
        void set_source(std::string new_source);
        std::string scan(const std::string& source);
        CursorCoordinate get_cursor_coordinates(int pos);
        void count_lines();

        bool is_line_map_dirty = true;
        std::size_t cursor_pos = 0;
        std::string source; // The string given to the lexer
        std::vector<size_t> line_map;  //list of lines in the file, where the number stored is the cursor position at the beginning of the line.
        std::vector<DMToken> tokens;    // All of the tokens that have been generated
        Context current_context = Context::START_OF_FILE;
        int indents = 0;
        std::string current_dm_path = "";
        static std::array<TokenStrategy*, 5> strategy_lookup;

    private:
        std::string peek(const std::string& source);
        bool is_escape_character(const char character);
};