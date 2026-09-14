// AVLTree: a binary search tree that rebalances itself on every insert.
// Each node stores its height. Balance factor = left height minus right height.
// Allowed range is -1 to 1. Anything outside triggers a rotation.
// Compile: g++ -std=c++17 -Wall -Wextra 11-avl-tree/avl-tree.cpp -o /tmp/avl && /tmp/avl

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

class AVLTree {
public:
    AVLTree() : root_(nullptr) {}
    ~AVLTree() { clear(root_); }

    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    void insert(int key) { root_ = insert_in(root_, key); }
    bool contains(int key) const { return BST_find(root_, key); }

    std::vector<int> inorder() const {
        std::vector<int> out;
        walk(root_, out);
        return out;
    }

    int height() const { return node_height(root_); }

    // Interview gold: prove the whole tree satisfies the AVL rule.
    bool balanced() const { return check(root_) != -2; }

private:
    struct Node {
        int key;
        int height;
        Node* left;
        Node* right;
        explicit Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    static int node_height(Node* n) { return n ? n->height : 0; }

    static void fix_height(Node* n) {
        n->height = 1 + std::max(node_height(n->left), node_height(n->right));
    }

    static int balance_of(Node* n) {
        return node_height(n->left) - node_height(n->right);
    }

    // Right rotation: left child moves up. Fixes left-left heavy.
    static Node* rotate_right(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        fix_height(y);
        fix_height(x);
        return x;
    }

    // Left rotation: right child moves up. Fixes right-right heavy.
    static Node* rotate_left(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        fix_height(x);
        fix_height(y);
        return y;
    }

    static Node* rebalance(Node* n) {
        fix_height(n);
        int b = balance_of(n);
        if (b > 1) {
            // Left heavy. Inner right child means double rotation.
            if (balance_of(n->left) < 0) {
                n->left = rotate_left(n->left);
            }
            return rotate_right(n);
        }
        if (b < -1) {
            // Right heavy. Inner left child means double rotation.
            if (balance_of(n->right) > 0) {
                n->right = rotate_right(n->right);
            }
            return rotate_left(n);
        }
        return n;
    }

    static Node* insert_in(Node* n, int key) {
        if (n == nullptr) return new Node(key);
        if (key < n->key) {
            n->left = insert_in(n->left, key);
        } else if (key > n->key) {
            n->right = insert_in(n->right, key);
        } else {
            return n;  // duplicate, ignore
        }
        return rebalance(n);
    }

    static bool BST_find(Node* n, int key) {
        while (n != nullptr) {
            if (key == n->key) return true;
            n = (key < n->key) ? n->left : n->right;
        }
        return false;
    }

    static void walk(Node* n, std::vector<int>& out) {
        if (n == nullptr) return;
        walk(n->left, out);
        out.push_back(n->key);
        walk(n->right, out);
    }

    // Returns subtree height, or -2 the moment any node breaks the rule.
    static int check(Node* n) {
        if (n == nullptr) return 0;
        int l = check(n->left);
        int r = check(n->right);
        if (l == -2 || r == -2) return -2;
        if (abs(l - r) > 1) return -2;
        return 1 + std::max(l, r);
    }

    static void clear(Node* n) {
        if (n == nullptr) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

    Node* root_;
};

int main() {
    // Sorted input: plain BST would build a chain of height 7.
    AVLTree t;
    for (int k = 1; k <= 7; ++k) {
        t.insert(k);
    }
    assert(t.inorder() == std::vector<int>({1, 2, 3, 4, 5, 6, 7}));
    assert(t.balanced());
    assert(t.height() <= 3);  // 7 nodes fit in height 3 when balanced
    assert(t.contains(4) && !t.contains(99));

    // Each rotation shape, built small enough to check by hand.
    AVLTree ll;  // descending: right rotation territory
    ll.insert(30);
    ll.insert(20);
    ll.insert(10);
    assert(ll.balanced());
    assert(ll.inorder() == std::vector<int>({10, 20, 30}));

    AVLTree rr;  // ascending: left rotation territory
    rr.insert(10);
    rr.insert(20);
    rr.insert(30);
    assert(rr.balanced());
    assert(rr.inorder() == std::vector<int>({10, 20, 30}));

    AVLTree lr;  // left then right: double rotation
    lr.insert(30);
    lr.insert(10);
    lr.insert(20);
    assert(lr.balanced());
    assert(lr.inorder() == std::vector<int>({10, 20, 30}));

    AVLTree rl;  // right then left: double rotation
    rl.insert(10);
    rl.insert(30);
    rl.insert(20);
    assert(rl.balanced());
    assert(rl.inorder() == std::vector<int>({10, 20, 30}));

    // A longer mixed run stays balanced throughout.
    AVLTree big;
    for (int k : {50, 25, 75, 10, 40, 60, 90, 5, 15, 55, 80, 95, 1}) {
        big.insert(k);
        assert(big.balanced());
    }
    assert(big.contains(55) && !big.contains(100));

    std::cout << "All AVL checks passed. height(1..7)=" << t.height() << "\n";
    return 0;
}
