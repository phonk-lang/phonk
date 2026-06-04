//
// Created by maxmo on 5/29/2026.
//

#include "transpiler.h"

std::string Transpiler::generateCPP() {

    declaredVariables_.clear();

    std::string result =
        "#include <iostream>\n\n"
        "int main() {\n";

    for (const auto& statement : statements_) {

        result += generateStatement(
            statement.get(),
            1
        );
    }

    result +=
        "    return 0;\n"
        "}";

    return result;
}

std::string Transpiler::indent(const int level) {
    return std::string(level * 4, ' ');
}

std::string Transpiler::generateStatement(const Statement* stmt, int indentLevel) {
    if (const auto assign = dynamic_cast<const AssignmentStatement*>(stmt)) {
        std::string result;

        if (!declaredVariables_.contains(assign->identifier_)) {

            declaredVariables_.insert(assign->identifier_);

            result =
                indent(indentLevel) +
                "auto " +
                assign->identifier_ +
                " = " +
                assign->expression_->toCPP() +
                ";\n";
        }
        else {

            result =
                indent(indentLevel) +
                assign->identifier_ +
                " = " +
                assign->expression_->toCPP() +
                ";\n";
        }

        return result;
    }
    if (const auto print = dynamic_cast<const PrintStatement*>(stmt)) {

        return
            indent(indentLevel) +
            "std::cout << " +
            print->expression_->toCPP() +
            " << std::endl;\n";
    }

    if (const auto loop = dynamic_cast<const WhileStatement*>(stmt)) {

        std::string result =
            indent(indentLevel) +
            "while (" +
            loop->condition_->toCPP() +
            ") {\n";

        for (const auto& statement : loop->body_) {

            result += generateStatement(
                statement.get(),
                indentLevel + 1
            );
        }

        result += indent(indentLevel) + "}\n";

        return result;
    }

    if (const auto ifStmt = dynamic_cast<const IfStatement*>(stmt)) {

        std::string result =
            indent(indentLevel) +
            "if (" +
            ifStmt->condition_->toCPP() +
            ") {\n";

        for (const auto& statement : ifStmt->thenBody_) {

            result += generateStatement(
                statement.get(),
                indentLevel + 1
            );
        }

        result += indent(indentLevel) + "}";

        if (ifStmt->elseIf_) {

            result += " else ";

            result += generateStatement(
                ifStmt->elseIf_.get(),
                0
            );

            return result;
        }

        if (!ifStmt->elseBody_.empty()) {

            result += " else {\n";

            for (const auto& statement : ifStmt->elseBody_) {

                result += generateStatement(
                    statement.get(),
                    indentLevel + 1
                );
            }

            result += indent(indentLevel) + "}";
        }

        result += "\n";

        return result;
    }

    return "";
}