#pragma once
#include <string>
#include "cursor_coordinates.hpp"

#define TOKEN_LIST(X) \
    X(PLACEHOLDER)             \
    X(END_OF_FILE)             \
    X(TOKEN_ERROR)             \
    X(TOKEN_IGNORE)            \
    X(TOKEN_WHITESPACE)        \
    X(COMMENT_INLINE)          \
    X(COMMENT_MULTILINE)       \
    X(STRING)                  \
    X(STRING_MULTILINE)        \
    X(NUMBER)                  \
    X(IDENTIFIER)              \
    X(NEWLINE)                 \
    X(SEPARATOR)               \
    X(INDENT)                  \
    X(DEDENT)                  \
    X(EMBED_OPEN)              \
    X(EMBED_CLOSE)             \
    X(NULL_OP)                 \
    X(OP_DOT_PATH)             \
    X(OP_COLON_PATH)           \
    X(OP_SLASH)                \
    X(OP_COLON_COLON)          \
    X(OP_DOT_ACCESS)           \
    X(OP_COLON_ACCESS)         \
    X(OP_NULL_COND_DOT)        \
    X(OP_NULL_COND_COLON)      \
    X(OP_NULL_COND_INDEX)      \
    X(OP_TILDE)                \
    X(OP_BANG)                 \
    X(OP_MINUS)                \
    X(OP_INCREMENT)            \
    X(OP_DECREMENT)            \
    X(OP_POINTER_STAR)         \
    X(OP_POINTER_AMP)          \
    X(OP_EXPONENT)             \
    X(OP_MULTIPLY)             \
    X(OP_DIVIDE)               \
    X(OP_MOD)                  \
    X(OP_MOD_FLOAT)            \
    X(OP_ADD)                  \
    X(OP_SUBTRACT)             \
    X(OP_GREATER_THAN)         \
    X(OP_GREATER_EQUAL)        \
    X(OP_LESS_THAN)            \
    X(OP_LESS_EQUAL)           \
    X(OP_SORT)                 \
    X(OP_OUTPUT)               \
    X(OP_BITSHIFT_LEFT)        \
    X(OP_OUTPUT_SAVEFILE)      \
    X(OP_INPUT)                \
    X(OP_BITSHIFT_RIGHT)       \
    X(OP_INPUT_SAVEFILE)       \
    X(OP_EQUAL_TO)             \
    X(OP_NOT_EQUAL)            \
    X(OP_EQUIVALENT_TO)        \
    X(OP_NOT_EQUIVALENT)       \
    X(OP_BITWISE_AND)          \
    X(OP_BITWISE_XOR)          \
    X(OP_BITWISE_NOT)          \
    X(OP_BITWISE_OR)           \
    X(OP_BOOLEAN_AND)          \
    X(OP_BOOLEAN_NOT)          \
    X(OP_TERNARY_IF)           \
    X(OP_TERNARY_ELSE)         \
    X(OP_ASSIGN_EQUAL)         \
    X(OP_ASSIGN_ADD)           \
    X(OP_ASSIGN_SUBTRACT)      \
    X(OP_ASSIGN_MULTIPLY)      \
    X(OP_ASSIGN_DIVIDE)        \
    X(OP_ASSIGN_MOD)           \
    X(OP_ASSIGN_MOD_FLOAT)     \
    X(OP_ASSIGN_BITWISE_AND)   \
    X(OP_ASSIGN_BITWISE_NOT)   \
    X(OP_ASSIGN_BITWISE_XOR)   \
    X(OP_ASSIGN_BITSHIFT_LEFT) \
    X(OP_ASSIGN_BITSHIFT_RIGHT)\
    X(OP_ASSIGN_INTO)          \
    X(OP_ASSIGN_BOOL_AND_INTO) \
    X(OP_ASSIGN_BOOL_OR_INTO)  \
    X(OP_BRACKET_OPEN)         \
    X(OP_BRACKET_CLOSE)        \
    X(OP_PAREN_OPEN)           \
    X(OP_PAREN_CLOSE)          \
    X(OP_CURLY_OPEN)           \
    X(OP_CURLY_CLOSE)          \
    X(KW_BREAK)                \
    X(KW_CONTINUE)             \
    X(KW_RETURN)               \
    X(KW_GOTO)                 \
    X(KW_IF)                   \
    X(KW_ELSE)                 \
    X(KW_SWITCH)               \
    X(KW_CASE)                 \
    X(KW_DEFAULT)              \
    X(KW_FOR)                  \
    X(KW_WHILE)                \
    X(KW_DO)                   \
    X(KW_TO)                   \
    X(KW_IN)                   \
    X(KW_AS)                   \
    X(KW_VAR)                  \
    X(KW_GLOBAL)               \
    X(KW_STATIC)               \
    X(KW_TMP)                  \
    X(KW_CONST)                \
    X(KW_ARG)                  \
    X(KW_NEW)                  \
    X(KW_DEL)                  \
    X(KW_PROC)                 \
    X(KW_VERB)                 \
    X(KW_SPAWN)                \
    X(KW_SLEEP)                \
    X(KW_TRY)                  \
    X(KW_CATCH)                \
    X(KW_THROW)                \
    X(KW_FINAL)                \
    X(KW_SET)


struct DMToken {
    public:
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

        DMToken(CursorCoordinate c);
        DMToken( DMToken::TokenType t, uint32_t v,  CursorCoordinate c);

        DMToken::TokenType type;
        uint32_t value_index;
        uint16_t line;
        uint16_t column;

        std::string_view get_name();
    };