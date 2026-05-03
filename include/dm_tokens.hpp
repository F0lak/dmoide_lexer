#pragma once
#include <string>


struct DMToken {
    public:
    
        enum class TokenType : uint16_t {
            PLACEHOLDER,
            
            LABEL,
            NUMBER,
            WHITESPACE,
            NEWLINE,
            SEPARATOR, // (as in a comma)  But commas and semicolons can be interchangable given the context (ie for())

            INDENT,
            DEDENT,

            // TODO: Sort these based on order of operations as defined in: https://www.byond.com/docs/ref/#/operator
            OP_DOT_PATH,
            OP_COLON_PATH,
            OP_SLASH,
            OP_COLON_COLON, // this has multiple uses, will probably split into several tokens later
            OP_DOT_ACCESS,
            OP_COLON_ACCESS,
            OP_INDEX_ACCESS,
            OP_NULL_COND_DOT,
            OP_NULL_COND_COLON,
            OP_NULL_COND_INDEX,
            OP_TILDE,
            OP_BANG,
            OP_MINUS,
            OP_INCREMENT,
            OP_DECREMENT,
            OP_POINTER_STAR,
            OP_POINTER_AMP,
            OP_EXPONENT,
            OP_MULTIPLY,
            OP_DIVIDE,
            OP_MOD,
            OP_MOD_FLOAT,
            OP_ADD,
            OP_SUBTRACT,
            OP_GREATER_THAN,
            OP_GREATER_EQUAL,
            OP_LESS_THAN,
            OP_LESS_EQUAL,
            OP_SORT,        // <=> https://www.byond.com/docs/ref/#/operator/%3c=%3e
            OP_OUTPUT,
            OP_BITSHIFT_LEFT,
            OP_OUTPUT_SAVEFILE,
            OP_INPUT,
            OP_BITSHIFT_RIGHT,
            OP_INPUT_SAVEFILE,
            OP_EQUAL_TO,
            OP_NOT_EQUAL, // != and <> are the same
            OP_EQUIVALENT_TO,
            OP_NOT_EQUIVALENT,

            OP_BITWISE_AND,
            OP_BITWISE_XOR,
            OP_BITWISE_NOT,
            OP_BITWISE_OR,
            OP_BOOLEAN_AND,
            OP_BOOLEAN_NOT,
            OP_TERNARY_IF,
            OP_TERNARY_ELSE,

            OP_ASSIGN_EQUAL,
            OP_ASSIGN_ADD,
            OP_ASSIGN_SUBTRACT,
            OP_ASSIGN_MULTIPLY,
            OP_ASSIGN_DIVIDE,
            OP_ASSIGN_MOD,
            OP_ASSIGN_MOD_FLOAT,
            OP_ASSIGN_BITWISE_AND,
            OP_ASSIGN_BITWISE_NOT,
            OP_ASSIGN_BITWISE_XOR,
            OP_ASSIGN_BITSHIFT_LEFT,
            OP_ASSIGN_BITSHIFT_RIGHT,
            OP_ASSIGN_INTO,
            OP_ASSIGN_BOOL_AND_INTO,
            OP_ASSIGN_BOOL_OR_INTO,

            };

        TokenType type;
        std::string value;
    };

struct DMTokenPlaceholder : public DMToken {};