add_executable(phonk
        src/main.cpp
        src/source/SourceFile.cpp
        include/phonk/source/SourceLocation.hpp
        include/phonk/diagnostics/Diagnostic.hpp
        src/diagnostics/Diagnostic.cpp
        src/diagnostics/DiagnosticEngine.cpp
        include/phonk/diagnostics/DiagnosticEngine.hpp
)

target_include_directories(phonk PRIVATE include)

target_compile_features(phonk PRIVATE cxx_std_20)