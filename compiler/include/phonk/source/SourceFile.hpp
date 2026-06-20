//
// Created by maxmo on 6/20/2026.
//

#ifndef PHONK_SOURCEFILE_HPP
#define PHONK_SOURCEFILE_HPP
#include <string>

namespace phonk::source {

/**
 * Represents a source file written in the P.H.O.N.K. programming language (.phonk).
 */
class SourceFile {
public:
    SourceFile(std::string name, std::string content);

    const std::string& getName() const;

    const std::string& getContent() const;

private:
    std::string name_;
    std::string content_;
};

}

#endif //PHONK_SOURCEFILE_HPP