//
// Created by maxmo on 5/22/2026.
//

#include <iostream>

#include "lexer.h"
#include "parser.h"
#include "token.h"

std::string tokenTypeName(TokenType t) {
    switch (t) {
        case TokenType::Kw_Fn:      return "Kw_Fn";
        case TokenType::Kw_Int:     return "Kw_Int";
        case TokenType::Kw_Bool:    return "Kw_Bool";
        case TokenType::Kw_Str:     return "Kw_Str";
        case TokenType::Kw_If:      return "Kw_If";
        case TokenType::Kw_Else:    return "Kw_Else";
        case TokenType::Kw_For:     return "Kw_For";
        case TokenType::Kw_Print:   return "Kw_Print";
        case TokenType::Kw_Return: return "Kw_Return";
        case TokenType::Kw_Returns: return "Kw_Returns";
        case TokenType::Kw_True:    return "Kw_True";
        case TokenType::Kw_False:   return "Kw_False";
        case TokenType::Identifier: return "Identifier";
        case TokenType::Number:     return "Number";
        case TokenType::String_Lit: return "String_Lit";
        case TokenType::Plus:       return "Plus";
        case TokenType::Minus:      return "Minus";
        case TokenType::Star:       return "Star";
        case TokenType::Slash:      return "Slash";
        case TokenType::Assign:     return "Assign";
        case TokenType::Eq:         return "Eq";
        case TokenType::N_Eq:       return "N_Eq";
        case TokenType::Lt:         return "Lt";
        case TokenType::Gt:         return "Gt";
        case TokenType::Lte:        return "Lte";
        case TokenType::Gte:        return "Gte";
        case TokenType::L_Paren:    return "L_Paren";
        case TokenType::R_Paren:    return "R_Paren";
        case TokenType::L_Brace:    return "L_Brace";
        case TokenType::R_Brace:    return "R_Brace";
        case TokenType::Semicolon:  return "Semicolon";
        case TokenType::Comma:      return "Comma";
        case TokenType::Dot:        return "Dot";
        case TokenType::Newline:    return "Newline";
        case TokenType::Unknown:    return "Unknown";
        case TokenType::Eof_Token:  return "Eof_Token";
        default:                    return "???";
    }
}

void printTokens(const std::vector<Token>& tokens) {
    for (const auto& tok : tokens) {
        std::cout << "Line " << tok.line
                  << " | " << tokenTypeName(tok.type)
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


int main() {
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

    std::string source = "x + 2";

    Lexer lexer(source);

    auto tokens = lexer.tokenize();

    Parser parser(tokens);

    auto ast = parser.parse();

    std::cout << ast->toString() << std::endl;

    return 0;
}