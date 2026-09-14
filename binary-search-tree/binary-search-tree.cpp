// BST: plain binary search tree with insert, search, remove, and traversal.
// Smaller keys go left, bigger keys go right. Duplicates are ignored.
// Compile: g++ -std=c++17 -Wall -Wextra binary-search-tree/binary-search-tree.cpp -o /tmp/bst && /tmp/bst

#include <cassert>
#include <iostream>
#include <vector>

class BST {
public:
    BST() : root_(nullptr) {}
    ~BST() { clear(root_); }

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(int key) { root_ = insert_in(root_, key); }

    bool contains(int key) const {
        Node* n = root_;
        while (n != nullptr) {
            if (key == n->key) return true;
            n = (key < n->key) ? n->left : n->right;
        }
        return false;
    }

    void remove(int key) { root_ = remove_from(root_, key); }

    // Sorted order, useful for checks and for interviews.
    std::vector<int> inorder() const {
        std::vector<int> out;
        walk(root_, out);
        return out;
    }

    bool empty() const { return root_ == nullptr; }

private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        explicit Node(int k) : key(k), left(nullptr), right(nullptr) {}
    };

    static Node* insert_in(Node* n, int key) {
        if (n == nullptr) return new Node(key);
        if (key < n->key) {
            n->left = insert_in(n->left, key);
        } else if (key > n->key) {
            n->right = insert_in(n->right, key);
        }
        return n;
    }

    static Node* min_node(Node* n) {
        while (n->left != nullptr) n = n->left;
        return n;
    }

    static Node* remove_from(Node* n, int key) {
        if (n == nullptr) return nullptr;
        if (key < n->key) {
            n->left = remove_from(n->left, key);
        } else if (key > n->key) {
            n->right = remove_from(n->right, key);
        } else {
            // Found it. Three cases below.
            if (n->left == nullptr) {
                Node* r = n->right;
                delete n;
                return r;
            }
            if (n->right == nullptr) {
                Node* l = n->left;
                delete n;
                return l;
            }
            // Two children: copy the successor up, delete it below.
            Node* next = min_node(n->right);
            n->key = next->key;
            n->right = remove_from(n->right, next->key);
        }
        return n;
    }

    static void walk(Node* n, std::vector<int>& out) {
        if (n == nullptr) return;
        walk(n->left, out);
        out.push_back(n->key);
        walk(n->right, out);
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
    BST t;
    assert(t.empty());

    for (int k : {50, 30, 70, 20, 40, 60, 80}) {
        t.insert(k);
    }
    assert(t.inorder() == std::vector<int>({20, 30, 40, 50, 60, 70, 80}));
    assert(t.contains(40));
    assert(!t.contains(99));

    // Duplicate insert changes nothing.
    t.insert(30);
    assert(t.inorder() == std::vector<int>({20, 30, 40, 50, 60, 70, 80}));

    // Remove a leaf.
    t.remove(20);
    assert(!t.contains(20));

    // Remove a node with one child (30 now has only right child 40).
    t.remove(30);
    assert(!t.contains(30));
    assert(t.contains(40));

    // Remove a node with two children (the root 50).
    t.remove(50);
    assert(!t.contains(50));
    assert(t.inorder() == std::vector<int>({40, 60, 70, 80}));

    // Removing a missing key is a safe no-op.
    t.remove(999);
    assert(t.inorder() == std::vector<int>({40, 60, 70, 80}));

    std::cout << "All BST checks passed.\n";
    return 0;
}
