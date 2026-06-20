//
// Created by maxmo on 5/26/2026.
//

#include "parser.h"

#include "error.h"

Parser::Parser(const std::vector<Token> &tokens) : tokens_(tokens), pos_(0) {
}

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

std::vector<std::unique_ptr<Statement> > Parser::parse() {
    std::vector<std::unique_ptr<Statement> > statements;

    while (!isAtEnd()) {
        statements.push_back(parseStatement());
    }

    return statements;
}

std::unique_ptr<Expression> Parser::parseOr() {
    auto expr = parseAnd();

    while (current().type == TokenType::Kw_Or) {
        Token op = advance();

        auto right = parseAnd();

        expr = std::make_unique<BinaryExpression>(
            std::move(expr),
            op.value,
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expression> Parser::parseAnd() {
    auto expr = parseComparison();

    while (current().type == TokenType::Kw_And) {
        Token op = advance();

        auto right = parseComparison();

        expr = std::make_unique<BinaryExpression>(
            std::move(expr),
            op.value,
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expression> Parser::parseComparison() {
    auto expr = parseArithmetic();

    while (
        current().type == TokenType::Eq ||
        current().type == TokenType::N_Eq ||
        current().type == TokenType::Lt ||
        current().type == TokenType::Gt ||
        current().type == TokenType::Lte ||
        current().type == TokenType::Gte
    ) {
        Token op = advance();

        auto right = parseArithmetic();

        expr = std::make_unique<BinaryExpression>(
            std::move(expr),
            op.value,
            std::move(right)
        );
    }

    return expr;
}

std::unique_ptr<Expression> Parser::parseArithmetic() {
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

    while (current().type == TokenType::Star || current().type == TokenType::Slash || current().type ==
           TokenType::Percent) {
        Token op = advance();

        auto right = parsePrimary();

        expr = std::make_unique<BinaryExpression>(std::move(expr), op.value, std::move(right));
    }

    return expr;
}

std::unique_ptr<Expression> Parser::parsePrimary() {
    if (current().type == TokenType::Kw_Not) {
        Token op = advance();

        auto expr = parsePrimary();

        return std::make_unique<UnaryExpression>(
            op.value,
            std::move(expr)
        );
    }

    if (current().type == TokenType::L_Paren) {
        advance(); // consume '('

        auto expr = parseOr();

        if (current().type != TokenType::R_Paren) {
            throw ParserError(current().line, current().col, "expected ')'");
        }

        advance(); // consume ')'

        return expr;
    }

    if (const Token token = current(); token.type == TokenType::Kw_True) {
        advance();
        return std::make_unique<BooleanExpression>(true);
    }

    if (const Token token = current(); token.type == TokenType::Kw_False) {
        advance();
        return std::make_unique<BooleanExpression>(false);
    }

    if (const Token token = current();
        token.type == TokenType::Identifier) {
        advance();

        if (current().type == TokenType::L_Paren) {
            advance();

            std::vector<std::unique_ptr<Expression> > args;

            while (
                !isAtEnd() &&
                current().type != TokenType::R_Paren
            ) {
                args.push_back(parseOr());

                if (current().type == TokenType::Comma) {
                    advance();
                }
            }

            if (current().type != TokenType::R_Paren) {
                throw ParserError(
                    current().line,
                    current().col,
                    "expected ')'"
                );
            }

            advance();

            return std::make_unique<CallExpression>(
                token.value,
                std::move(args)
            );
        }

        return std::make_unique<IdentifierExpression>(
            token.value
        );
    }

    if (const Token token = current();
        token.type == TokenType::String_Lit) {
        advance();

        return std::make_unique<StringExpression>(token.value);
    }

    if (Token const token = current(); token.type == TokenType::Number) {
        advance();
        return std::make_unique<NumberExpression>(token.value);
    }

    throw ParserError(current().line, current().col, "expected expression");
}

std::unique_ptr<Statement> Parser::parseStatement() {
    if (current().type == TokenType::Kw_Phonk) {
        return parseFunctionStatement();
    }

    if (current().type == TokenType::Kw_Return) {
        return parseReturnStatement();
    }

    if (current().type == TokenType::Kw_While) {
        return parseWhileStatement();
    }

    if (current().type == TokenType::Kw_If) {
        return parseIfStatement();
    }

    if (current().type == TokenType::Identifier) {
        Token identifier = advance();

        if (
            current().type == TokenType::Increment ||
            current().type == TokenType::Decrement
        ) {
            const Token op = advance();

            if (current().type != TokenType::Semicolon) {
                throw ParserError(
                    current().line,
                    current().col,
                    "expected ';'"
                );
            }

            advance();

            return std::make_unique<IncrementStatement>(
                identifier.value,
                op.type == TokenType::Increment
            );
        }

        if (current().type != TokenType::Assign) {
            throw ParserError(
                current().line,
                current().col,
                "expected '='"
            );
        }

        advance(); // consume '='

        auto expr = parseOr();

        if (current().type != TokenType::Semicolon) {
            throw ParserError(
                current().line,
                current().col,
                "expected ';'"
            );
        }

        advance();

        return std::make_unique<AssignmentStatement>(
            identifier.value,
            std::move(expr)
        );
    }

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

        auto expr = parseOr();

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

std::vector<std::unique_ptr<Statement> > Parser::parseBlock() {
    std::vector<std::unique_ptr<Statement> > statements;

    while (
        !isAtEnd() &&
        current().type != TokenType::R_Brace
    ) {
        if (current().type == TokenType::Kw_Phonk) {
            throw ParserError(current().line, current().col, "illegal function declaration");
        }
        statements.push_back(parseStatement());
    }

    return statements;
}

std::unique_ptr<Statement> Parser::parseIfStatement() {
    advance(); // consume 'if'

    if (current().type != TokenType::L_Paren) {
        throw ParserError(
            current().line,
            current().col,
            "expected '(' after if"
        );
    }

    advance(); // consume '('

    auto condition = parseOr();

    if (current().type != TokenType::R_Paren) {
        throw ParserError(
            current().line,
            current().col,
            "expected ')'"
        );
    }

    advance(); // consume ')'

    if (current().type != TokenType::L_Brace) {
        throw ParserError(
            current().line,
            current().col,
            "expected '{'"
        );
    }

    advance(); // consume '{'

    auto thenBody = parseBlock();

    if (current().type != TokenType::R_Brace) {
        throw ParserError(
            current().line,
            current().col,
            "expected '}'"
        );
    }

    advance(); // consume '}'

    std::vector<std::unique_ptr<Statement> > elseBody;
    std::unique_ptr<IfStatement> elseIf = nullptr;

    if (current().type == TokenType::Kw_Else) {
        advance(); // consume 'else'

        // else if (...)
        if (current().type == TokenType::Kw_If) {
            auto stmt = parseIfStatement();

            elseIf.reset(
                dynamic_cast<IfStatement *>(stmt.release())
            );
        }

        // else { ... }
        else {
            if (current().type != TokenType::L_Brace) {
                throw ParserError(
                    current().line,
                    current().col,
                    "expected '{' after else"
                );
            }

            advance(); // consume '{'

            elseBody = parseBlock();

            if (current().type != TokenType::R_Brace) {
                throw ParserError(
                    current().line,
                    current().col,
                    "expected '}'"
                );
            }

            advance(); // consume '}'
        }
    }

    return std::make_unique<IfStatement>(
        std::move(condition),
        std::move(thenBody),
        std::move(elseBody),
        std::move(elseIf)
    );
}

std::unique_ptr<Statement> Parser::parseWhileStatement() {
    advance(); // consume 'while'

    if (current().type != TokenType::L_Paren) {
        throw ParserError(
            current().line,
            current().col,
            "expected '(' after while"
        );
    }

    advance(); // consume '('

    auto condition = parseOr();

    if (current().type != TokenType::R_Paren) {
        throw ParserError(
            current().line,
            current().col,
            "expected ')'"
        );
    }

    advance(); // consume ')'

    if (current().type != TokenType::L_Brace) {
        throw ParserError(
            current().line,
            current().col,
            "expected '{'"
        );
    }

    advance(); // consume '{'

    auto body = parseBlock();

    if (current().type != TokenType::R_Brace) {
        throw ParserError(
            current().line,
            current().col,
            "expected '}'"
        );
    }

    advance(); // consume '}'

    return std::make_unique<WhileStatement>(std::move(condition), std::move(body));
}

std::unique_ptr<Statement> Parser::parseFunctionStatement() {
    advance(); // phonk

    if (current().type != TokenType::Identifier) {
        throw ParserError(
            current().line,
            current().col,
            "expected function name"
        );
    }

    std::string name = advance().value;

    if (current().type != TokenType::L_Paren) {
        throw ParserError(
            current().line,
            current().col,
            "expected '('"
        );
    }

    advance();

    std::vector<std::string> params;

    while (
        !isAtEnd() &&
        current().type != TokenType::R_Paren
    ) {
        if (current().type != TokenType::Identifier) {
            throw ParserError(
                current().line,
                current().col,
                "expected parameter"
            );
        }

        params.push_back(
            advance().value
        );

        if (current().type == TokenType::Comma) {
            advance();
        }
    }

    advance(); // )

    if (current().type != TokenType::L_Brace) {
        throw ParserError(
            current().line,
            current().col,
            "expected '{'"
        );
    }

    advance();

    auto body = parseBlock();

    if (current().type != TokenType::R_Brace) {
        throw ParserError(
            current().line,
            current().col,
            "expected '}'"
        );
    }

    advance();

    return std::make_unique<FunctionStatement>(
        name,
        std::move(params),
        std::move(body)
    );
}

std::unique_ptr<Statement> Parser::parseReturnStatement() {
    advance();

    auto expr = parseOr();

    if (current().type != TokenType::Semicolon) {
        throw ParserError(
            current().line,
            current().col,
            "expected ';'"
        );
    }

    advance();

    return std::make_unique<ReturnStatement>(
        std::move(expr)
    );
}
