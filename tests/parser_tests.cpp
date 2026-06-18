//
// Created by maxmo on 6/17/2026.
//

#include <gtest/gtest.h>
#include "error.h"
#include "lexer.h"
#include "parser.h"
#include "statement.h"

static std::vector<std::unique_ptr<Statement> >
parseProgram(const std::string &source) {
    Lexer lexer(source);

    const auto tokens = lexer.tokenize();

    Parser parser(tokens);

    return parser.parse();
}

TEST(ParserTests, ParsesIntegerAssignment) {
    const auto ast = parseProgram("x = 5;");

    ASSERT_EQ(ast.size(), 1);

    EXPECT_EQ(
        ast[0]->toString(),
        "(assign x 5)"
    );
}

TEST(ParserTests, ParsesStringAssignment) {
    const auto ast = parseProgram("msg = \"hello\";");

    ASSERT_EQ(ast.size(), 1);

    EXPECT_EQ(
        ast[0]->toString(),
        "(assign msg \"hello\")"
    );
}

TEST(ParserTests, ParsesBooleanAssignment) {
    const auto ast = parseProgram("done = true;");

    ASSERT_EQ(ast.size(), 1);

    EXPECT_EQ(
        ast[0]->toString(),
        "(assign done true)"
    );
}

TEST(ParserTests, ParsesPrintStatement) {
    const auto ast = parseProgram(
        "print(\"hello\");"
    );

    ASSERT_EQ(ast.size(), 1);

    EXPECT_EQ(
        ast[0]->toString(),
        "(print \"hello\")"
    );
}

TEST(ParserTests, ParsesAddition) {
    const auto ast = parseProgram(
        "x = 5 + 3;"
    );

    EXPECT_EQ(
        ast[0]->toString(),
        "(assign x (+ 5 3))"
    );
}
