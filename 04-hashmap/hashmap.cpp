// MyHashMap: key value store with separate chaining and rehashing.
// Compile: g++ -std=c++17 -Wall -Wextra 04-hashmap/hashmap.cpp -o /tmp/hashmap && /tmp/hashmap

#include <cassert>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename K, typename V>
class MyHashMap {
public:
    explicit MyHashMap(size_t buckets = 8)
        : buckets_(buckets), size_(0), table_(buckets, nullptr) {}

    ~MyHashMap() { clear_all(); }

    MyHashMap(const MyHashMap&) = delete;
    MyHashMap& operator=(const MyHashMap&) = delete;

    void put(const K& key, const V& value) {
        if (load_factor() > 0.75) {
            rehash(buckets_ * 2);
        }
        size_t i = index(key);
        for (Node* n = table_[i]; n != nullptr; n = n->next) {
            if (n->key == key) {
                n->value = value;
                return;
            }
        }
        table_[i] = new Node(key, value, table_[i]);
        ++size_;
    }

    bool contains(const K& key) const {
        for (Node* n = table_[index(key)]; n != nullptr; n = n->next) {
            if (n->key == key) return true;
        }
        return false;
    }

    V& get(const K& key) {
        for (Node* n = table_[index(key)]; n != nullptr; n = n->next) {
            if (n->key == key) return n->value;
        }
        throw std::out_of_range("key not found");
    }

    void remove(const K& key) {
        size_t i = index(key);
        Node* prev = nullptr;
        for (Node* n = table_[i]; n != nullptr; n = n->next) {
            if (n->key == key) {
                if (prev == nullptr) {
                    table_[i] = n->next;
                } else {
                    prev->next = n->next;
                }
                delete n;
                --size_;
                return;
            }
            prev = n;
        }
    }

    size_t size() const { return size_; }
    size_t bucket_count() const { return buckets_; }

private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v, Node* n) : key(k), value(v), next(n) {}
    };

    size_t index(const K& key) const {
        return std::hash<K>{}(key) % buckets_;
    }

    double load_factor() const {
        return static_cast<double>(size_) / static_cast<double>(buckets_);
    }

    void rehash(size_t new_buckets) {
        std::vector<Node*> new_table(new_buckets, nullptr);
        for (size_t i = 0; i < buckets_; ++i) {
            Node* n = table_[i];
            while (n != nullptr) {
                Node* next = n->next;
                size_t j = std::hash<K>{}(n->key) % new_buckets;
                n->next = new_table[j];
                new_table[j] = n;
                n = next;
            }
        }
        table_ = new_table;
        buckets_ = new_buckets;
    }

    void clear_all() {
        for (size_t i = 0; i < buckets_; ++i) {
            Node* n = table_[i];
            while (n != nullptr) {
                Node* next = n->next;
                delete n;
                n = next;
            }
        }
    }

    size_t buckets_;
    size_t size_;
    std::vector<Node*> table_;
};

int main() {
    MyHashMap<int, std::string> m;
    m.put(1, "one");
    m.put(2, "two");
    m.put(3, "three");
    assert(m.size() == 3);
    assert(m.get(2) == "two");
    assert(m.contains(1));

    // Overwrite, size must not grow.
    m.put(2, "TWO");
    assert(m.get(2) == "TWO");
    assert(m.size() == 3);

    m.remove(2);
    assert(!m.contains(2));
    assert(m.size() == 2);

    // Removing a missing key is a safe no-op.
    m.remove(999);
    assert(m.size() == 2);

    // Missing get must throw.
    bool threw = false;
    try {
        m.get(999);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    assert(threw);

    // Force rehash with many inserts.
    size_t before = m.bucket_count();
    for (int i = 100; i < 300; ++i) {
        m.put(i, "x");
    }
    assert(m.bucket_count() > before);
    assert(m.get(150) == "x");
    assert(m.get(1) == "one");

    std::cout << "All hashmap checks passed. size=" << m.size()
              << " buckets=" << m.bucket_count() << "\n";
    return 0;
}
