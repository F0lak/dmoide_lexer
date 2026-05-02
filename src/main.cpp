#include "lexer.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <array>

std::string newline_test_file = "C:/Users/F0lak/dm_open_ide/test_dm_files/newline_test.dm";
std::string token_test_file = "C:/Users/F0lak/dm_open_ide/test_dm_files/token_test.dm";

std::string load_file(const std::string& path) {
    std::ifstream file(path, std::ios::in | std::ios::binary);

    if(!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void test_run() {
    std::cout << "Current path is: " << std::filesystem::current_path() << std::endl;
    Lexer lexer;
    std::string file_contents = load_file(token_test_file);
    std::cout << "Token Result: " << lexer.scan(file_contents) << "\n";
}

void lexer_test() {
    Lexer lexer;
    std::cout << "Running Lexer Test with LUT[" << lexer.strategy_lookup.size() << "]\n";

    for(size_t i = 0; i < lexer.strategy_lookup.size(); ++i) {
        std::cout << "Index[" << i << "]: " << lexer.strategy_lookup[i]->name() << "\n";
    }
}

int main() {
    try {
        lexer_test();
        return 0;
    }
    catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}