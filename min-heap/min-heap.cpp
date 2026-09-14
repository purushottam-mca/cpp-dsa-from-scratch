// MinHeap: array based binary heap, smallest item always on top.
// Same shape as MaxHeap with every comparison flipped.
// Compile: g++ -std=c++17 -Wall -Wextra min-heap/min-heap.cpp -o /tmp/minheap && /tmp/minheap

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

class MinHeap {
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
        while (i > 0 && data_[i] < data_[parent(i)]) {
            std::swap(data_[i], data_[parent(i)]);
            i = parent(i);
        }
    }

    void sift_down(size_t i) {
        while (true) {
            size_t smallest = i;
            if (left(i) < data_.size() && data_[left(i)] < data_[smallest]) {
                smallest = left(i);
            }
            if (right(i) < data_.size() && data_[right(i)] < data_[smallest]) {
                smallest = right(i);
            }
            if (smallest == i) return;
            std::swap(data_[i], data_[smallest]);
            i = smallest;
        }
    }

    std::vector<int> data_;
};

int main() {
    MinHeap h;
    assert(h.empty());

    for (int v : {5, 3, 8, 1, 9, 2}) {
        h.push(v);
    }
    assert(h.size() == 6);
    assert(h.top() == 1);

    // Pops must come out smallest first.
    std::vector<int> order;
    while (!h.empty()) {
        order.push_back(h.top());
        h.pop();
    }
    assert(order == std::vector<int>({1, 2, 3, 5, 8, 9}));

    // Classic use: keep k largest from a stream with a min heap of size k.
    MinHeap top3;
    for (int v : {5, 1, 9, 3, 7, 2, 8}) {
        top3.push(v);
        if (top3.size() > 3) {
            top3.pop();  // drop the smallest of the four, keep the big three
        }
    }
    assert(top3.size() == 3);
    assert(top3.top() == 7);  // the top three are 7, 8, 9

    bool threw = false;
    MinHeap e;
    try {
        e.top();
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    std::cout << "All min heap checks passed.\n";
    return 0;
}
