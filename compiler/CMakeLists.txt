add_executable(phonk
        src/main.cpp
        src/source/source_file.cpp
        include/phonk/source/source_location.hpp
        include/phonk/diagnostics/diagnostic.hpp
        src/diagnostics/diagnostic.cpp
        src/diagnostics/diagnostic_engine.cpp
        include/phonk/diagnostics/diagnostic_engine.hpp
        include/phonk/lexer/token.hpp
        src/lexer/lexer.cpp
        include/phonk/lexer/lexer.hpp
        include/phonk/source/source_range.hpp
        src/compiler.cpp
        include/phonk/compiler.hpp
)

target_include_directories(phonk PRIVATE include)

target_compile_features(phonk PRIVATE cxx_std_20)
