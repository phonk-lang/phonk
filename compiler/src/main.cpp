//
// Created by maxmo on 6/20/2026.
//

#include <iostream>
#include <phonk/compiler.hpp>

int main() {
    phonk::Compiler compiler;

    compiler.addVirtualFile("test.phonk", "print(\"Hello World\"");

    return compiler.compile();
}
