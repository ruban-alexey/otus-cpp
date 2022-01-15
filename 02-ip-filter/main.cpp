#include <iostream>
#include <sstream>

#include "lib.h"

std::ostream& operator<<(std::ostream& out, const IpAddress& addr) {
    for(size_t i = 0; i < IpAddress::kIp4AddressLength; ++i) {
        out << addr.values[i];
        if (i != IpAddress::kIp4AddressLength - 1) {
            out << '.';
        }
    }
    return out;
}

int main() {
    std::string in = "113.162.145.156\t111\t0\n"
                     "157.39.22.224\t5\t6\n"
                     "79.180.73.190\t2\t1\n"
                     "179.210.145.4\t22\t0";
    std::stringstream stream(in);
    auto ip_list = GetIpList(stream);

    for(auto& ip : ip_list) {
        std::cout << ip << "\n";
    }

    return 0;
}