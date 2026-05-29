//
// Created by maxmo on 5/26/2026.
//

#ifndef CSA_FINAL_PARSER_H
#define CSA_FINAL_PARSER_H

#include <vector>
#include <memory>

#include "token.h"
#include "expression.h"
#include "statement.h"

class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    /**
     * Entry point for expression parsing.
     *
     * Parses a single expression AST from the token stream.
     *
     * @return The root node of the parsed expression tree.
     */
    std::vector<std::unique_ptr<Statement>> parse();

private:
    std::vector<Token> tokens_;
    int pos_;

    /**
     * Returns the current token without consuming it.
     *
     * @return The token at the parser's current position.
     */
    Token current() const;

    /**
     * Checks whether the parser has reached the end-of-file token.
     *
     * @return True if the current token is EOF, otherwise false.
     */
    bool isAtEnd() const;

    /**
    * Consumes and returns the current token, advancing the parser position by one.
     *
     * @return The token that was consumed.
     */
    Token advance();

    /**
     * Parses addition and subtraction expressions.
     *
     * @return A syntax tree representing the parsed expression.
     */
    std::unique_ptr<Expression> parseExpression();

    /**
     * Parses multiplication and division expressions.
     *
     * @return A syntax tree representing the parsed term.
     */
    std::unique_ptr<Expression> parseTerm();

    /**
     * Parses the most basic expression units (numeric literals, variable references, etc.).
     *
     * @return A syntax tree representing the parsed factor.
     * @throws ParserError If no valid expression is found.
     */
    std::unique_ptr<Expression> parsePrimary();

    /**
     * Parses statements (e.g., print).
     *
     * @return A syntax tree representing the parsed statement.
     * @throws ParserError If no closing right parenthesis is found.
     */
    std::unique_ptr<Statement> parseStatement();

};

#endif //CSA_FINAL_PARSER_H
