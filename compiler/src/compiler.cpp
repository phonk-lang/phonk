//
// Created by maxmo on 6/25/2026.
//

#include <phonk/compiler.hpp>

#include <iostream>

namespace phonk {

void Compiler::addFile(const std::filesystem::path& path) {
    files_.emplace_back(path);
}

void Compiler::addVirtualFile(const std::string& name, const std::string& content) {
    files_.emplace_back(name, content);
}

int Compiler::compileFile(const source::SourceFile& file) const {
    std::cout
        << "Compiling "
        << file.getName()
        << "..."
        << std::endl;

    return 0;
}

int Compiler::compile() const {
    for (const auto& file : files_) {
        compileFile(file);
    }

    return 0;
}

} // phonk