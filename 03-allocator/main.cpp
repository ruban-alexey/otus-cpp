#include <iostream>
#include <vector>

#include "allocator.h"

int main() {
    std::vector<int, MyAllocator<int>> v;
    return 0;
}
