//
// Created by maxmo on 6/21/2026.
//

#ifndef PHONK_SOURCERANGE_HPP
#define PHONK_SOURCERANGE_HPP
#include <phonk/source/SourceLocation.hpp>

namespace phonk::source {

struct SourceRange {
    SourceLocation begin;
    SourceLocation end;
};

}

#endif //PHONK_SOURCERANGE_HPP
