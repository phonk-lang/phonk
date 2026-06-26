#ifndef PHONK_SOURCE_LOCATION_HPP
#define PHONK_SOURCE_LOCATION_HPP
#include <cstddef>

namespace phonk::source {

struct SourceLocation {
    size_t offset;
    size_t line;
    size_t column;
};

}

#endif