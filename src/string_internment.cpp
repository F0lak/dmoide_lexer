#include "string_internment.hpp"

void StringInterner::reserve(size_t capacity) {
    intern_hashmap.reserve(capacity);
    intern_table.reserve(capacity);
}

void StringInterner::trim(size_t size_buffer) {
    intern_table.reserve(intern_table.size() + size_buffer);
    intern_table.shrink_to_fit();
}

uint32_t StringInterner::intern_string(std::string_view string) {
    auto it = intern_hashmap.find(string);
    if(it != intern_hashmap.end()){
        return it->second;
    }

    uint32_t new_index = intern_table.size();
    intern_table.emplace_back(string);

    std::string_view perm_string = intern_table.back();
    intern_hashmap[perm_string] = new_index;

    return new_index;
}

std::string_view StringInterner::lookup(uint32_t index) {
    return intern_table[index];
}

uint32_t StringInterner::size() {
    return intern_table.size();
}