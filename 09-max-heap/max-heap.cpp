// MaxHeap: array based binary heap, biggest item always on top.
// Parent of i is (i-1)/2. Children of i are 2*i+1 and 2*i+2.
// Compile: g++ -std=c++17 -Wall -Wextra 09-max-heap/max-heap.cpp -o /tmp/maxheap && /tmp/maxheap

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

class MaxHeap {
public:
    void push(int value) {
        data_.push_back(value);
        sift_up(data_.size() - 1);
    }

    void pop() {
        if (data_.empty()) {
            throw std::out_of_range("pop on empty heap");
        }
        data_[0] = data_.back();
        data_.pop_back();
        if (!data_.empty()) {
            sift_down(0);
        }
    }

    int top() const {
        if (data_.empty()) {
            throw std::out_of_range("top on empty heap");
        }
        return data_[0];
    }

    size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }

private:
    static size_t parent(size_t i) { return (i - 1) / 2; }
    static size_t left(size_t i) { return 2 * i + 1; }
    static size_t right(size_t i) { return 2 * i + 2; }

    void sift_up(size_t i) {
        while (i > 0 && data_[i] > data_[parent(i)]) {
            std::swap(data_[i], data_[parent(i)]);
            i = parent(i);
        }
    }

    void sift_down(size_t i) {
        while (true) {
            size_t biggest = i;
            if (left(i) < data_.size() && data_[left(i)] > data_[biggest]) {
                biggest = left(i);
            }
            if (right(i) < data_.size() && data_[right(i)] > data_[biggest]) {
                biggest = right(i);
            }
            if (biggest == i) return;
            std::swap(data_[i], data_[biggest]);
            i = biggest;
        }
    }

    std::vector<int> data_;
};

int main() {
    MaxHeap h;
    assert(h.empty());

    for (int v : {5, 3, 8, 1, 9, 2}) {
        h.push(v);
    }
    assert(h.size() == 6);
    assert(h.top() == 9);

    // Pops must come out biggest first.
    std::vector<int> order;
    while (!h.empty()) {
        order.push_back(h.top());
        h.pop();
    }
    assert(order == std::vector<int>({9, 8, 5, 3, 2, 1}));

    // Duplicates are fine.
    MaxHeap d;
    d.push(4);
    d.push(4);
    d.push(4);
    assert(d.top() == 4);
    d.pop();
    assert(d.top() == 4);

    // Empty pop and top must throw.
    bool threw = false;
    try {
        d.pop();
        d.pop();
        d.pop();
        d.pop();
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    std::cout << "All max heap checks passed.\n";
    return 0;
}
