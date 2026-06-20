//
// Created by maxmo on 6/20/2026.
//

#ifndef PHONK_DIAGNOSTIC_HPP
#define PHONK_DIAGNOSTIC_HPP
#include <phonk/source/SourceLocation.hpp>

#include <string>

namespace phonk::diagnostics {

// More severe errors come first in declaration for comparison purposes
enum class Severity {
    Error,
    Warning,
    Info,
};

class Diagnostic {
public:
    Diagnostic(Severity severity, std::string message,
               source::SourceLocation location);

    Severity getSeverity() const;

    std::string getMessage() const;

    source::SourceLocation getLocation() const;

private:
    Severity severity_;
    std::string message_;
    source::SourceLocation location_;
};

}

#endif //PHONK_DIAGNOSTIC_HPP