// Simplified UniquePtr and SharedPtr to learn ownership and RAII.
// Compile: g++ -std=c++17 -Wall -Wextra 06-smart-pointers/smart-pointers.cpp -o /tmp/smart && /tmp/smart

#include <cassert>
#include <iostream>
#include <utility>

template <typename T>
class UniquePtr {
public:
    explicit UniquePtr(T* p = nullptr) : ptr_(p) {}
    ~UniquePtr() { delete ptr_; }

    // Only one owner: copies are banned, moves are allowed.
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    T* get() const { return ptr_; }

    T* release() {
        T* p = ptr_;
        ptr_ = nullptr;
        return p;
    }

    void reset(T* p = nullptr) {
        delete ptr_;
        ptr_ = p;
    }

private:
    T* ptr_;
};

template <typename T>
class SharedPtr {
public:
    explicit SharedPtr(T* p = nullptr) : ptr_(p), count_(nullptr) {
        if (p != nullptr) {
            count_ = new size_t(1);
        }
    }

    ~SharedPtr() { drop(); }

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), count_(other.count_) {
        if (count_ != nullptr) {
            ++(*count_);
        }
    }

    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            drop();
            ptr_ = other.ptr_;
            count_ = other.count_;
            if (count_ != nullptr) {
                ++(*count_);
            }
        }
        return *this;
    }

    SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), count_(other.count_) {
        other.ptr_ = nullptr;
        other.count_ = nullptr;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            drop();
            ptr_ = other.ptr_;
            count_ = other.count_;
            other.ptr_ = nullptr;
            other.count_ = nullptr;
        }
        return *this;
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    T* get() const { return ptr_; }
    size_t use_count() const { return count_ ? *count_ : 0; }

    void reset(T* p = nullptr) {
        drop();
        ptr_ = p;
        count_ = (p != nullptr) ? new size_t(1) : nullptr;
    }

private:
    void drop() {
        if (count_ != nullptr) {
            --(*count_);
            if (*count_ == 0) {
                delete ptr_;
                delete count_;
            }
            ptr_ = nullptr;
            count_ = nullptr;
        }
    }

    T* ptr_;
    size_t* count_;
};

int main() {
    // UniquePtr: one owner, move hands it over.
    UniquePtr<int> u(new int(42));
    assert(*u == 42);
    assert(u.get() != nullptr);

    UniquePtr<int> v = std::move(u);
    assert(u.get() == nullptr);
    assert(*v == 42);

    v.reset(new int(7));
    assert(*v == 7);

    int* raw = v.release();
    assert(v.get() == nullptr);
    assert(*raw == 7);
    delete raw;

    // SharedPtr: many owners, last one out deletes.
    SharedPtr<int> a(new int(100));
    assert(a.use_count() == 1);
    {
        SharedPtr<int> b = a;
        assert(a.use_count() == 2);
        assert(b.use_count() == 2);
        assert(*b == 100);
        SharedPtr<int> c;
        c = b;
        assert(a.use_count() == 3);
    }
    assert(a.use_count() == 1);

    a.reset();
    assert(a.use_count() == 0);
    assert(a.get() == nullptr);

    std::cout << "All smart pointer checks passed.\n";
    return 0;
}
