#pragma once

#include <iostream>

template <typename T, size_t LIMIT>
struct MyAllocator {
    using value_type = T;

    MyAllocator() = default;

    template <typename U>
    explicit MyAllocator(const MyAllocator<U, LIMIT>& other) {}

    ~MyAllocator() {
        if (buffer_) {
            std::free(buffer_);
        }
    }

    T* allocate(std::size_t n) {
        if (n + elements_allocated_ > LIMIT) {
            std::cerr << "Can't allocate memory! limit exceeded\n";
            throw std::bad_alloc();
        }
        if (!buffer_) {
            buffer_ = reinterpret_cast<T*>(std::malloc(n * sizeof(T)));
            if (!buffer_) {
                std::cerr << "Can't allocate memory! malloc error\n";
                throw std::bad_alloc();
            }
        }

        T* data_ptr = (buffer_ + (sizeof(T) * elements_allocated_));
        elements_allocated_ += n;
        return data_ptr;
    }

    // not required
    void deallocate(T*, std::size_t) {}

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        new (p) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p) {
        p->~U();
    }

    template<class U>
    struct rebind {
        using other = MyAllocator<U, LIMIT>;
    };

    size_t elements_allocated_{0};
    T* buffer_{nullptr};
};