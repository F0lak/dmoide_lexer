
#include <unordered_map>
#include <memory>
#include "lexer.hpp"
#include "token_strategies.hpp"

void Lexer::initialize() {
    // should be clear anyways, but just in case, y'know?    

    // emplace here is better than []= assignment, in that it won't overwrite the values if this is called again for some reason
    strategy_lookup[static_cast<size_t>(StrategyContext::Whitespace)]       = std::make_unique<WhitespaceStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Identifier)]       = std::make_unique<IdentifierStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Default)]          = std::make_unique<PlaceholderStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Whitespace)]       = std::make_unique<WhitespaceStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Identifier)]       = std::make_unique<IdentifierStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Operator)]         = std::make_unique<OperatorStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::CommentInline)]    = std::make_unique<CommentInlineStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::CommentMultiline)] = std::make_unique<CommentMultilineStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Number)]           = std::make_unique<NumberStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Indentation)]      = std::make_unique<IndentationStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::CurlyBrace)]       = std::make_unique<CurlyBraceStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::String)]           = std::make_unique<StringStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::StringMultiLine)]  = std::make_unique<StringMultilineStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::StringEmbed)]      = std::make_unique<StringEmbedStrategy>(*this);
    strategy_lookup[static_cast<size_t>(StrategyContext::Error)]            = std::make_unique<ErrorStrategy>(*this);
}