#pragma once
#include <string>
#include "cursor_coordinates.hpp"

#define TOKEN_LIST(X, Y) \
    X(PLACEHOLDER,  None)             \
    X(END_OF_FILE, None)             \
    X(ERROR, None)                   \
    X(IGNORE, None)                  \
    X(WHITESPACE, None)              \
    X(COMMENT_INLINE, Comment)          \
    X(COMMENT_MULTILINE, Comment)       \
    X(STRING_OPEN, String)             \
    X(STRING_CLOSE, String)            \
    X(STRING_MULTILINE_OPEN, String)   \
    X(STRING_MULTILINE_CLOSE, String)  \
    X(NUMBER, Number)                  \
    X(IDENTIFIER, Identifier)              \
    X(NEWLINE, Newline)                 \
    X(SEPARATOR, None)               \
    X(INDENT, None)                  \
    X(DEDENT, None)                  \
    X(EMBED_OPEN, None)              \
    X(EMBED_CLOSE, None)             \
    X(NULL_OP, Operator)                 \
    X(OP_DOT_PATH, Operator)             \
    X(OP_COLON_PATH, Operator)           \
    X(OP_SLASH, Operator)                \
    X(OP_COLON_COLON, Operator)          \
    X(OP_DOT_ACCESS, Operator)           \
    X(OP_COLON_ACCESS, Operator)         \
    X(OP_NULL_COND_DOT, Operator)        \
    X(OP_NULL_COND_COLON, Operator)      \
    X(OP_NULL_COND_INDEX, Operator)      \
    X(OP_TILDE, Operator)                \
    X(OP_BANG, Operator)                 \
    X(OP_MINUS, Operator)                \
    X(OP_INCREMENT, Operator)            \
    X(OP_DECREMENT, Operator)            \
    X(OP_POINTER_STAR, Operator)         \
    X(OP_POINTER_AMP, Operator)          \
    X(OP_EXPONENT, Operator)             \
    X(OP_MULTIPLY, Operator)             \
    X(OP_DIVIDE, Operator)               \
    X(OP_MOD, Operator)                  \
    X(OP_MOD_FLOAT, Operator)            \
    X(OP_ADD, Operator)                  \
    X(OP_SUBTRACT, Operator)             \
    X(OP_GREATER_THAN, Operator)         \
    X(OP_GREATER_EQUAL, Operator)        \
    X(OP_LESS_THAN, Operator)            \
    X(OP_LESS_EQUAL, Operator)           \
    X(OP_SORT, Operator)                 \
    X(OP_OUTPUT, Operator)               \
    X(OP_BITSHIFT_LEFT, Operator)        \
    X(OP_OUTPUT_SAVEFILE, Operator)      \
    X(OP_INPUT, Operator)                \
    X(OP_BITSHIFT_RIGHT, Operator)       \
    X(OP_INPUT_SAVEFILE, Operator)       \
    X(OP_EQUAL_TO, Operator)             \
    X(OP_NOT_EQUAL, Operator)            \
    X(OP_EQUIVALENT_TO, Operator)        \
    X(OP_NOT_EQUIVALENT, Operator)       \
    X(OP_BITWISE_AND, Operator)          \
    X(OP_BITWISE_XOR, Operator)          \
    X(OP_BITWISE_NOT, Operator)          \
    X(OP_BITWISE_OR, Operator)           \
    X(OP_BOOLEAN_AND, Operator)          \
    X(OP_BOOLEAN_NOT, Operator)          \
    X(OP_TERNARY_IF, Operator)           \
    X(OP_TERNARY_ELSE, Operator)         \
    X(OP_ASSIGN_EQUAL, Operator)         \
    X(OP_ASSIGN_ADD, Operator)           \
    X(OP_ASSIGN_SUBTRACT, Operator)      \
    X(OP_ASSIGN_MULTIPLY, Operator)      \
    X(OP_ASSIGN_DIVIDE, Operator)        \
    X(OP_ASSIGN_MOD, Operator)           \
    X(OP_ASSIGN_MOD_FLOAT, Operator)     \
    X(OP_ASSIGN_BITWISE_AND, Operator)   \
    X(OP_ASSIGN_BITWISE_NOT, Operator)   \
    X(OP_ASSIGN_BITWISE_XOR, Operator)   \
    X(OP_ASSIGN_BITSHIFT_LEFT, Operator) \
    X(OP_ASSIGN_BITSHIFT_RIGHT, Operator)\
    X(OP_ASSIGN_INTO, Operator)          \
    X(OP_ASSIGN_BOOL_AND_INTO, Operator) \
    X(OP_ASSIGN_BOOL_OR_INTO, Operator)  \
    X(OP_BRACKET_OPEN, Operator)         \
    X(OP_BRACKET_CLOSE, Operator)        \
    X(OP_PAREN_OPEN, Operator)           \
    X(OP_PAREN_CLOSE, Operator)          \
    X(OP_CURLY_OPEN, Operator)           \
    X(OP_CURLY_CLOSE, Operator)          \
    X(KW_BREAK, Keyword)                \
    X(KW_CONTINUE, Keyword)             \
    X(KW_RETURN, Keyword)               \
    X(KW_GOTO, Keyword)                 \
    X(KW_IF, Keyword)                   \
    X(KW_ELSE, Keyword)                 \
    X(KW_SWITCH, Keyword)               \
    X(KW_CASE, Keyword)                 \
    X(KW_DEFAULT, Keyword)              \
    X(KW_FOR, Keyword)                  \
    X(KW_WHILE, Keyword)                \
    X(KW_DO, Keyword)                   \
    X(KW_TO, Keyword)                   \
    X(KW_IN, Keyword)                   \
    X(KW_AS, Keyword)                   \
    X(KW_VAR, Keyword)                  \
    X(KW_GLOBAL, Keyword)               \
    X(KW_STATIC, Keyword)               \
    X(KW_TMP, Keyword)                  \
    X(KW_CONST, Keyword)                \
    X(KW_ARG, Keyword)                  \
    X(KW_NEW, Keyword)                  \
    X(KW_DEL, Keyword)                  \
    X(KW_PROC, Keyword)                 \
    X(KW_VERB, Keyword)                 \
    X(KW_SPAWN, Keyword)                \
    X(KW_SLEEP, Keyword)                \
    X(KW_TRY, Keyword)                  \
    X(KW_CATCH, Keyword)                \
    X(KW_THROW, Keyword)                \
    X(KW_FINAL, Keyword)                \
    X(KW_SET, Keyword)


struct DMToken {
    public:
        enum class TokenCategory : uint8_t {
            None,
            Keyword,
            Operator,
            Literal,
            Number,
            Comment,
            String,
            Identifier,
            Newline
        };

        enum class TokenType : uint16_t {
            #define AS_ENUM(name) name,
            TOKEN_LIST(AS_ENUM)
            #undef AS_ENUM
            };

        // Using std::array with std::string_view for a compile-time, zero-allocation table
        static constexpr std::string_view token_names[] = {
            #define AS_STRING(name) #name,
            TOKEN_LIST(AS_STRING)
            #undef AS_STRING
        };

        static constexpr TokenCategory token_classes[] = {
            #define AS_CATEGORY(name, classification) TokenCategory::classification,
            TOKEN_LIST(AS_CATEGORY)
            #undef AS_CATEGORY
        };

        DMToken(uint32_t p);
        DMToken( DMToken::TokenType t, uint32_t p);

        DMToken::TokenType type; // uint16
        DMToken::TokenCategory category;
        uint32_t pos;
    //    uint16_t line;
    //    uint16_t column;

        std::string_view name() const;
    };