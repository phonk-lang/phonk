//
// Created by maxmo on 6/17/2026.
//

#include <gtest/gtest.h>

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

TEST(ParserTests, ParsesSubtraction) {
    const auto ast = parseProgram(
        "x = 8 - 2;"
    );

    EXPECT_EQ(
        ast[0]->toString(),
        "(assign x (- 8 2))"
    );
}


TEST(ParserTests, ParsesMultiplication) {
    const auto ast = parseProgram(
        "x = 2 * 4;"
    );

    EXPECT_EQ(
        ast[0]->toString(),
        "(assign x (* 2 4))"
    );
}

TEST(ParserTests, ParsesDivision) {
    const auto ast = parseProgram(
        "x = 9 / 3;"
    );

    EXPECT_EQ(
        ast[0]->toString(),
        "(assign x (/ 9 3))"
    );
}

TEST(ParserTests, ParsesModulus) {
    const auto ast = parseProgram(
        "x = 7 % 2;"
    );

    EXPECT_EQ(
        ast[0]->toString(),
        "(assign x (% 7 2))"
    );
}

TEST(ParserTests, ParsesIncrementStatement) {
    const auto ast = parseProgram("x++;");
    ASSERT_EQ(ast.size(), 1);
    EXPECT_EQ(ast[0]->toString(), "(inc x)");
}

TEST(ParserTests, ParsesDecrementStatement) {
    const auto ast = parseProgram("x--;");
    ASSERT_EQ(ast.size(), 1);
    EXPECT_EQ(ast[0]->toString(), "(dec x)");
}
