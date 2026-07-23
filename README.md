<p align="center">
  <picture>
    <source
      media="(prefers-color-scheme: dark)"
      srcset=".github/phonk-logo-light.svg">
    <source
      media="(prefers-color-scheme: light)"
      srcset=".github/phonk-logo-dark.svg">
    <img
      src=".github/phonk-logo-dark.svg"
      alt="Phonk logo"
      width="180">
  </picture>
</p>

<h1 align="center">Phonk</h1>

<p align="center">
  <img src="https://github.com/phonk-lang/phonk/actions/workflows/ci.yml/badge.svg" alt="CI">
  <img src="https://img.shields.io/badge/C++-20-blue.svg" alt="C++20">
  <img src="https://img.shields.io/github/v/release/phonk-lang/phonk?include_prereleases" alt="Release">
  <img src="https://img.shields.io/badge/license-MIT%20%7C%20Apache--2.0-green.svg" alt="License">
  <img src="https://img.shields.io/github/last-commit/phonk-lang/phonk.svg" alt="Last commit">
</p>

<p align="center">
  A programming language and compiler project focused on clarity and performance.
</p>

> [!WARNING]
> Phonk is in early development and is not stable yet.

## About

Phonk is a programming language and compiler written in C++20.

## Building

### Requirements

* C++20 compiler
* CMake
* Git

### Installation

```bash
git clone https://github.com/phonk-lang/phonk.git
cd phonk
```

### Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## Testing

```bash
ctest --test-dir build --output-on-failure --build-config Release
```

## Documentation

Project documentation is available in [`docs/`](docs/).

## Contributing

See [`CONTRIBUTING.md`](CONTRIBUTING.md) before opening a pull request.

## License

Phonk is available under the MIT License or Apache License 2.0.
