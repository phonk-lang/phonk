add_executable(phonk
        src/main.cpp
        src/source/source_file.cpp
        include/phonk/source/source_location.hpp
        include/phonk/diagnostics/Diagnostic.hpp
        src/diagnostics/Diagnostic.cpp
        src/diagnostics/diagnostic_engine.cpp
        include/phonk/diagnostics/diagnostic_engine.hpp
        include/phonk/lexer/Token.hpp
        src/lexer/Lexer.cpp
        include/phonk/lexer/Lexer.hpp
        include/phonk/source/source_range.hpp
)

target_include_directories(phonk PRIVATE include)

target_compile_features(phonk PRIVATE cxx_std_20)