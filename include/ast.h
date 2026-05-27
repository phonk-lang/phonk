//
// Created by maxmo on 5/26/2026.
//

#ifndef CSA_FINAL_AST_H
#define CSA_FINAL_AST_H
#include <memory>
#include <string>
#include <utility>

class Expression {
public:
    virtual ~Expression() = default;

    virtual std::string toString() const = 0;
};

class NumberExpression : public Expression {
public:
    std::string value_;

    explicit NumberExpression(std::string value) : value_(std::move(value)) {}

    std::string toString() const override {
        return value_;
    }
};

class BinaryExpression : public Expression {
public:
    std::unique_ptr<Expression> left_;
    std::string op_;
    std::unique_ptr<Expression> right_;

    explicit BinaryExpression(
            std::unique_ptr<Expression> left,
            std::string op,
            std::unique_ptr<Expression> right
        )
        :   left_(std::move(left)),
            op_(std::move(op)),
            right_(std::move(right)) {}

    std::string toString() const override {
        return "(" + op_ + " " +
               left_->toString() + " " +
               right_->toString() + ")";
    }
};

class IdentifierExpression : public Expression {
public:
    std::string identifier_;

    explicit IdentifierExpression(std::string identifier)
        : identifier_(std::move(identifier)) {}

    std::string toString() const override {
        return identifier_;
    }
};

#endif //CSA_FINAL_AST_H
