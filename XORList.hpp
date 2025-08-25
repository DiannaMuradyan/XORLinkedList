#include "XORList.tpp"

//it ctors and operators
template <typename T>
XORLL<T>::Iterator::Iterator(XORLL<T>::Node* prev_, XORLL<T>::Node* curr) : m_prev(prev_), m_curr(curr) {}

template <typename T>
typename XORLL<T>::Iterator::reference XORLL<T>::Iterator::operator*() {
    return this ->m_curr ->val;
}


template <typename T> 
typename XORLL<T>::Iterator::pointer XORLL<T>::Iterator::operator->() {
    return this ->m_curr;
}

template <typename T>
typename XORLL<T>::Node* XORLL<T>::XOR(XORLL<T>::Node* p1, XORLL<T>::Node* p2) {
    return reinterpret_cast<XORLL<T>::Node*>(reinterpret_cast<uintptr_t>(p1)^reinterpret_cast<uintptr_t>(p2));
}

template <typename T>
typename XORLL<T>::Iterator&  XORLL<T>::Iterator::operator++() {
    XORLL<T>::Node* next = XOR(m_curr ->both, m_prev);;
    m_prev = m_curr;
    m_curr = next;
    return *this;
}

template <typename T>
typename XORLL<T>::Iterator XORLL<T>::Iterator::operator++(int) {
    XORLL::Iterator tmp {*this};
    ++(*this);
    return tmp;
}


template <typename T>
typename XORLL<T>::Iterator&  XORLL<T>::Iterator::operator--() {
    if (m_curr == nullptr) {
        m_curr = m_prev;
        m_prev = m_curr ? XOR(m_prev ->both, nullptr): nullptr;
    }
    else if (m_prev == nullptr) {
        m_curr = nullptr;
    }
    else {
        XORLL<T>::Node* prevprev = XORLL<T>::XOR(m_curr, m_prev ->both);
        m_curr = m_prev;
        m_prev = prevprev;
    }
    return *this;
}


template <typename T>
typename XORLL<T>::Iterator XORLL<T>::Iterator::operator--(int) {
    XORLL<T>::Iterator tmp {*this};
    --(*this);
    return tmp;
}


template <typename T>
bool XORLL<T>::Iterator::operator==(const XORLL<T>::Iterator& other) const {
    return (m_curr == other.m_curr);
}


template <typename T>
bool XORLL<T>::Iterator::operator!=(const XORLL<T>::Iterator& other) const {
    return !(*this == other);
}


//it functions for list
template <typename T>
typename XORLL<T>::Iterator XORLL<T>::begin() {
    return typename XORLL<T>::Iterator::Iterator{m_head, nullptr};
}

template <typename T>
typename XORLL<T>::Iterator XORLL<T>::end() {
    return XORLL<T>::Iterator{m_tail, nullptr};
}


template <typename T>
typename XORLL<T>::Iterator XORLL<T>::rbegin() {
    auto it = XORLL<T>::end();
    --it;
    return it;
}

template <typename T>
typename XORLL<T>::Iterator XORLL<T>::rend() {
    auto it = XORLL<T>::begin();
    --it;
    return it;
}


//list ctors
template <typename T>
XORLL<T>::XORLL() = default;


template <typename T>
XORLL<T>::XORLL(const XORLL<T>& rhs) {
    m_head = m_tail = nullptr;
    m_size = 0;
    auto tmp_rhs_head = rhs.m_head;
    XORLL<T>::Node* prev_ = nullptr;

    while(tmp_rhs_head) {
        push_back(tmp_rhs_head ->val);
        auto next = XOR(tmp_rhs_head->both, prev_);
        prev_ = tmp_rhs_head;
        tmp_rhs_head = next;
    }
}


//list push_back()
template <typename T>
void XORLL<T>::push_back(T val) {
    auto new_obj = new XORLL<T>::Node{val};
    if (m_head == nullptr) {
        m_head = m_tail = new_obj;
    }
    else {
        new_obj ->both = m_tail; //XOR(m_tail, nullptr)
        m_tail ->both = XOR(m_tail ->both, new_obj);
        m_tail = new_obj;
    }
    ++m_size;
}


//clean()
template <typename T>
void XORLL<T>::clean() {
    XORLL<T>::Node* prev_{nullptr};
    while (m_head != nullptr) {
        auto next = XOR(m_head ->both, prev_);
        prev_ = m_head;
        delete m_head;
        m_head = next;
    }
    m_head = m_tail = nullptr;
    m_size = 0;
    return;
}

template <typename T>
XORLL<T>& XORLL<T>::operator=(const XORLL& rhs) {
    if (this != &rhs) {
        clean();
        auto tmp_rhs_head = rhs.m_head;
        XORLL<T>::Node* prev_ = nullptr;
        
        while(tmp_rhs_head) {
            push_back(tmp_rhs_head ->val);
            auto next = XOR(tmp_rhs_head->both, prev_);
            prev_ = tmp_rhs_head;
            tmp_rhs_head = next;
        }
    }
    return *this;
}


