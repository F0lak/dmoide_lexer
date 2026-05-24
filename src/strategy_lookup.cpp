
#include <unordered_map>
#include <memory>
#include "lexer.hpp"
#include "token_strategies.hpp"

void Lexer::initialize() {
    // should be clear anyways, but just in case, y'know?    

    // emplace here is better than []= assignment, in that it won't overwrite the values if this is called again for some reason
    strategy_lookup[static_cast<size_t>(StrategyContext::Whitespace)]       = WhitespaceStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Identifier)]       = IdentifierStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Default)]          = PlaceholderStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Whitespace)]       = WhitespaceStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Identifier)]       = IdentifierStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Operator)]         = OperatorStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::CommentInline)]    = CommentInlineStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::CommentMultiline)] = CommentMultilineStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Number)]           = NumberStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Indentation)]      = IndentationStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::CurlyBrace)]       = CurlyBraceStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::String)]           = StringStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::StringMultiLine)]  = StringMultilineStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::StringEmbed)]      = StringEmbedStrategy(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Error)]            = ErrorStrategy(*this);
}