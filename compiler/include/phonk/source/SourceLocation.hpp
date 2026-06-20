#ifndef PHONK_SOURCELOCATION_HPP
#define PHONK_SOURCELOCATION_HPP
#include <cstddef>

namespace phonk::source {

struct SourceLocation {
    size_t line;
    size_t col;
};

}

#endif