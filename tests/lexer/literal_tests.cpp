//
// Created by maxmo on 6/26/2026.
//

#include "lexer_test_utils.hpp"

#include <gtest/gtest.h>
#include <phonk/lexer/lexer.hpp>
#include <phonk/source/source_file.hpp>

using phonk::lexer::TokenType;
using phonk::tests::ExpectedToken;
using phonk::tests::expectTokens;

TEST(LexerTests, TokenizesIntegerLiteral) {
    expectTokens("123", {
                     {TokenType::IntegerLiteral, "123"},
                     {TokenType::EndOfFile, ""}
                 });
}

TEST(LexerTests, TokenizesFloatLiteral) {
    expectTokens("12.34", {
                     {TokenType::FloatLiteral, "12.34"},
                     {TokenType::EndOfFile, ""}
                 });
}

TEST(LexerTests, TokenizesStringLiteral) {
    expectTokens("\"hello world\"", {
                     {TokenType::StringLiteral, "\"hello world\""},
                     {TokenType::EndOfFile, ""}
                 });
}