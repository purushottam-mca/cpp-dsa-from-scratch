// MyQueue: first in, first out, with a circular array.
// Compile: g++ -std=c++17 -Wall -Wextra 03-queue/queue.cpp -o /tmp/queue && /tmp/queue

#include <cassert>
#include <iostream>
#include <stdexcept>

template <typename T>
class MyQueue {
public:
    MyQueue() : data_(nullptr), head_(0), size_(0), capacity_(0) {}
    ~MyQueue() { delete[] data_; }

    MyQueue(const MyQueue&) = delete;
    MyQueue& operator=(const MyQueue&) = delete;

    void enqueue(const T& value) {
        if (size_ == capacity_) {
            grow();
        }
        size_t tail = (head_ + size_) % capacity_;
        data_[tail] = value;
        ++size_;
    }

    void dequeue() {
        if (size_ == 0) {
            throw std::out_of_range("dequeue on empty queue");
        }
        head_ = (head_ + 1) % capacity_;
        --size_;
    }

    T& front() {
        if (size_ == 0) {
            throw std::out_of_range("front on empty queue");
        }
        return data_[head_];
    }

    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

private:
    void grow() {
        size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[(head_ + i) % capacity_];
        }
        delete[] data_;
        data_ = new_data;
        head_ = 0;
        capacity_ = new_cap;
    }

    T* data_;
    size_t head_;
    size_t size_;
    size_t capacity_;
};

int main() {
    MyQueue<int> q;
    assert(q.empty());

    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    assert(q.front() == 1);

    q.dequeue();
    assert(q.front() == 2);
    assert(q.size() == 2);

    // Wrap around the circle: remove all, add again.
    q.dequeue();
    q.dequeue();
    assert(q.empty());
    q.enqueue(10);
    q.enqueue(20);
    assert(q.front() == 10);
    q.dequeue();
    assert(q.front() == 20);

    // Push many to force grows with a moved head.
    for (int i = 0; i < 100; ++i) {
        q.enqueue(i);
    }
    assert(q.size() == 101);

    bool threw = false;
    MyQueue<int> e;
    try {
        e.dequeue();
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    std::cout << "All queue checks passed. size=" << q.size() << "\n";
    return 0;
}
