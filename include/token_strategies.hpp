#pragma once
#include <string>

class TokenStrategy {
    public:
        virtual std::string name() const = 0;
        virtual void run() = 0;
        virtual ~TokenStrategy() = default;
};

class PlaceholderStrategy : public TokenStrategy {
    public:
        std::string name() const override;
        static PlaceholderStrategy* instance();
        void run() override;
};