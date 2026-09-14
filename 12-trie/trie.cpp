// Trie: a letter tree for prefix search. Lowercase a-z only.
// Each node holds up to 26 children plus an end-of-word flag.
// Compile: g++ -std=c++17 -Wall -Wextra 12-trie/trie.cpp -o /tmp/trie && /tmp/trie

#include <cassert>
#include <iostream>
#include <string>

class Trie {
public:
    Trie() : root_(new Node()) {}
    ~Trie() { clear(root_); }

    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    void insert(const std::string& word) {
        Node* n = root_;
        for (char c : word) {
            int i = slot(c);
            if (n->child[i] == nullptr) {
                n->child[i] = new Node();
            }
            n = n->child[i];
        }
        n->is_end = true;
    }

    // True only for a full word that was inserted.
    bool search(const std::string& word) const {
        Node* n = find(word);
        return n != nullptr && n->is_end;
    }

    // True when some inserted word starts with this prefix.
    bool startsWith(const std::string& prefix) const {
        return find(prefix) != nullptr;
    }

private:
    struct Node {
        Node* child[26];
        bool is_end;
        Node() : is_end(false) {
            for (int i = 0; i < 26; ++i) child[i] = nullptr;
        }
    };

    static int slot(char c) { return c - 'a'; }

    Node* find(const std::string& s) const {
        Node* n = root_;
        for (char c : s) {
            n = n->child[slot(c)];
            if (n == nullptr) return nullptr;
        }
        return n;
    }

    static void clear(Node* n) {
        if (n == nullptr) return;
        for (int i = 0; i < 26; ++i) clear(n->child[i]);
        delete n;
    }

    Node* root_;
};

int main() {
    Trie t;
    t.insert("apple");
    t.insert("app");
    t.insert("application");
    t.insert("banana");

    // Full words found, plain prefixes are not words.
    assert(t.search("apple"));
    assert(t.search("app"));
    assert(!t.search("appl"));
    assert(!t.search("ban"));

    // Prefix checks.
    assert(t.startsWith("app"));
    assert(t.startsWith("appl"));
    assert(t.startsWith("ban"));
    assert(!t.startsWith("cat"));
    assert(!t.startsWith("applepie"));

    // Empty trie answers false to everything.
    Trie e;
    assert(!e.search("a"));
    assert(!e.startsWith("a"));

    std::cout << "All trie checks passed.\n";
    return 0;
}
