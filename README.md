# XORLinkedList (C++)

An implementation of a **memory-efficient doubly linked list** in C++ using the XOR linked list technique.  
This data structure stores the XOR of previous and next node addresses instead of storing two explicit pointers,  
reducing memory usage compared to a traditional doubly linked list.

---

## ✨ Features

- Space-efficient list nodes (`prev ^ next` pointer trick).
- `push_front`, `push_back`, `pop_front`, `pop_back`.
- Insert and erase at arbitrary positions.
- Forward and reverse traversal via custom iterators.
- STL-style iterators (`begin`, `end`, `rbegin`, `rend`).
- Stream output (`operator<<`) for easy debugging.

---

## ⚙️ How it works

Each node stores a single pointer `both`, which is the XOR of the addresses of the previous and next nodes:

