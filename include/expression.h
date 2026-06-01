//
// Created by maxmo on 5/26/2026.
//

#ifndef CSA_FINAL_EXPRESSION_H
#define CSA_FINAL_EXPRESSION_H
#include <memory>
#include <string>
#include <utility>

class Expression {
public:
    virtual ~Expression() = default;

    virtual std::string toCPP() const = 0;

    virtual std::string toString() const = 0;
};

class NumberExpression : public Expression {
public:
    std::string value_;

    explicit NumberExpression(std::string value) : value_(std::move(value)) {}

    std::string toCPP() const override {
        return value_;
    }

    std::string toString() const override {
        return value_;
    }
};

class StringExpression : public Expression {
public:
    std::string value_;

    explicit StringExpression(std::string value)
        : value_(std::move(value)) {}

    std::string toCPP() const override {
        return "\"" + value_ + "\"";
    }

    std::string toString() const override {
        return "\"" + value_ + "\"";
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

    std::string toCPP() const override {
        std::string cppOp{op_};

        if (op_ == "and") {
            cppOp = "&&";
        }
        if (op_ == "or") {
            cppOp = "||";
        }

        return "(" + left_->toCPP() + " " +
               cppOp + " " +
               right_->toCPP() + ")";
    }

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

    std::string toCPP() const override {
        return identifier_;
    }

    std::string toString() const override {
        return identifier_;
    }
};

class BooleanExpression : public Expression {
public:
    bool value_;

    explicit BooleanExpression(const bool value)
        : value_(value) {}

    std::string toCPP() const override {
        return value_ ? "true" : "false";
    }

    std::string toString() const override {
        return value_ ? "true" : "false";
    }
};

class UnaryExpression : public Expression {
public:
    std::string op_;
    std::unique_ptr<Expression> expr_;

    UnaryExpression(
        std::string op,
        std::unique_ptr<Expression> expr
    )
        : op_(std::move(op)),
          expr_(std::move(expr)) {}

    std::string toCPP() const override {

        std::string cppOp = op_;

        if (op_ == "not") {
            cppOp = "!";
        }

        return "(" + cppOp + expr_->toCPP() + ")";
    }

    std::string toString() const override {
        return "(" + op_ + " " +
               expr_->toString() + ")";
    }
};

#endif //CSA_FINAL_EXPRESSION_H
