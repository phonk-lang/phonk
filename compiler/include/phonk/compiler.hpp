//
// Created by maxmo on 6/25/2026.
//

#ifndef PHONK_COMPILER_HPP
#define PHONK_COMPILER_HPP
#include <filesystem>
#include <string>
#include <vector>
#include <phonk/source/source_file.hpp>

namespace phonk {

class Compiler {
public:
    void addFile(const std::filesystem::path& path);

    void addVirtualFile(const std::string& name, const std::string& content);

    int compile() const;

private:
    std::vector<source::SourceFile> files_;

    int compileFile(const source::SourceFile& file) const;
};

} // phonk

#endif //PHONK_COMPILER_HPP
