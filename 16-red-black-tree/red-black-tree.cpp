// RBTree: binary search tree kept balanced with red and black paint.
// New nodes arrive red. Fixup repaints and rotates until the rules hold.
// Scope note: insert plus search. Delete fixup is header-only knowledge here.
// Compile: g++ -std=c++17 -Wall -Wextra 16-red-black-tree/red-black-tree.cpp -o /tmp/rb && /tmp/rb

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

class RBTree {
public:
    RBTree() {
        nil_ = new Node(0, BLACK);
        nil_->left = nil_->right = nil_->parent = nil_;
        root_ = nil_;
    }

    ~RBTree() {
        clear(root_);
        delete nil_;
    }

    RBTree(const RBTree&) = delete;
    RBTree& operator=(const RBTree&) = delete;

    void insert(int key) {
        Node* z = new Node(key, RED);
        z->left = z->right = z->parent = nil_;
        Node* y = nil_;
        Node* x = root_;
        while (x != nil_) {
            y = x;
            if (z->key == x->key) {  // duplicate, ignore
                delete z;
                return;
            }
            x = (z->key < x->key) ? x->left : x->right;
        }
        z->parent = y;
        if (y == nil_) {
            root_ = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
        fix_insert(z);
    }

    bool contains(int key) const {
        Node* n = root_;
        while (n != nil_) {
            if (key == n->key) return true;
            n = (key < n->key) ? n->left : n->right;
        }
        return false;
    }

    std::vector<int> inorder() const {
        std::vector<int> out;
        walk(root_, out);
        return out;
    }

    // Interview gold: prove every rule holds, right now.
    bool valid() const {
        if (root_->color != BLACK) return false;
        return black_height(root_) != -1;
    }

private:
    enum Color { RED, BLACK };

    struct Node {
        int key;
        Color color;
        Node* left;
        Node* right;
        Node* parent;
        Node(int k, Color c) : key(k), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    void rotate_left(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nil_) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nil_) {
            root_ = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void rotate_right(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nil_) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nil_) {
            root_ = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        x->right = y;
        y->parent = x;
    }

    void fix_insert(Node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* uncle = z->parent->parent->right;
                if (uncle->color == RED) {
                    // Both parent and uncle red: push the problem upward.
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        rotate_left(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotate_right(z->parent->parent);
                }
            } else {
                Node* uncle = z->parent->parent->left;
                if (uncle->color == RED) {
                    z->parent->color = BLACK;
                    uncle->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rotate_right(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotate_left(z->parent->parent);
                }
            }
        }
        root_->color = BLACK;
    }

    // Returns the black height, or -1 the moment any rule breaks.
    // A red node with a red child fails. Unequal child heights fail.
    int black_height(Node* n) const {
        if (n == nil_) return 0;
        if (n->color == RED &&
            (n->left->color == RED || n->right->color == RED)) {
            return -1;
        }
        int l = black_height(n->left);
        int r = black_height(n->right);
        if (l == -1 || r == -1 || l != r) return -1;
        return l + (n->color == BLACK ? 1 : 0);
    }

    void walk(Node* n, std::vector<int>& out) const {
        if (n == nil_) return;
        walk(n->left, out);
        out.push_back(n->key);
        walk(n->right, out);
    }

    void clear(Node* n) {
        if (n == nil_) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

    Node* root_;
    Node* nil_;
};

int main() {
    // Sorted input: plain BST would chain to height 7.
    RBTree t;
    for (int k = 1; k <= 7; ++k) {
        t.insert(k);
        assert(t.valid());  // rules hold after EVERY insert
    }
    assert(t.inorder() == std::vector<int>({1, 2, 3, 4, 5, 6, 7}));
    assert(t.contains(4) && !t.contains(99));

    // A messier order that hits recolor and rotation paths.
    RBTree m;
    for (int k : {10, 20, 30, 15, 25, 5, 1, 40, 35, 50}) {
        m.insert(k);
        assert(m.valid());
    }
    assert(m.inorder() ==
           std::vector<int>({1, 5, 10, 15, 20, 25, 30, 35, 40, 50}));

    // Height stays logarithmic: h <= 2 * log2(n + 1).
    RBTree big;
    for (int k = 1; k <= 100; ++k) big.insert(k);
    assert(big.valid());
    // (height not exposed; validity plus sorted order is the check)

    // Duplicate insert is a safe no-op.
    m.insert(10);
    assert(m.valid());
    assert(m.inorder().size() == 10);

    std::cout << "All red-black checks passed.\n";
    return 0;
}
