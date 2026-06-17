//
// Created by maxmo on 6/16/2026.
//

#include <gtest/gtest.h>
#include "error.h"
#include "lexer.h"
#include "token.h"

TEST(LexerTests, TokenizesSingleNumber) {
    Lexer lexer("1");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Number);
    EXPECT_EQ(tokens[0].value, "1");
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesMultiDigitNumber) {
    Lexer lexer("987654");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Number);
    EXPECT_EQ(tokens[0].value, "987654");
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesStringLiteral) {
    Lexer lexer("\"hello\"");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::String_Lit);
    EXPECT_EQ(tokens[0].value, "hello");
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesEmptyStringLiteral) {
    Lexer lexer("\"\"");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::String_Lit);
    EXPECT_EQ(tokens[0].value, "");
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesIdentifier) {
    Lexer lexer("x");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[0].value, "x");
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesIdentifierWithUnderscore) {
    Lexer lexer("_temp_var");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[0].value, "_temp_var");
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesIdentifierWithDigits) {
    Lexer lexer("var123");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[0].value, "var123");
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordPhonk) {
    Lexer lexer("phonk");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_Phonk);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordReturn) {
    Lexer lexer("return");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_Return);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordReturns) {
    Lexer lexer("returns");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_Returns);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordIf) {
    Lexer lexer("if");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_If);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordElse) {
    Lexer lexer("else");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_Else);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordWhile) {
    Lexer lexer("while");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_While);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordPrint) {
    Lexer lexer("print");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_Print);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordTrue) {
    Lexer lexer("true");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_True);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordFalse) {
    Lexer lexer("false");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_False);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordInt) {
    Lexer lexer("int");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_Int);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordBool) {
    Lexer lexer("bool");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_Bool);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordStr) {
    Lexer lexer("str");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_Str);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordAnd) {
    Lexer lexer("and");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_And);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordOr) {
    Lexer lexer("or");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_Or);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, RecognizesKeywordNot) {
    Lexer lexer("not");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_Not);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, DoesNotTreatKeywordPrefixAsKeyword) {
    Lexer lexer("printx");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesPlus) {
    Lexer lexer("+");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Plus);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesMinus) {
    Lexer lexer("-");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Minus);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesStar) {
    Lexer lexer("*");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Star);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesSlash) {
    Lexer lexer("/");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Slash);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesPercent) {
    Lexer lexer("%");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Percent);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesLeftParen) {
    Lexer lexer("(");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::L_Paren);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesRightParen) {
    Lexer lexer(")");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::R_Paren);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesLeftBrace) {
    Lexer lexer("{");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::L_Brace);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesRightBrace) {
    Lexer lexer("}");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::R_Brace);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesSemicolon) {
    Lexer lexer(";");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Semicolon);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesComma) {
    Lexer lexer(",");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Comma);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesAssignment) {
    Lexer lexer("=");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Assign);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesEquality) {
    Lexer lexer("==");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Eq);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesNotEqual) {
    Lexer lexer("!=");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::N_Eq);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesLessThan) {
    Lexer lexer("<");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Lt);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesGreaterThan) {
    Lexer lexer(">");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Gt);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesLessThanOrEqual) {
    Lexer lexer("<=");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Lte);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesGreaterThanOrEqual) {
    Lexer lexer(">=");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Gte);
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesSimpleAssignmentStatement) {
    Lexer lexer("x = 5;");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 5);

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[0].value, "x");
    EXPECT_EQ(tokens[1].type, TokenType::Assign);
    EXPECT_EQ(tokens[2].type, TokenType::Number);
    EXPECT_EQ(tokens[2].value, "5");
    EXPECT_EQ(tokens[3].type, TokenType::Semicolon);
    EXPECT_EQ(tokens[4].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesPrintStatement) {
    Lexer lexer("print(\"hello\");");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 6);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_Print);
    EXPECT_EQ(tokens[1].type, TokenType::L_Paren);
    EXPECT_EQ(tokens[2].type, TokenType::String_Lit);
    EXPECT_EQ(tokens[2].value, "hello");
    EXPECT_EQ(tokens[3].type, TokenType::R_Paren);
    EXPECT_EQ(tokens[4].type, TokenType::Semicolon);
    EXPECT_EQ(tokens[5].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesIfStatement) {
    Lexer lexer("if (x < 10) {}");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 9);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_If);
    EXPECT_EQ(tokens[1].type, TokenType::L_Paren);
    EXPECT_EQ(tokens[2].type, TokenType::Identifier);
    EXPECT_EQ(tokens[2].value, "x");
    EXPECT_EQ(tokens[3].type, TokenType::Lt);
    EXPECT_EQ(tokens[4].type, TokenType::Number);
    EXPECT_EQ(tokens[4].value, "10");
    EXPECT_EQ(tokens[5].type, TokenType::R_Paren);
    EXPECT_EQ(tokens[6].type, TokenType::L_Brace);
    EXPECT_EQ(tokens[7].type, TokenType::R_Brace);
    EXPECT_EQ(tokens[8].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesBooleanExpression) {
    Lexer lexer("true and false");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 4);

    EXPECT_EQ(tokens[0].type, TokenType::Kw_True);
    EXPECT_EQ(tokens[1].type, TokenType::Kw_And);
    EXPECT_EQ(tokens[2].type, TokenType::Kw_False);
    EXPECT_EQ(tokens[3].type, TokenType::Eof_Token);
}

