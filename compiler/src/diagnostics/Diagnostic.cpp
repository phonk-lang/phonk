//
// Created by maxmo on 6/20/2026.
//

#include <phonk/diagnostics/Diagnostic.hpp>

namespace phonk::diagnostics {

Diagnostic::Diagnostic(Severity severity, std::string message,
                       source::SourceLocation location) : severity_(severity),
                                                          message_(std::move(message)),
                                                          location_(location) {

}

Severity Diagnostic::getSeverity() const {
    return severity_;
}

std::string Diagnostic::getMessage() const {
    return message_;
}

const source::SourceLocation& Diagnostic::getLocation() const {
    return location_;
}

}