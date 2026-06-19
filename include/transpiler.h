#ifndef PHONK_LANG_TRANSPILER_H
#define PHONK_LANG_TRANSPILER_H

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "statement.h"

class Transpiler {
public:
    explicit Transpiler(std::vector<std::unique_ptr<Statement>> statements)
        : statements_(std::move(statements)) {}

    std::string generateCPP();

private:
    std::vector<std::unique_ptr<Statement>> statements_;
    std::string functions;

    std::vector<std::unordered_set<std::string>> scopes_;

private:
    std::string generateStatement(Statement* stmt, int indentLevel);
    static std::string indent(int level);

    void pushScope() {
        scopes_.push_back({});
    }

    void popScope() {
        scopes_.pop_back();
    }

    bool isDeclared(const std::string& name) {
        for (auto it = scopes_.rbegin(); it != scopes_.rend(); ++it) {
            if (it->contains(name)) return true;
        }
        return false;
    }

    void declare(const std::string& name) {
        scopes_.back().insert(name);
    }
};

#endif