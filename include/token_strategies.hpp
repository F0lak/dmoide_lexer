#pragma once
#include <string>
#include "dm_tokens.hpp"

class TokenStrategy {
    public:
        virtual std::string name() const = 0;
        virtual DMToken run(const std::string& source, int pos) = 0;
        virtual ~TokenStrategy() = default;
};

class PlaceholderStrategy : public TokenStrategy {
    public:
        std::string name() const override;
        static PlaceholderStrategy* instance();
        DMToken run(const std::string& source, int pos) override;
};

class WhitespaceStrategy : public TokenStrategy {
    public:
        std::string name() const override;
        static WhitespaceStrategy* instance();
        DMToken run(const std::string& source, int pos) override;
};