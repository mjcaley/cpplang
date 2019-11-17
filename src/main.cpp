#include <fstream>
#include <iostream>
#include "Lexer/Context.hpp"
#include "Lexer/Lexer.hpp"


int main() {
    std::cout << "Hello, World!" << std::endl;

    auto input = R"(example.txt)";
    auto context = cpplang::Context { std::ifstream { input, std::istream::binary } };
    while (!context.eof())
    {
        context.advance();
        std::cout << "Character: " << context.get_current_char().value_or('\0') << std::endl;
        std::cout << "Position: " <<
            context.get_current_position().value_or(cpplang::Position {0, 0}).line() << ", " <<
            context.get_current_position().value_or(cpplang::Position {0, 0}).column() << std::endl;
    }

    return 0;
}
