
#include <unordered_map>
#include <memory>
#include "lexer.hpp"
#include "token_strategies.hpp"

void Lexer::initialize() {
    // should be clear anyways, but just in case, y'know?
    strategy_lookup.clear();
    
    // Optional: Pre-size the map to avoid re-hashing during these insertions
    strategy_lookup.reserve(9);

    // emplace here is better than []= assignment, in that it won't overwrite the values if this is called again for some reason
    strategy_lookup.emplace(StrategyContext::Default,           std::make_unique<PlaceholderStrategy>(*this));
    strategy_lookup.emplace(StrategyContext::Whitespace,        std::make_unique<WhitespaceStrategy>(*this));
    strategy_lookup.emplace(StrategyContext::Identifier,        std::make_unique<IdentifierStrategy>(*this));
    strategy_lookup.emplace(StrategyContext::Operator,          std::make_unique<OperatorStrategy>(*this));
    strategy_lookup.emplace(StrategyContext::CommentInline,     std::make_unique<CommentInlineStrategy>(*this));
    strategy_lookup.emplace(StrategyContext::CommentMultiline,  std::make_unique<CommentMultilineStrategy>(*this));
    strategy_lookup.emplace(StrategyContext::Number,            std::make_unique<NumberStrategy>(*this));
    strategy_lookup.emplace(StrategyContext::Indentation,       std::make_unique<IndentationStrategy>(*this));
    strategy_lookup.emplace(StrategyContext::CurlyBrace,        std::make_unique<CurlyBraceStrategy>(*this));
    strategy_lookup.emplace(StrategyContext::String,            std::make_unique<StringStrategy>(*this));
    strategy_lookup.emplace(StrategyContext::StringMultiLine,   std::make_unique<StringMultilineStrategy>(*this));
}