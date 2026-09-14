// LRUCache: hash map plus doubly linked list.
// Most used sits at the front, least used at the back. Full cache drops the back.
// Compile: g++ -std=c++17 -Wall -Wextra lru-cache/lru-cache.cpp -o /tmp/lru && /tmp/lru

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

class LRUCache {
public:
    explicit LRUCache(size_t capacity) : capacity_(capacity), head_(nullptr), tail_(nullptr) {
        if (capacity == 0) {
            throw std::invalid_argument("capacity must be above zero");
        }
    }

    ~LRUCache() {
        Node* n = head_;
        while (n != nullptr) {
            Node* next = n->next;
            delete n;
            n = next;
        }
    }

    LRUCache(const LRUCache&) = delete;
    LRUCache& operator=(const LRUCache&) = delete;

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
        Node* node = new Node(key, value);
        add_to_front(node);
        map_[key] = node;
        if (map_.size() > capacity_) {
            Node* old = tail_;
            remove_node(old);
            map_.erase(old->key);
            delete old;
        }
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
    // Classic interview sequence with capacity 2.
    LRUCache c(2);
    c.put(1, 1);
    c.put(2, 2);
    assert(c.get(1) == 1);  // 1 is now most used, 2 is least used.
    c.put(3, 3);            // drops key 2.
    assert(c.get(2) == -1);
    c.put(4, 4);            // drops key 1.
    assert(c.get(1) == -1);
    assert(c.get(3) == 3);
    assert(c.get(4) == 4);

    // Update moves the key to the front.
    LRUCache d(2);
    d.put(1, 1);
    d.put(2, 2);
    d.put(1, 10);  // 1 is most used now, so 2 drops next.
    d.put(3, 3);
    assert(d.get(2) == -1);
    assert(d.get(1) == 10);

    // Capacity 1 keeps only the newest.
    LRUCache e(1);
    e.put(1, 1);
    e.put(2, 2);
    assert(e.get(1) == -1);
    assert(e.get(2) == 2);

    std::cout << "All LRU checks passed.\n";
    return 0;
}
