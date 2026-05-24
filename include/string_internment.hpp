#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class StringInterner {
    public:
        void reserve(size_t capacity);
        void trim(size_t size_buffer);
        uint32_t intern_string(std::string_view string);
        std::string_view lookup(uint32_t index);
        uint32_t size();

    private:
        std::unordered_map<std::string_view, uint32_t> intern_hashmap;
        std::vector<std::string> intern_table;
};