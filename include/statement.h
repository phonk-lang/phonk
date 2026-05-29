//
// Created by maxmo on 5/27/2026.
//

#ifndef CSA_FINAL_STATEMENT_H
#define CSA_FINAL_STATEMENT_H
#include <memory>
#include <string>

#include "expression.h"

class Statement {
public:
    virtual ~Statement() = default;

    virtual std::string toCPP() const = 0;

    virtual std::string toString() const = 0;
};

class PrintStatement : public Statement {
public:
    std::unique_ptr<Expression> expression_;

    explicit PrintStatement(std::unique_ptr<Expression> statement) : expression_(std::move(statement)) {};

    std::string toCPP() const override {
        return "std::cout << " + expression_->toCPP() + " << std::endl;";
    };

    std::string toString() const override {
        return "(print " + expression_->toString() + ")";
    }
};

class AssignmentStatement : public Statement {
public:
    std::string identifier_;
    std::unique_ptr<Expression> expression_;

    explicit AssignmentStatement(
        std::string identifier,
        std::unique_ptr<Expression> expression
    )
        : identifier_(std::move(identifier)),
          expression_(std::move(expression)) {}

    std::string toCPP() const override {
        return "auto " + identifier_ +
               " = " +
               expression_->toCPP() +
               ";";
    }

    std::string toString() const override {
        return "(assign " +
               identifier_ +
               " " +
               expression_->toString() +
               ")";
    }
};

#endif //CSA_FINAL_STATEMENT_H
