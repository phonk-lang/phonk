add_library(phonkc STATIC
        src/source/source_file.cpp
        src/diagnostics/diagnostic.cpp
        src/diagnostics/diagnostic_engine.cpp
        src/lexer/lexer.cpp
        src/compiler.cpp
)

target_include_directories(phonkc PUBLIC include)
target_compile_features(phonkc PUBLIC cxx_std_20)

add_executable(phonk
        src/main.cpp
)

target_link_libraries(phonk PRIVATE phonkc)

if (PHONK_ENABLE_WARNINGS)
    target_compile_options(phonkc PRIVATE
            $<$<CXX_COMPILER_ID:Clang,AppleClang,GNU>:
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wshadow
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Woverloaded-virtual
            -Wnull-dereference
            >

            $<$<CXX_COMPILER_ID:MSVC>:
            /W4
            /permissive-
            >
    )
endif ()