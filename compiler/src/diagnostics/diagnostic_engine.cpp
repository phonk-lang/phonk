//
// Created by maxmo on 6/20/2026.
//

#include <phonk/diagnostics/diagnostic_engine.hpp>

namespace phonk::diagnostics {

void DiagnosticEngine::report(Severity severity, std::string& message,
                              source::SourceLocation location) {
    diagnostics_.emplace_back(severity, message, location);
}

bool DiagnosticEngine::hasErrors() const {
    return !diagnostics_.empty();
}

}