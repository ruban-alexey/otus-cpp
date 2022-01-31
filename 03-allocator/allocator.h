#pragma once

#include <iostream>

template <typename T, size_t LIMIT>
struct MyAllocator {
    using value_type = T;

    MyAllocator() = default;

    template <typename U>
    explicit MyAllocator(const MyAllocator<U, LIMIT>& other) {}

    T* allocate(std::size_t n) {
        if (n + elements_allocated_ > LIMIT) {
            std::cerr << "Can't allocate memory! limit exceeded\n";
            throw std::bad_alloc();
        }
        auto p = std::malloc(n * sizeof(T));
        if (!p) {
            std::cerr << "Can't allocate memory! malloc error\n";
            throw std::bad_alloc();
        }

        elements_allocated_ += n;
        return reinterpret_cast<T *>(p);
    }

    void deallocate(T* p, std::size_t n) {
        std::free(p);
        if (n > elements_allocated_) {
            std::cerr << "Can't free required amount of memory\n";
        }
        elements_allocated_ -= n;
    }

    template<class U>
    struct rebind {
        using other = MyAllocator<U, LIMIT>;
    };

    size_t elements_allocated_{0};
};