TEST(LexerTests, TokenizesArithmeticExpression) {
    Lexer lexer("x + y * 5");

    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 6);

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[1].type, TokenType::Plus);
    EXPECT_EQ(tokens[2].type, TokenType::Identifier);
    EXPECT_EQ(tokens[3].type, TokenType::Star);
    EXPECT_EQ(tokens[4].type, TokenType::Number);
    EXPECT_EQ(tokens[5].type, TokenType::Eof_Token);
}

TEST(LexerTests, SkipsSpaces) {
    Lexer lexer(" x");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[0].value, "x");
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, SkipsSingleLineComment) {
    Lexer lexer("x // comment\n y");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[0].value, "x");
    EXPECT_EQ(tokens[1].type, TokenType::Identifier);
    EXPECT_EQ(tokens[1].value, "y");
    EXPECT_EQ(tokens[2].type, TokenType::Eof_Token);
}

TEST(LexerTests, SkipsSingleLineCommentAtEndOfFile) {
    Lexer lexer("x // comment");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 2);

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[0].value, "x");
    EXPECT_EQ(tokens[1].type, TokenType::Eof_Token);
}

TEST(LexerTests, SkipsBlockComment) {
    Lexer lexer("x /* comment */ y");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[0].value, "x");
    EXPECT_EQ(tokens[1].type, TokenType::Identifier);
    EXPECT_EQ(tokens[1].value, "y");
    EXPECT_EQ(tokens[2].type, TokenType::Eof_Token);
}

TEST(LexerTests, SkipsMultiLineBlockComment) {
    Lexer lexer("x /* line1\nline2\nline3 */ y");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[0].value, "x");
    EXPECT_EQ(tokens[1].type, TokenType::Identifier);
    EXPECT_EQ(tokens[1].value, "y");
    EXPECT_EQ(tokens[2].type, TokenType::Eof_Token);
}

TEST(LexerTests, SkipsBlockCommentWithSymbolsInside) {
    Lexer lexer("x /* + == if return */ y");
    const auto tokens = lexer.tokenize();

    ASSERT_EQ(tokens.size(), 3);

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[0].value, "x");
    EXPECT_EQ(tokens[1].type, TokenType::Identifier);
    EXPECT_EQ(tokens[1].value, "y");
    EXPECT_EQ(tokens[2].type, TokenType::Eof_Token);
}

TEST(LexerTests, ThrowsOnUnknownCharacter) {
    Lexer lexer("@");

    EXPECT_THROW(lexer.tokenize(), LexerError);
}

TEST(LexerTests, ThrowsOnDanglingExclamationMark) {
    Lexer lexer("!");

    EXPECT_THROW(lexer.tokenize(), LexerError);
}

TEST(LexerTests, ThrowsOnUnterminatedString) {
    Lexer lexer("\"hello");

    EXPECT_THROW(lexer.tokenize(), LexerError);
}

TEST(LexerTests, ThrowsOnUnterminatedBlockComment) {
    Lexer lexer("/* comment");

    EXPECT_THROW(lexer.tokenize(), LexerError);
}

TEST(LexerTests, TracksFirstTokenPosition) {
    Lexer lexer("x");
    const auto tokens = lexer.tokenize();

    EXPECT_EQ(tokens[0].line, 1);
    EXPECT_EQ(tokens[0].col, 1);
}

TEST(LexerTests, TracksColumnAfterWhitespace) {
    Lexer lexer("   x");
    const auto tokens = lexer.tokenize();

    EXPECT_EQ(tokens[0].value, "x");
    EXPECT_EQ(tokens[0].col, 4);
}

TEST(LexerTests, TracksLineAfterNewline) {
    Lexer lexer("x\ny");
    const auto tokens = lexer.tokenize();

    EXPECT_EQ(tokens[1].value, "y");
    EXPECT_EQ(tokens[1].line, 2);
}

TEST(LexerTests, TracksPositionInProgram) {
    Lexer lexer(
        "x = 5;\n"
        "print(x);"
    );
    const auto tokens = lexer.tokenize();

    EXPECT_EQ(tokens[4].value, "print");
    EXPECT_EQ(tokens[4].line, 2);
    EXPECT_EQ(tokens[4].col, 1);
}

TEST(LexerTests, PreservesTokenOrder) {
    Lexer lexer("x + 5");
    const auto tokens = lexer.tokenize();

    EXPECT_EQ(tokens[0].type, TokenType::Identifier);
    EXPECT_EQ(tokens[1].type, TokenType::Plus);
    EXPECT_EQ(tokens[2].type, TokenType::Number);
}