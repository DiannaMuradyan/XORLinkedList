#pragma once
#include <cstdint>
#include <iostream>
#include <iterator>

template <typename T>
class XORLL {
private:
    struct Node;
    class Iterator;

public:
    //ctors of list
    XORLL ();
    XORLL (const XORLL& rhs);
    XORLL& operator=(const XORLL& rhs);

    XORLL(XORLL&& rhs) noexcept;
    XORLL& operator=(XORLL&& rhs) noexcept;

    ~XORLL();

    // Iterator related
	Iterator begin();
	Iterator end();
	Iterator rbegin();
	Iterator rend();

    std::size_t getSize() const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const XORLL<U>& list);  //wefwefwefjewhfieubfeowgfoewgfcowe

    T front() const;
    T back() const;
    bool empty() const;

    void push_back(T val);
    void push_front(T val);

    void pop_back();
    void pop_front();

    void insert(T val, int pos);
    void erase(int pos);
    void clean();
    static Node* XOR(Node* p1, Node* p2);

private:
    Node* m_head{};
    Node* m_tail{};
    std::size_t m_size{};


    struct Node {
        T val{};
        Node* both{};
    };

    class Iterator {
    public:
        using iterator_type = std::bidirectional_iterator_tag;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;

        Iterator(Node* prev_, Node* curr);
        reference operator*();
        pointer operator->();

        Iterator& operator++();
        Iterator operator++(int); 

        Iterator& operator--();
        Iterator operator--(int); 

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node* m_prev{};
        Node* m_curr{};
    };

};


#include "XORList.hpp"