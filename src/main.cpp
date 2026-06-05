//
// Created by maxmo on 5/22/2026.
//

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>

#include "lexer.h"
#include "parser.h"
#include "token.h"
#include "transpiler.h"

void printTokens(const std::vector<Token>& tokens) {
    for (const auto& tok : tokens) {
        std::cout << "Line " << tok.line
                  << " | " << Token::tokenTypeToString(tok.type) << "\n"
                  << " | '" << tok.value << "'\n";
    }
}

void runTest(const std::string& label, const std::string& source) {
    std::cout << "\n=== " << label << " ===\n";
    try {
        Lexer lexer(source);
        const auto tokens = lexer.tokenize();
        printTokens(tokens);
    } catch (std::exception& e) {
        std::cout << "ERROR: " << e.what() << "\n";
    }
}


int main(int argc, char* argv[]) {
    // // Test 1: keywords and identifiers
    // runTest("Keywords", "int bool str if else for fn returns");
    //
    // // Test 2: a variable declaration
    // runTest("Variable", "int x = 42;");
    //
    // // Test 3: a full function
    // runTest("Function", R"(
    //     fn add(int x) returns int {
    //         int y = x + 1;
    //         return y;
    //     }
    // )");
    //
    // // Test 4: if statement
    // runTest("If statement", R"(
    //     if (x == 10) {
    //         print("yes");
    //     }
    // )");
    //
    // // Test 5: comments should produce no tokens
    // runTest("Comment", "// this is a comment\nint x = 1;");
    //
    // // Test 6: two-character operators
    // runTest("Operators", "== != <= >=");
    //
    // // Test 7: bad input should throw
    // runTest("Bad character", "int x = @;");
    //
    // // Test 8: unterminated string should throw
    // runTest("Unterminated string", "\"hello");

    std::ifstream file("../example.phonk");

    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string source = buffer.str();

    using Clock = std::chrono::high_resolution_clock;

    auto totalStart = Clock::now();

    auto lexStart = Clock::now();
    Lexer lexer(source);
    const auto tokens = lexer.tokenize();
    auto lexEnd = Clock::now();

    auto parseStart = Clock::now();
    Parser parser(tokens);
    auto ast = parser.parse();
    auto parseEnd = Clock::now();

    auto transpileStart = Clock::now();
    Transpiler transpiler(std::move(ast));
    std::string cppCode = transpiler.generateCPP();
    auto transpileEnd = Clock::now();

    // Write generated code
    std::ofstream out("output.cpp"); // cmake-build-debug/

    out << cppCode;

    out.close();

    // Compile generated code
    auto compileStart = Clock::now();

    system("g++ output.cpp -o output.exe");

    auto compileEnd = Clock::now();

    auto totalEnd = Clock::now();

    // Run generated executable
    system("output.exe");

    std::cout << "\n=== Compile Statistics ===\n";

    std::cout << "Tokens: " << tokens.size() << '\n';

    std::cout << "Lexer: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     lexEnd - lexStart
                 ).count()
              << " us\n";

    std::cout << "Parser: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     parseEnd - parseStart
                 ).count()
              << " us\n";

    std::cout << "Transpiler: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     transpileEnd - transpileStart
                 ).count()
              << " us\n";

    std::cout << "Frontend Compiler: "
              << std::chrono::duration_cast<std::chrono::microseconds>(
                     transpileEnd - totalStart
                 ).count()
              << " us\n";



    std::cout << "g++: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     compileEnd - compileStart
                 ).count()
              << " ms\n";

    std::cout << "Total: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     totalEnd - totalStart
                 ).count()
              << " ms\n";

    return 0;
}