#pragma once
#include "ilexer_interface.hpp"
#include "tracy/Tracy.hpp"

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

struct LexerState {
    enum class Context {
        NoContext,
        Identifier,
        StringInline,
        StringMultiline,
        CommentInline,
        CommentMultiline,
        Operator,
        Whitespace
    };
    Context context = Context::NoContext;
    int depth = 0;
    std::vector<Context> stack;
    int start_pos = 0;

    size_t size() {
        return stack.size();
    }

    void push(Context c){
        stack.push_back(c);
        context = c;
    }

    void pop(){
        if(!stack.empty()){
            stack.pop_back();
        }
        if(!stack.empty()){
            context = stack.back();
        }
        else{
            context = Context::NoContext;
        }
    }

    void clear() {
        context = Context::NoContext;
        depth = 0;
    }
};

class Lexer : public ILexerInterface {

    public:
        Lexer();

        LexerData tokenize(std::string_view source) override;

        uint32_t line_count();

    private:
        void set_source(std::string_view new_source);
        CursorCoordinate get_cursor_coordinates(int pos);
        void count_lines();
        DMToken new_token(DMToken::TokenType t, uint32_t p, uint8_t l);

        // these are reset every time tokenize() is ran
        std::string_view source; // The string given to the lexer
        IndentationStack indentation = IndentationStack();
        LexerState lexer_state = LexerState();
        std::vector<size_t> line_map;  //list of lines in the file, where the number stored is the cursor position at the beginning of the line.
        int indents = 0;
        bool is_line_map_dirty = true;
        std::uint32_t cursor_pos = 0;
};