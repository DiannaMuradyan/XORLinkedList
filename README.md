# 🔗 XOR Linked List in C++

This project implements an **XOR Linked List (XORLL)** in C++ as a template container.  
Unlike traditional linked lists that store both **next** and **previous** pointers, each node in an XOR Linked List stores a single value:  

both = prev ⊕ next


This reduces memory usage but requires careful pointer arithmetic when traversing.  

---

## 🚀 Features

- **Templated Design** → Works with any data type.  
- **Smart Copy/Move Semantics** → Implements deep copy constructor, assignment operator, and move semantics.  
- **Bidirectional Iterator** → Allows traversal in both forward and reverse directions.  
- **Standard List Operations**:
  - `push_back`, `push_front`  
  - `pop_back`, `pop_front`  
  - `insert` at position  
  - `erase` at position  
  - `clean` (clear the list)  
- **Utility Methods**:
  - `front()`, `back()`  
  - `empty()`  
  - `getSize()`  
- **Stream Output Operator (`<<`)** for easy printing.  

---

## 📂 Project Structure

```
.
├── XORList.h # Class definition (template & iterator)
├── XORList.hpp # Method implementations
├── main.cpp # Example usage and test driver
└── README.md # Documentation
```

---

## 🏗️ Compilation

Compile with **C++17 or later**:

```bash
g++ -std=c++17 -o xorll main.cpp
```
