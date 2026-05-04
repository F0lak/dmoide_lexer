
#include <unordered_map>
#include "lexer.hpp"
#include "token_strategies.hpp"

void Lexer::initialize() {
    strategy_lookup = {
        {StrategyContext::Default, PlaceholderStrategy::instance()},
        {StrategyContext::Whitespace, WhitespaceStrategy::instance()},
        {StrategyContext::Identifier, IdentifierStrategy::instance()},
        {StrategyContext::Operator, OperatorStrategy::instance()},
        {StrategyContext::CommentInline, CommentInlineStrategy::instance()}
    };
}