// MRUCache: hash map plus doubly linked list.
// Most used sits at the front. Full cache drops the FRONT (most used).
// That single eviction flip is the whole difference from LRU.
// Compile: g++ -std=c++17 -Wall -Wextra mru-cache/mru-cache.cpp -o /tmp/mru && /tmp/mru

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

class MRUCache {
public:
    explicit MRUCache(size_t capacity) : capacity_(capacity), head_(nullptr), tail_(nullptr) {
        if (capacity == 0) {
            throw std::invalid_argument("capacity must be above zero");
        }
    }

    ~MRUCache() {
        Node* n = head_;
        while (n != nullptr) {
            Node* next = n->next;
            delete n;
            n = next;
        }
    }

    MRUCache(const MRUCache&) = delete;
    MRUCache& operator=(const MRUCache&) = delete;

    int get(int key) {
        auto it = map_.find(key);
        if (it == map_.end()) {
            return -1;
        }
        move_to_front(it->second);
        return it->second->value;
    }

    void put(int key, int value) {
        auto it = map_.find(key);
        if (it != map_.end()) {
            it->second->value = value;
            move_to_front(it->second);
            return;
        }
        if (map_.size() == capacity_) {
            // MRU eviction first: drop the head, the most recently used.
            // Evicting after insert would delete the new node itself.
            Node* old = head_;
            remove_node(old);
            map_.erase(old->key);
            delete old;
        }
        Node* node = new Node(key, value);
        add_to_front(node);
        map_[key] = node;
    }

private:
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    void add_to_front(Node* node) {
        node->prev = nullptr;
        node->next = head_;
        if (head_ != nullptr) {
            head_->prev = node;
        }
        head_ = node;
        if (tail_ == nullptr) {
            tail_ = node;
        }
    }

    void remove_node(Node* node) {
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head_ = node->next;
        }
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail_ = node->prev;
        }
    }

    void move_to_front(Node* node) {
        if (node == head_) return;
        remove_node(node);
        add_to_front(node);
    }

    size_t capacity_;
    Node* head_;
    Node* tail_;
    std::unordered_map<int, Node*> map_;
};

int main() {
    // Same opening as the LRU demo, opposite ending. Capacity 2.
    MRUCache c(2);
    c.put(1, 1);
    c.put(2, 2);
    assert(c.get(1) == 1);  // 1 is now most used, so 1 is the eviction target.
    c.put(3, 3);            // drops key 1 (LRU would drop 2).
    assert(c.get(1) == -1);
    assert(c.get(2) == 2);
    assert(c.get(3) == 3);

    // Update also marks most used, so the updated key drops next.
    MRUCache d(2);
    d.put(1, 1);
    d.put(2, 2);
    d.put(2, 20);  // 2 is most used now.
    d.put(3, 3);   // drops key 2.
    assert(d.get(2) == -1);
    assert(d.get(1) == 1);
    assert(d.get(3) == 3);

    // Capacity 1 keeps only the newest.
    MRUCache e(1);
    e.put(1, 1);
    e.put(2, 2);
    assert(e.get(1) == -1);
    assert(e.get(2) == 2);

    std::cout << "All MRU checks passed.\n";
    return 0;
}
