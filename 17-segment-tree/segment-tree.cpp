// SegmentTree: range sum queries plus point updates, both logarithmic.
// Array of size 4*n holds the tree. Node i covers a range,
// its children 2*i and 2*i+1 split that range in half.
// Compile: g++ -std=c++17 -Wall -Wextra 17-segment-tree/segment-tree.cpp -o /tmp/seg && /tmp/seg

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <vector>

class SegmentTree {
public:
    explicit SegmentTree(const std::vector<int>& data)
        : n_(data.size()), tree_(4 * data.size(), 0) {
        if (data.empty()) {
            throw std::invalid_argument("need at least one element");
        }
        build(1, 0, n_ - 1, data);
    }

    // Sum over [l, r], inclusive.
    int query(int l, int r) const {
        if (l < 0 || r >= (int)n_ || l > r) {
            throw std::out_of_range("bad query range");
        }
        return ask(1, 0, n_ - 1, l, r);
    }

    void update(int index, int value) {
        if (index < 0 || index >= (int)n_) {
            throw std::out_of_range("bad update index");
        }
        set(1, 0, n_ - 1, index, value);
    }

    size_t size() const { return n_; }

private:
    void build(int node, int lo, int hi, const std::vector<int>& data) {
        if (lo == hi) {
            tree_[node] = data[lo];
            return;
        }
        int mid = (lo + hi) / 2;
        build(2 * node, lo, mid, data);
        build(2 * node + 1, mid + 1, hi, data);
        tree_[node] = tree_[2 * node] + tree_[2 * node + 1];
    }

    int ask(int node, int lo, int hi, int l, int r) const {
        if (r < lo || hi < l) return 0;          // outside, contributes nothing
        if (l <= lo && hi <= r) return tree_[node];  // fully inside, take it
        int mid = (lo + hi) / 2;                 // partial, ask both halves
        return ask(2 * node, lo, mid, l, r) + ask(2 * node + 1, mid + 1, hi, l, r);
    }

    void set(int node, int lo, int hi, int index, int value) {
        if (lo == hi) {
            tree_[node] = value;
            return;
        }
        int mid = (lo + hi) / 2;
        if (index <= mid) {
            set(2 * node, lo, mid, index, value);
        } else {
            set(2 * node + 1, mid + 1, hi, index, value);
        }
        tree_[node] = tree_[2 * node] + tree_[2 * node + 1];
    }

    size_t n_;
    std::vector<int> tree_;
};

int main() {
    SegmentTree st({1, 3, 5, 7, 9, 11});
    assert(st.query(0, 5) == 36);
    assert(st.query(1, 3) == 15);
    assert(st.query(2, 2) == 5);

    st.update(1, 10);  // 3 becomes 10
    assert(st.query(0, 5) == 43);
    assert(st.query(1, 3) == 22);
    assert(st.query(0, 0) == 1);

    // Single element tree.
    SegmentTree one({42});
    assert(one.query(0, 0) == 42);
    one.update(0, 7);
    assert(one.query(0, 0) == 7);

    // Bad ranges throw instead of silently answering wrong.
    bool threw = false;
    try {
        st.query(3, 1);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    threw = false;
    try {
        st.update(99, 1);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    std::cout << "All segment tree checks passed.\n";
    return 0;
}
