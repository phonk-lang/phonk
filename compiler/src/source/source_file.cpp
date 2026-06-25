//
// Created by maxmo on 6/20/2026.
//

#include <utility>

#include <phonk/source/source_file.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace phonk::source {

SourceFile::SourceFile(std::string name, std::string content) : name_(std::move(name)),
                                                                path_(std::nullopt),
                                                                content_(std::move(content)) {
}

SourceFile::SourceFile(const std::filesystem::path& path) : name_(path.filename().string()),
                                                            path_(path) {
    std::ifstream file(path);

    if (!file) {
        throw std::runtime_error("Failed to open file: " + path.string());
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    content_ = buffer.str();
}

const std::string& SourceFile::getName() const {
    return name_;
}

const std::optional<std::filesystem::path>& SourceFile::getPath() const {
    return path_;
}

const std::string& SourceFile::getContent() const {
    return content_;
}

}
