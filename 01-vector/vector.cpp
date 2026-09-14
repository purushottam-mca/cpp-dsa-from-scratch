// MyVector: a simple dynamic array built from scratch.
// Compile: g++ -std=c++17 -Wall -Wextra 01-vector/vector.cpp -o /tmp/vector && /tmp/vector

#include <cassert>
#include <iostream>
#include <stdexcept>

template <typename T>
class MyVector {
public:
    MyVector() : data_(nullptr), size_(0), capacity_(0) {}

    ~MyVector() { delete[] data_; }

    // No copying for now to keep the interview version short.
    // Rule of three note: if you add copy, also add copy assign.
    MyVector(const MyVector&) = delete;
    MyVector& operator=(const MyVector&) = delete;

    void push_back(const T& value) {
        if (size_ == capacity_) {
            grow();
        }
        data_[size_] = value;
        ++size_;
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("pop_back on empty vector");
        }
        --size_;
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
        return data_[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("index out of range");
        }
        return data_[index];
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
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
    MyVector<int> v;
    assert(v.empty());

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    assert(v.size() == 3);
    assert(v[0] == 10 && v[1] == 20 && v[2] == 30);

    v[1] = 99;
    assert(v[1] == 99);

    v.pop_back();
    assert(v.size() == 2);

    // Force a few grows and check everything survives.
    for (int i = 0; i < 100; ++i) {
        v.push_back(i);
    }
    assert(v.size() == 102);
    assert(v.capacity() >= v.size());

    // Empty pop must throw, not crash silently.
    MyVector<int> e;
    bool threw = false;
    try {
        e.pop_back();
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    std::cout << "All vector checks passed. size=" << v.size()
              << " capacity=" << v.capacity() << "\n";
    return 0;
}
