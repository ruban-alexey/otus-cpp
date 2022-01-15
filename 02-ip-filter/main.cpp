#include <iostream>
#include <sstream>

#include "lib.h"

int main() {
    auto ip_list = GetIpList(std::cin);

    for(auto& ip : ip_list) {
        std::cout << ip << "\n";
    }

    return 0;
}