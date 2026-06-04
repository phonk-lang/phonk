//
// Created by maxmo on 5/22/2026.
//

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

    std::ifstream file("../program.templang");

    if (!file) {
        std::cerr << "Failed to open file\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string source = buffer.str();

    Lexer lexer(source);

    const auto tokens = lexer.tokenize();

    Parser parser(tokens);

    Transpiler transpiler(parser.parse());

    std::string cppCode = transpiler.generateCPP();

    // Write generated code
    std::ofstream out("output.cpp"); // cmake-build-debug/

    out << cppCode;

    out.close();

    // Compile generated code
    system("g++ output.cpp -o output.exe");

    // Run generated executable
    system("output.exe");

    return 0;
}