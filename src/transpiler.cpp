//
// Created by maxmo on 5/29/2026.
//

#include "../include/transpiler.h"

std::string Transpiler::generateCPP() const {

    std::string result =
        "#include <iostream>\n\n"
        "int main() {\n";

    for (const auto& statement : statements_) {
        result += "    " + statement->toCPP() + "\n";
    }

    result +=
        "\n"
        "    return 0;\n"
        "}";

    return result;
}