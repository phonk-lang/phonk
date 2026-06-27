include(FetchContent)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)


add_executable(phonk_tests
        lexer/lexer_tests.cpp
        lexer/lexer_tests.cpp
)

target_link_libraries(phonk_tests
        PRIVATE
        phonkc
        GTest::gtest_main
)


include(GoogleTest)

gtest_discover_tests(phonk_tests)