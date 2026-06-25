//
// Created by maxmo on 6/21/2026.
//

#ifndef PHONK_SOURCE_RANGE_HPP
#define PHONK_SOURCE_RANGE_HPP
#include <phonk/source/source_location.hpp>

namespace phonk::source {

struct SourceRange {
    SourceLocation begin;
    SourceLocation end;
};

}

#endif //PHONK_SOURCE_RANGE_HPP