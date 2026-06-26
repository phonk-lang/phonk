//
// Created by maxmo on 6/20/2026.
//

#ifndef PHONK_DIAGNOSTIC_ENGINE_HPP
#define PHONK_DIAGNOSTIC_ENGINE_HPP
#include <vector>
#include <phonk/diagnostics/diagnostic.hpp>

namespace phonk::diagnostics {

class DiagnosticEngine {
public:
    void report(Severity severity, const std::string& message, source::SourceLocation location);

    bool hasErrors() const;

private:
    std::vector<Diagnostic> diagnostics_;
};

}

#endif //PHONK_DIAGNOSTIC_ENGINE_HPP
