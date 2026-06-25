//
// Created by maxmo on 6/20/2026.
//

#include <utility>

#include <phonk/source/source_file.hpp>

namespace phonk::source {

SourceFile::SourceFile(std::string name, std::string content) : name_(std::move(name)),
                                                                content_(std::move(content)) {
}

const std::string& SourceFile::getName() const {
    return name_;
}

const std::string& SourceFile::getContent() const {
    return content_;
}

}
