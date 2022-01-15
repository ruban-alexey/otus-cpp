#include <iostream>
#include <sstream>

#include "lib.h"

int main() {
    // 1.
    auto all_addresses = GetIpList(std::cin);
    std::sort(all_addresses.begin(), all_addresses.end());
    std::reverse(all_addresses.begin(), all_addresses.end());
    PrintIpList(std::cout, all_addresses);
    // 2.
    std::vector<IpAddress> task2;
    std::copy_if(all_addresses.begin(), all_addresses.end(), std::back_inserter(task2), [](const IpAddress& addr){return addr.values[0] == 1;});
    if (!task2.empty()) {
        std::cout << "\n";
    }
    PrintIpList(std::cout, task2);
    // 3.
    std::vector<IpAddress> task3;
    std::copy_if(all_addresses.begin(), all_addresses.end(), std::back_inserter(task3), [](const IpAddress& addr){return addr.values[0] == 46 && addr.values[1] == 70;});
    if (!task3.empty()) {
        std::cout << "\n";
    }
    PrintIpList(std::cout, task3);
    // 4.
    std::vector<IpAddress> task4;
    std::copy_if(all_addresses.begin(), all_addresses.end(), std::back_inserter(task4), [](const IpAddress& addr){return addr.values[0] == 46 || addr.values[1] == 46 || addr.values[2] == 46 || addr.values[3] == 46;});
    if (!task4.empty()) {
        std::cout << "\n";
    }
    PrintIpList(std::cout, task4);
    return 0;
}