#include <iostream>
#include <vector>
#include <map>

#include "allocator.h"
#include "container.h"

int main() {
    std::map<int, int, std::less<>, MyAllocator<std::pair<const int, int>, 10>> mp;
    mp[0] = 1;
    for(int i = 1; i < 10; ++i) {
        mp[i] = mp[i - 1] * i;
    }

    MyContainer<int> v;
    v.push(1);
    v.push(2);

    for(auto& val : v) {
        std::cout << *val.data << "\n";
    }

    return 0;
}
