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

class IfStatement : public Statement {
public:
    std::unique_ptr<Expression> condition_;

    std::vector<std::unique_ptr<Statement>> thenBody_;

    std::vector<std::unique_ptr<Statement>> elseBody_;

    std::unique_ptr<IfStatement> elseIf_;

    explicit IfStatement(
        std::unique_ptr<Expression> condition,
        std::vector<std::unique_ptr<Statement>> thenBody,
        std::vector<std::unique_ptr<Statement>> elseBody = {},
        std::unique_ptr<IfStatement> elseIf = nullptr
    )
        : condition_(std::move(condition)),
          thenBody_(std::move(thenBody)),
          elseBody_(std::move(elseBody)),
          elseIf_(std::move(elseIf)) {}

    std::string toCPP() const override {

        std::string result =
            "if (" + condition_->toCPP() + ") {\n";

        for (const auto& stmt : thenBody_) {
            result += "        " + stmt->toCPP() + "\n";
        }

        result += "    }";

        if (elseIf_) {

            result += " else ";
            result += elseIf_->toCPP();

        } else if (!elseBody_.empty()) {

            result += " else {\n";

            for (const auto& stmt : elseBody_) {
                result += "        " + stmt->toCPP() + "\n";
            }

            result += "    }";
        }

        result += "\n";

        return result;
    }

    std::string toString() const override {

        std::string thenPart;

        for (const auto& stmt : thenBody_) {
            thenPart += stmt->toString() + " ";
        }

        std::string result =
            "(if " +
            condition_->toString() +
            " (" +
            thenPart +
            ")";

        if (elseIf_) {
            result += " " + elseIf_->toString();
        }
        else if (!elseBody_.empty()) {

            std::string elsePart;

            for (const auto& stmt : elseBody_) {
                elsePart += stmt->toString() + " ";
            }

            result += " (else " + elsePart + ")";
        }

        result += ")";

        return result;
    }
};

class WhileStatement : public Statement {
public:
    std::unique_ptr<Expression> condition_;

    std::vector<std::unique_ptr<Statement>> body_;

    explicit WhileStatement(std::unique_ptr<Expression> condition, std::vector<std::unique_ptr<Statement>> body)
            : condition_(std::move(condition)), body_(std::move(body)) {}

    std::string toCPP() const override {
        std::string result =
            "while (" + condition_->toCPP() + ") {\n";

        for (const auto& stmt : body_) {
            result += "        " + stmt->toCPP() + "\n";
        }

        result += "    }";

        return result;
    }

    std::string toString() const override {
        std::string body;

        for (const auto& stmt : body_) {
            body += stmt->toString() + " ";
        }

        std::string result =
            "(while " +
            condition_->toString() +
            " (" +
            body +
            "))";

        return result;
    }
};

#endif //CSA_FINAL_STATEMENT_H
