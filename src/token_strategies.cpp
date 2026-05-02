#include "token_strategies.hpp"
#include <string>

std::string PlaceholderStrategy::name() const  {
    return "PlaceholderStrategy";
}

PlaceholderStrategy* PlaceholderStrategy::instance() {
    static PlaceholderStrategy instance;
    return &instance;
}

void PlaceholderStrategy::run() {};
