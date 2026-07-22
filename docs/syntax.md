# Phonk Language Syntax

This document defines the syntax of the Phonk programming language.

## 1. Source Files

Phonk uses the following file extension: `.phonk`

A source file may contain:
* Statements
* Functions
* Comments

## 2. Identifiers

Identifiers name functions, variables, types, and other language elements.

An identifier may contain:
* Letters
* Digits
* Underscores

An identifier may not:
* Start with a digit
* Match a reserved keyword
* Contain whitespaces

Examples of valid identifiers:
* `value`
* `myVar1`
* `GetNumber`
* `player_score`

Examples of invalid identifiers:
* `1number`
* `phonk`
* `return`
* `User Name`

Identifiers in Phonk are case-sensitive.

Example:

```phonk
myVar = 10;
print(MyVar); // unknown identifier error
```

## 3. Keywords

The following keywords are reserved:

| Keyword   | Purpose                                                |
|-----------|--------------------------------------------------------|
| `phonk`   | Signals the start of a function declaration.           |
| `return`  | Returns a value at the end of a function.              |
| `returns` | Signals the return type in the function declaration.   |
| `if`      | Begins an if-statement.                                |
| `else`    | Adds an alternative outcome to an if-statement.        |
| `for`     | Signals the start of a for-loop.                       |
| `while`   | Signals the start of a while-loop.                     |
| `break`   | Exits a loop.                                          |
| `true`    | Represents a boolean value of true.                    |
| `false`   | Represents a boolean value of false.                   |
| `and`     | Adds a condition to a boolean expression.              |
| `or`      | Adds an alternative condition to a boolean expression. |
| `not`     | Negates a boolean expression.                          |

## 4. Whitespace

Whitespace includes:
* Spaces
* Tabs
* New lines

The compiler will ignore whitespace between identifiers, symbols, keywords, and at the end of a statement.
