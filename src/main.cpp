#include "lexer.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <array>

std::string newline_test_file = "C:/Users/F0lak/dm_open_ide/test_dm_files/newline_test.dm";
std::string token_test_file = "C:/Users/F0lak/dm_open_ide/test_dm_files/token_test.dm";
std::string operator_test_file = "C:/Users/F0lak/dm_open_ide/test_dm_files/operators.dm";
std::string milestone1_test_file = "C:/Users/F0lak/dm_open_ide/test_dm_files/keyword_test.dm";
std::string milestone2_test_file = "C:/Users/F0lak/dm_open_ide/test_dm_files/operators.dm";

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
    const std::string TEST_FILE = milestone2_test_file;
    std::string file_contents = load_file(TEST_FILE);
    lexer.set_source(file_contents);
    std::cout << "Lexer Source set successfully\n";

    std::string scan_result = lexer.scan(file_contents);
    std::cout << "Scan Result:\n" << scan_result << "\n";

    std::cout << TEST_FILE << " is " << file_contents.size() << " characters long\n";
    std::cout << TEST_FILE << " has " << lexer.line_map.size() << " lines\n";
}

void count_strategies(Lexer lexer) {
    std::cout << "Lexer has " << Lexer::strategy_lookup.size() << " TokenStrategies:\n";

    // Use a range-based for loop to iterate over the map
    for (auto const& [context, strategy] : Lexer::strategy_lookup) {
        // 'strategy' is the pointer to the instance
        std::cout << "  Strategy: " << strategy->name() << "\n";
    }
}

void lexer_test() {
    std::cout << "Running Lexer Test\n";
    std::cout << "Current path is: " << std::filesystem::current_path() << "\n";
    Lexer lexer;
    std::cout << "Lexer Constructed Successfully\n\n";
    std::string file_contents = load_file(token_test_file);
    std::cout << token_test_file << " is " << file_contents.size() << " characters long\n";

    try {
        lexer.set_source(file_contents);
        std::cout << "Lexer Source set successfully\n";
    }
    catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    try{
        lexer.count_lines();
        std::cout << "Lexer Lines counted successfully\n";
    }
    catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    std::cout << token_test_file << " has " << lexer.line_map.size() << " lines\n";
   // std::cout << "\nPress the any Key to end test...\n";
   // std::cin.get();
    std::cout << "Lexer Test Complete";
}

int main() {
    try {
        test_run();
        return 0;
    }
    catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}