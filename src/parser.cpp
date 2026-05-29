//
// Created by maxmo on 5/26/2026.
//

#include "parser.h"

#include <iostream>

#include "error.h"

Parser::Parser(const std::vector<Token> &tokens) : tokens_(tokens), pos_(0) {}

Token Parser::current() const {
    return tokens_.at(pos_);
}

bool Parser::isAtEnd() const {
    return current().type == TokenType::Eof_Token;
}

Token Parser::advance() {
    if (!isAtEnd()) {
        pos_++;
    }

    return tokens_.at(pos_ - 1);
}

std::unique_ptr<Expression> Parser::parseExpression() {
    auto expr = parseTerm();

    while (
        current().type == TokenType::Plus ||
        current().type == TokenType::Minus
    ) {
        Token op = advance();

        auto right = parseTerm();

        expr = std::make_unique<BinaryExpression>(
            std::move(expr),
            op.value,
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expression> Parser::parseTerm() {
    auto expr = parsePrimary();

    while (current().type == TokenType::Star || current().type == TokenType::Slash) {
        Token op = advance();

        auto right = parsePrimary();

        expr = std::make_unique<BinaryExpression>(std::move(expr), op.value, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::parsePrimary() {

    if (current().type == TokenType::L_Paren) {
        advance(); // consume '('

        auto expr = parseExpression();

        if (current().type != TokenType::R_Paren) {

            throw ParserError(current().line, current().col, "expected ')'");
        }

        advance(); // consume ')'

        return expr;
    }

    if (const Token token = current(); token.type == TokenType::Identifier) {
        advance();
        return std::make_unique<IdentifierExpression>(token.value);
    }

    if (const Token token = current();
        token.type == TokenType::String_Lit) {

        advance();

        return std::make_unique<StringExpression>(
            token.value
        );
    }

    if (Token const token = current(); token.type == TokenType::Number) {
        advance();
        return std::make_unique<NumberExpression>(token.value);
    }

    throw ParserError(current().line, current().col, "expected expression");
}

std::vector<std::unique_ptr<Statement> > Parser::parse() {
    std::vector<std::unique_ptr<Statement>> statements;

    while (!isAtEnd()) {
        statements.push_back(parseStatement());
    }

    return statements;
}

std::unique_ptr<Statement> Parser::parseStatement() {

    if (current().type == TokenType::Kw_Print) {
        advance(); // consume print

        if (current().type != TokenType::L_Paren) {
            throw ParserError(
                current().line,
                current().col,
                "expected '(' after print"
            );
        }

        advance(); // consume '('

        auto expr = parseExpression();

        if (current().type != TokenType::R_Paren) {
            throw ParserError(current().line, current().col, "expected ')'");
        }

        advance();

        if (current().type != TokenType::Semicolon) {
            throw ParserError(current().line, current().col, "expected ';'");
        }

        advance();

        return std::make_unique<PrintStatement>(
            std::move(expr)
        );
    }

    throw ParserError(current().line, current().col, "unknown expression");
}