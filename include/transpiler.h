//
// Created by maxmo on 5/29/2026.
//

#ifndef CSA_FINAL_TRANSPILER_H
#define CSA_FINAL_TRANSPILER_H
#include <memory>
#include <string>
#include <vector>

#include "statement.h"

class Transpiler {
public:
    explicit Transpiler(std::vector<std::unique_ptr<Statement>> statements) : statements_(std::move(statements)) {};

    std::string generateCPP() const;
private:
    std::vector<std::unique_ptr<Statement>> statements_;
};

#endif //CSA_FINAL_TRANSPILER_H
