//
// Created by maxmo on 6/20/2026.
//

#ifndef PHONK_SOURCE_FILE_HPP
#define PHONK_SOURCE_FILE_HPP
#include <filesystem>
#include <optional>
#include <string>

namespace phonk::source {

/**
 * Represents a source file written in the P.H.O.N.K. programming language (.phonk).
 */
class SourceFile {
public:
    explicit SourceFile(std::string name, std::string content);

    explicit SourceFile(const std::filesystem::path& path);

    const std::string& getName() const;

    const std::optional<std::filesystem::path>& getPath() const;

    const std::string& getContent() const;

private:
    std::string name_;
    std::optional<std::filesystem::path> path_;
    std::string content_;
};

}

#endif //PHONK_SOURCE_FILE_HPP