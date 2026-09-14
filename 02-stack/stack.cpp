// MyStack: last in, first out. Built on a simple growing array.
// Compile: g++ -std=c++17 -Wall -Wextra stack/stack.cpp -o /tmp/stack && /tmp/stack

#include <cassert>
#include <iostream>
#include <stdexcept>

template <typename T>
class MyStack {
public:
    MyStack() : data_(nullptr), size_(0), capacity_(0) {}
    ~MyStack() { delete[] data_; }

    MyStack(const MyStack&) = delete;
    MyStack& operator=(const MyStack&) = delete;

    void push(const T& value) {
        if (size_ == capacity_) {
            grow();
        }
        data_[size_] = value;
        ++size_;
    }

    void pop() {
        if (size_ == 0) {
            throw std::out_of_range("pop on empty stack");
        }
        --size_;
    }

    T& top() {
        if (size_ == 0) {
            throw std::out_of_range("top on empty stack");
        }
        return data_[size_ - 1];
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

private:
    void grow() {
        size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

    T* data_;
    size_t size_;
    size_t capacity_;
};

int main() {
    MyStack<int> s;
    assert(s.empty());

    s.push(1);
    s.push(2);
    s.push(3);
    assert(s.size() == 3);
    assert(s.top() == 3);

    s.pop();
    assert(s.top() == 2);
    assert(s.size() == 2);

    s.pop();
    s.pop();
    assert(s.empty());

    bool threw = false;
    try {
        s.pop();
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    threw = false;
    try {
        s.top();
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    std::cout << "All stack checks passed.\n";
    return 0;
}
