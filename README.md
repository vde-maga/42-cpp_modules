# 📘 42 C++ Modules

This repository contains my solutions to the 42 C++ modules (00 to 09). Each file demonstrates a specific concept or set of concepts from C++ (C++98 to C++ canonical form), following the school's progression.

---

## Module 00 — Basics & Syntax

| File              | Concept                                                                         |
|-------------------|---------------------------------------------------------------------------------|
| ex00              | Command-line arguments, basic output                                            |
| ex01              | Classes, private attributes, basic I/O, std::setw, string truncation            |

---

## Module 01 — Memory, References, and File I/O

| File              | Concept                                          |
|-------------------|--------------------------------------------------|
| ex00              | Stack vs heap allocation, constructors           |
| ex01              | Heap allocation, delete                          |
| ex02              | References vs pointers                           |
| ex03              | Using references, initializer lists              |
| ex04              | File reading/writing, string manipulation        |
| ex05              | Pointers to member functions                     |
| ex06              | Switch statments                                 |

---

## Module 02 — OOP and Ad-hoc Polymorphism

| File                  | Concept                                             |
|-----------------------|-----------------------------------------------------|
| ex00                  | Orthodox Canonical Form, fixed-point arithmetic     |
| ex01                  | Copy constructor, assignment operator               |
| ex02                  | Roundf, operator overloading, static polymorphism   |

---

## 📦 Module 03 — Inheritance & Polymorphism
| File                    | Concept                                       |
|-------------------------|-----------------------------------------------|
| ex00                    | Orthodox Canonical Form                       |
| ex01                    | Basic inheritance                             |
| ex02                    | Derived classes and method specialization     |
| ex03                    | Multiple inheritance, virtual inheritance     |

---

## Module 04 — Abstract Classes & Interfaces

| File                  | Concept                                                   |
|-----------------------|-----------------------------------------------------------|
| ex00                  | Abstract classes, virtual methods, dynamic polymorphism   |
| ex01                  | Deep copies, dynamic memory in class members              |
| ex02                  | Abstract classes, pure virtual functions                  |
| ex03                  | Interfaces, pure abstract classes                         |

---

## Module 05 — Exceptions

| File               | Concept                                           |
|--------------------|---------------------------------------------------|
| ex00               | Exceptions, try and catch, custom error handling  |
| ex01               | Virtual methods, operator overload                |
| ex02               | Abstract classes, polymorphism                    |
| ex03               | Switch Case                                       |

---

## Module 06 — Casting

| File                  | Concept                                                  |
|-----------------------|----------------------------------------------------------|
| ex00                  | Static casting, type identification, static functions    |
| ex01                  | Reinterpret casting, uintptr_t                           |
| ex02                  | Dynamic casting by pointer and reference, try and catch  |

---

## Module 07 — Templates

| File                | Concept                                          |
|---------------------|--------------------------------------------------|
| ex00                | Function templates                               |
| ex01                | Function template overload, function pointer     |
| ex02                | Class templates                                  |

---

## Module 08 — Containers & STL

| File                | Concept                                  |
|---------------------|------------------------------------------|
| ex00                | Template functions with containers       |
| ex01                | Efficient container algorithms and logic |
| ex02                | Iterators and container adpaters         |

---

## Module 09 — Advanced Containers & STL

| File                | Concept                                   |
|---------------------|-------------------------------------------|
| ex00                | std::map                                  |
| ex01                | std::stack                                |
| ex02                | Ford-Johnson algorithm, std::deque        |

---

## Tests

Where applicable, I’ve included test files or sample usage to demonstrate and validate each concept.

---

## Build & Run

All files can be compiled with a simple `Makefile` or using:
```bash
make
```
Or to include memory leak verification use (only in exercises where applicable):
```bash
make val
```
