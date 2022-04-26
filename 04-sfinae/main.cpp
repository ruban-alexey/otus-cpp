#include <algorithm>
#include <iostream>
#include <list>
#include <type_traits>
#include <vector>

/// Prints integer value splitted by 8-byte and converted into uint8_t representation
template<typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
void print_ip(T val) {
    for(int i = sizeof(T) - 1; i >= 0; --i) {
        unsigned char tmp = (val >> (i * 8)) & 0xFF;
        std::cout << (int)tmp;
        if (i != 0) {
            std::cout << ".";
        }
    }
    std::cout << "\n";
}

/// Just prints input stribn
template<typename T, typename = std::enable_if_t<std::is_same_v<typename std::remove_cv<typename std::remove_reference<T>::type>::type,
                                                                std::string>>>
void print_ip(T val) {
    std::cout << val << "\n";
}

/*
 * Output operator for printing two types of containers: list and vector
 * By default puts '.' between elements
 */
template<
    template<typename, typename> typename Container,
    typename Type,
    typename Allocator = std::allocator<Type>,
    typename = std::enable_if_t<
        std::is_same_v<Container<Type, Allocator>, std::vector<Type, Allocator>> ||
            std::is_same_v<Container<Type, Allocator>, std::list<Type, Allocator>>>>
void print_ip(Container<Type, Allocator> container) {
    for (auto iter = std::begin(container); iter != std::end(container); ++iter) {
        if (iter != std::begin(container))
            std::cout << ".";
        std::cout << *iter;
    }
    std::cout << "\n";
}

template<template<typename ...Args> typename T>
void print_ip(T<> tup) {
    std::cout << std::get<0>(tup);
}

int main() {
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
//    print_ip( std::make_tuple(123, 456, 789, 0) ); // 123.456.789.0

    return 0;
}