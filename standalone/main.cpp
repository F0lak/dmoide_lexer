#include "lexer.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <array>

std::string newline_test_file = "../../../test_dm_files/newline_test.dm";
std::string token_test_file = "../../../test_dm_files/token_test.dm";
std::string operator_test_file = "../../../test_dm_files/operators.dm";
std::string milestone1_test_file = "../../../test_dm_files/keyword_test.dm";
std::string milestone2_test_file = "../../../test_dm_files/operators.dm";
std::string milestone3_test_file = "../../../test_dm_files/number_test.dm";
std::string milestone4_test_file = "../../../test_dm_files/indentation_test.dm";
std::string milestone5_test_file = "../../../test_dm_files/string_test.dm";
std::string crashout1_test_file = "../../../test_dm_files/crashout1.dm";
std::string crashout2_test_file = "../../../test_dm_files/crashout2.dm";
std::string kinfig_test_file = "../../../test_dm_files/kinfig_test.dm";

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
    const std::string TEST_FILE = kinfig_test_file;
    std::string file_contents = load_file(TEST_FILE);
    std::cout << "Lexer Source set successfully\n";

    LexerData lexer_data = lexer.tokenize(file_contents);
    //std::cout << "Scan Result:\n" << lexer.get_formatted_tokens() << "\n";

    std::cout << TEST_FILE << " is " << file_contents.size() << " characters long\n";
    std::cout << TEST_FILE << " has " << lexer.line_count() << " lines\n";
}

void lexer_test() {
    std::cout << "Running Lexer Test\n";
    std::cout << "Current path is: " << std::filesystem::current_path() << "\n";
    Lexer lexer;
    std::cout << "Lexer Constructed Successfully\n";
    std::string file_contents = load_file(token_test_file);
    std::cout << token_test_file << " is " << file_contents.size() << " characters long\n";
    std::cout << token_test_file << " has " << lexer.line_count() << " lines\n";
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