//
// Created by maxmo on 5/29/2026.
//

#include "transpiler.h"

std::string Transpiler::generateCPP() const {
    std::string result = "#include <iostream>\n\n"
                         "int main() {\n";

    std::unordered_set<std::string> declared;

    for (const auto& statement : statements_) {

        // special handling for assignment statements
        if (const auto* assign = dynamic_cast<AssignmentStatement*>(statement.get())) {
            if (const std::string& name = assign->identifier_; !declared.contains(name)) {
                declared.insert(name);
                result += "    auto " + name + " = " +
                          assign->expression_->toCPP() + ";\n";
            } else {
                result += "    " + name + " = " +
                          assign->expression_->toCPP() + ";\n";
            }
        }
        else {
            result += "    " + statement->toCPP() + "\n";
        }
    }

    return result + "    return 0;\n"
                    "}";
}