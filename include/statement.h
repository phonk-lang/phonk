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

    virtual std::string toString() const = 0;
};

class PrintStatement : public Statement {
public:
    std::unique_ptr<Expression> expression_;

    explicit PrintStatement(std::unique_ptr<Expression> statement) : expression_(std::move(statement)) {};

    std::string toString() const override {
        return "(print " + expression_->toString() + ")";
    }
};

#endif //CSA_FINAL_STATEMENT_H