template <typename T>
XORLL<T>::XORLL(XORLL<T>&& rhs) noexcept : m_head(rhs.m_head), m_tail(rhs.m_tail), m_size(rhs.m_size) {
    rhs.m_head = rhs.m_tail = nullptr;
    rhs.m_size = 0;
}


template <typename T>
XORLL<T>& XORLL<T>::operator=(XORLL<T>&& rhs) noexcept {
    if (this != &rhs) {
        clean();
        m_head = rhs.m_head;
        m_tail = rhs.m_tail;
        m_size = rhs.m_size;

        rhs.m_head = rhs.m_tail = nullptr;
        rhs.m_size = 0;
    }
    return *this;
}


//list dtor
template <typename T> 
XORLL<T>::~XORLL() {
    clean();
}

template <typename T>
std::size_t XORLL<T>::getSize() const {
    return m_size;
}


template <typename T>
T XORLL<T>::front() const{
    return m_head ->val;
}

template <typename T> 
T XORLL<T>::back() const {
    return m_tail ->val;
}

template <typename T>
bool XORLL<T>::empty() const {
    return (m_size == 0);
}


template <typename T>
void XORLL<T>::push_front(T val) {
    auto new_node = new XORLL<T>::Node{val};
    if(m_head == nullptr) {
        m_head = m_tail = new_node;
    }
    else {
        new_node ->both = m_head; //or  XOR(m_head, nullptr)
        m_head ->both = XOR(new_node, XOR(m_head ->both, nullptr));//or XOR(new_node, m_head ->both)
        m_head = new_node;
    }
    ++m_size;
    return;
} 


template <typename T>
void XORLL<T>::pop_front() {
    if (m_head == nullptr) {
        throw std::out_of_range("XORLL is empty");
    }
    else if (m_head == m_tail) {
        delete m_head;
        m_head = m_tail = nullptr;
    }
    else {
        auto prev_ = m_head;
        m_head = XOR(m_head ->both, nullptr);
        m_head ->both = XOR(nullptr, XOR(m_head ->both, prev_));
        delete prev_;
    }
    --m_size;
    return;
}


template <typename T>
void XORLL<T>::pop_back() {
    if (m_head == nullptr) {
        throw std::out_of_range("XORLL is empty");
    }
    else if (m_head == m_tail) {
        delete m_head;
        m_head = m_tail = nullptr;
    }
    else {
        auto tail_prev = m_tail ->both; //or XOR(m_tail ->both, nullptr)
        tail_prev ->both = XOR(nullptr, XOR(m_tail, tail_prev ->both));
        delete m_tail;
        m_tail = tail_prev;
    }
    --m_size;
    return;
}



template <typename T>
void XORLL<T>::insert(T val, int pos) {
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("invalid position");
    }
    else if (pos == 0) {
        push_front(val);
    }
    else {
        auto new_node = new XORLL<T>::Node{val};
        auto tmp_head{m_head};
        auto next{m_head};
        XORLL<T>::Node* prev_ = nullptr;

        for (int i = 1; i < pos; ++i) {
            next = XOR(tmp_head ->both, prev_);
            prev_ = tmp_head;
            tmp_head = next;
        } 

        next = XOR(tmp_head ->both, prev_);
        new_node ->both = XOR(tmp_head, next);

        tmp_head ->both = XOR(XOR(tmp_head ->both, next), new_node);
        next ->both = XOR(XOR(next ->both, tmp_head), new_node);
    }
    ++m_size;
    return;
}



template <typename T> 
void XORLL<T>::erase(int pos) {
    if (pos < 0 || pos > m_size) {
        throw std::out_of_range("invalid position");
    }
    else if (pos == 0) {
        pop_front();
    }
    else if (pos == m_size) {
        pop_back();
    }
    else {
        auto tmp_head{m_head};
        XORLL<T>::Node* prev_{nullptr};
        auto next{m_head};

        while (pos--) {
            next = XOR(tmp_head ->both, prev_);
            prev_ = tmp_head;
            tmp_head = next;
        }

        next = XOR(prev_, tmp_head ->both);
        prev_ ->both = XOR(XOR(prev_ ->both, tmp_head), next);
        next ->both = XOR(XOR(tmp_head, next ->both), prev_);

        delete tmp_head;
    }
    --m_size;
    return;
}


template <typename T>
std::ostream& operator<<(std::ostream& os, const XORLL<T>& list) {
    auto tmp_head{list.m_head};
    typename XORLL<T>::Node* prev_ = nullptr;
    typename XORLL<T>::Node* next = nullptr;

    while (tmp_head != nullptr) {
        os<<tmp_head ->val<<"-->";
        next = XORLL<T>::XOR(tmp_head ->both, prev_);
        prev_ = tmp_head;
        tmp_head = next;
    }
    os<<"nullptr\n";
    return os;
}