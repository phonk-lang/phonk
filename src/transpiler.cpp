#include "transpiler.h"

std::string Transpiler::generateCPP() {
    scopes_.clear();
    scopes_.emplace_back();

    functions.clear();

    std::string mainBody;

    for (const auto &statement: statements_) {
        mainBody += generateStatement(statement.get(), 1);
    }

    return
            "#include <iostream>\n\n" +
            functions +
            "\nint main() {\n" +
            mainBody +
            "    return 0;\n"
            "}";
}

std::string Transpiler::indent(const int level) {
    return std::string(level * 4, ' ');
}

std::string Transpiler::generateStatement(Statement *stmt, const int indentLevel) {
    if (const auto fn = dynamic_cast<FunctionStatement *>(stmt)) {
        std::string result = "auto " + fn->name_ + "(";

        for (size_t i = 0; i < fn->params_.size(); i++) {
            result += "auto " + fn->params_[i];
            if (i + 1 < fn->params_.size()) result += ", ";
        }

        result += ") {\n";

        pushScope();

        for (const auto &s: fn->body_) {
            result += generateStatement(s.get(), 1);
        }

        popScope();

        result += "}\n\n";

        functions += result;

        return "";
    }

    if (auto ret = dynamic_cast<ReturnStatement *>(stmt)) {
        return indent(indentLevel) +
               "return " +
               ret->expr_->toCPP() +
               ";\n";
    }

    if (auto assign = dynamic_cast<AssignmentStatement *>(stmt)) {
        if (!isDeclared(assign->identifier_)) {
            declare(assign->identifier_);
            return indent(indentLevel) +
                   "auto " +
                   assign->identifier_ +
                   " = " +
                   assign->expression_->toCPP() +
                   ";\n";
        }

        return indent(indentLevel) +
               assign->identifier_ +
               " = " +
               assign->expression_->toCPP() +
               ";\n";
    }

    if (auto print = dynamic_cast<PrintStatement *>(stmt)) {
        return indent(indentLevel) +
               "std::cout << " +
               print->expression_->toCPP() +
               " << std::endl;\n";
    }

    if (auto loop = dynamic_cast<WhileStatement *>(stmt)) {
        std::string result =
                indent(indentLevel) +
                "while (" +
                loop->condition_->toCPP() +
                ") {\n";

        pushScope();

        for (const auto &statement: loop->body_) {
            result += generateStatement(statement.get(), indentLevel + 1);
        }

        popScope();

        result += indent(indentLevel) + "}\n";

        return result;
    }

    if (auto ifStmt = dynamic_cast<IfStatement *>(stmt)) {
        std::string result =
                indent(indentLevel) +
                "if (" +
                ifStmt->condition_->toCPP() +
                ") {\n";

        pushScope();

        for (const auto &statement: ifStmt->thenBody_) {
            result += generateStatement(statement.get(), indentLevel + 1);
        }

        popScope();

        result += indent(indentLevel) + "}";

        if (ifStmt->elseIf_) {
            result += " else ";
            result += generateStatement(ifStmt->elseIf_.get(), indentLevel);
            return result;
        }

        if (!ifStmt->elseBody_.empty()) {
            result += " else {\n";

            pushScope();

            for (const auto &statement: ifStmt->elseBody_) {
                result += generateStatement(statement.get(), indentLevel + 1);
            }

            popScope();

            result += indent(indentLevel) + "}";
        }

        result += "\n";

        return result;
    }

    return "";
}
