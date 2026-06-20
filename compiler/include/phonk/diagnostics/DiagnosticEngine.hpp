//
// Created by maxmo on 6/20/2026.
//

#ifndef PHONK_DIAGNOSTICENGINE_HPP
#define PHONK_DIAGNOSTICENGINE_HPP
#include <vector>
#include <phonk/diagnostics/Diagnostic.hpp>

namespace phonk::diagnostics {

class DiagnosticEngine {
public:
    void report(Severity severity, std::string& message, source::SourceLocation location);

    bool hasErrors() const;

private:
    std::vector<Diagnostic> diagnostics_;
};

}

#endif //PHONK_DIAGNOSTICENGINE_HPP