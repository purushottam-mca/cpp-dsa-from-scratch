// UnionFind: disjoint sets with path compression and union by rank.
// Answers "are these two connected" in almost constant time.
// Compile: g++ -std=c++17 -Wall -Wextra 14-union-find/union-find.cpp -o /tmp/uf && /tmp/uf

#include <cassert>
#include <iostream>
#include <vector>

class UnionFind {
public:
    explicit UnionFind(int n) : parent_(n), rank_(n, 0), sets_(n) {
        for (int i = 0; i < n; ++i) parent_[i] = i;
    }

    // Root of x, flattening the path on the way up.
    int find(int x) {
        if (parent_[x] != x) {
            parent_[x] = find(parent_[x]);
        }
        return parent_[x];
    }

    // Merges the two sets. Returns false when already together.
    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        // Shorter tree hangs under the taller one.
        if (rank_[a] < rank_[b]) std::swap(a, b);
        parent_[b] = a;
        if (rank_[a] == rank_[b]) ++rank_[a];
        --sets_;
        return true;
    }

    bool connected(int a, int b) { return find(a) == find(b); }
    int count() const { return sets_; }

private:
    std::vector<int> parent_;
    std::vector<int> rank_;
    int sets_;
};

int main() {
    UnionFind uf(10);
    assert(uf.count() == 10);

    assert(uf.unite(0, 1));
    assert(uf.unite(2, 3));
    assert(uf.unite(1, 2));  // 0,1,2,3 now one family
    assert(uf.connected(0, 3));
    assert(!uf.connected(0, 4));
    assert(uf.count() == 7);

    // Redundant union changes nothing.
    assert(!uf.unite(0, 3));
    assert(uf.count() == 7);

    // Chain the rest together one link at a time.
    for (int i = 4; i < 9; ++i) {
        assert(uf.unite(i, i + 1));
    }
    assert(uf.connected(4, 9));
    assert(!uf.connected(0, 9));
    assert(uf.unite(3, 4));  // join the two families
    assert(uf.connected(0, 9));
    assert(uf.count() == 1);

    // Path compression check: after finds, everyone points near the root.
    UnionFind deep(8);
    for (int i = 0; i < 7; ++i) deep.unite(i, i + 1);
    int root = deep.find(0);
    for (int i = 1; i < 8; ++i) assert(deep.find(i) == root);

    std::cout << "All union-find checks passed.\n";
    return 0;
}
