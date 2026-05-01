#pragma once
namespace lexer{

void tokenize(); // just here for some testing

class Token {
    public:
        enum class Type {
            IDENTIFIER,
            STRING_LITERAL,
            OPERATOR_ADDITION
        };
        
        Type type;
        std::string value;
};

class Lexer {
    enum Context {
        FUNCTION,
        END_OF_FILE
    };

    public:
        int indents = 0;

};

}