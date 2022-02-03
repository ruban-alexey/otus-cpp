#include <iostream>
#include <vector>
#include <map>

#include "allocator.h"
#include "container.h"

int main() {
    constexpr int N = 10;

    {
        std::cout << "Default allocator:\n";
        std::map<int, int> facts;
        facts[0] = 1;
        for (int i = 1; i < N; ++i) {
            facts[i] = facts[i - 1] * i;
        }
        for (auto& val: facts) {
            std::cout << val.first << ' ' << val.second << "\n";
        }
        std::cout << "\n";
    }
    {
        std::cout << "Custom allocator:\n";
        std::map<int, int, std::less<>, MyAllocator<std::pair<const int, int>, N>> facts;
        facts[0] = 1;
        for (int i = 1; i < N; ++i) {
            facts[i] = facts[i - 1] * i;
        }
        for (auto& val: facts) {
            std::cout << val.first << ' ' << val.second << "\n";
        }
        std::cout << "\n";
    }

    {
        std::cout << "Custom container:\n";
        MyContainer<int> list;
        for (int i = 0; i < N; ++i) {
            list.push(i);
        }
        for (auto& val: list) {
            std::cout << val << ' ';
        }
        std::cout << "\n\n";
    }
    {
        std::cout << "Custom container and custom allocator:\n";
        MyContainer<int, MyAllocator<int, N>> list;
        for (int i = 0; i < N; ++i) {
            list.push(i);
        }
        for (auto& val: list) {
            std::cout << val << ' ';
        }
    }

    return 0;
}
