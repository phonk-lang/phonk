## P.H.O.N.K.

![Tests](https://github.com/P-H-O-N-K/phonk/actions/workflows/tests.yml/badge.svg)
![C++](https://img.shields.io/badge/C++-20-blue.svg)
![License](https://img.shields.io/badge/license-MIT%20%7C%20Apache--2.0-green.svg)
![Last Commit](https://img.shields.io/github/last-commit/P-H-O-N-K/phonk.svg)
![Repo Size](https://img.shields.io/github/repo-size/P-H-O-N-K/phonk.svg)

**Pythonic Syntax. C++ Speed. Low Overhead.**

P.H.O.N.K. is a transpiled programming language that combines Python-inspired readability with the performance of native C++ binaries.

Write simple, readable code. Compile to optimized C++. Release the beast.

---

## What is P.H.O.N.K.?

P.H.O.N.K. is a custom language developed as an AP Computer Science final project.

The goal is simple:

* Easy-to-read syntax
* Fast execution
* Beginner-friendly design
* Native compilation through C++

Instead of running through an interpreter or virtual machine, P.H.O.N.K. transpiles directly into C++ source code and then uses a standard C++ compiler to generate optimized machine code.

---

## Features

### Pythonic Syntax, C++ Speed

Write clean code without excessive syntax while still getting native performance.

### Intuitive Type System

A streamlined type system inspired by both Python and C++.

### Zero-Overhead Transpilation

No virtual machine.

No heavyweight runtime.

Just generated C++ and compiler optimizations.

### Built for Learning

P.H.O.N.K. is designed to be approachable for beginners while remaining powerful enough for advanced programming concepts.

---

## Compilation Pipeline

```text
.phonk Source File
        │
        ▼
P.H.O.N.K. Transpiler
        │
        ▼
Generated C++ (.cpp)
        │
        ▼
g++ / clang++
        │
        ▼
Native Executable
```

---

## Example

### Basic Program

```phonk
x = 10;
y = 20;

if (x < y) {
    print("hello");
}
```

### Functions and Control Flow

```phonk
phonk add(a, b) {
    return a + b;
}

phonk isEven(n) {
    if (n % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

while (i <= 10) {
    sum = add(sum, i);

    if (isEven(i)) {
        print("even");
    } else {
        print("odd");
    }

    i = i + 1;
}

print(sum);
```

---

## Installation

### Prerequisites

* Git
* C++20 compatible compiler

  * GCC 11+
  * Clang 14+
  * MSVC with C++20 support

### Clone the Repository

```bash
git clone https://github.com/phonk-lang/phonk
cd phonk
```

### Build

```bash
# Build instructions coming soon
```

### Testing

P.H.O.N.K. uses GoogleTest for automated testing.

Run tests:

```bash
cmake -B build
cmake --build build
cd build
ctest --output-on-failure
```

### Run

```bash
# Usage instructions coming soon
```

---

## Architecture

P.H.O.N.K. follows a transpilation-based architecture:

```text
P.H.O.N.K. Source
        │
        ▼
Lexer
        │
        ▼
Parser
        │
        ▼
Semantic Validation
        │
        ▼
C++ Code Generation
        │
        ▼
g++ / clang++
        │
        ▼
Executable Binary
```

By targeting C++, P.H.O.N.K. can leverage decades of compiler optimizations while maintaining a clean and approachable syntax.

---

## Performance

P.H.O.N.K. transpiles directly to C++, allowing generated programs to benefit from native compiler optimizations.

> Note: Any benchmark numbers shown in demonstrations are illustrative and may not reflect real-world performance.

---

## Project Status

Active Development

This project is currently being developed as an educational programming language and transpiler.

Features, syntax, and compiler behavior may change.

---

## Contributors

Jasio Adorno

Maxwell Morgan


---

## License

P.H.O.N.K. is licensed under both the Apache License (Version 2.0) and the MIT license.

For more information, see [LICENSE-APACHE](LICENSE-APACHE) and [LICENSE-MIT](LICENSE-MIT).

---

*"Everything you love about Python. Everything you need from C++."*
