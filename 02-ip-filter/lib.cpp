#include "lib.h"

std::string ExtractIpFromCsvLine(const std::string& line) {
    std::string res = line;
    res.erase(res.find('\t'));
    return res;
}

IpAddress String2Addr(const std::string& str) {
    IpAddress addr;
    if (str.empty()) {
        return addr; // return incorrect address -1.-1.-1.-1
    }
    int curr = -1;
    size_t pos = 0;
    auto it = str.begin();
    while(pos < IpAddress::kIp4AddressLength && it != str.end()) {
        if (*it == '.') {
            addr[pos++] = curr;
            curr = -1;
        } else {
            curr = curr == -1 ? (*it - '0') : curr * 10 + (*it - '0');
        }
        ++it;
    }
    addr[pos] = curr;

    return addr;
}

std::vector<IpAddress> GetIpList(std::istream& in) {
    if (!in) {
        std::cerr << "Invalid stream received\n";
        return {};
    }
    std::vector<IpAddress> res;
    std::string buff;

    while(getline(in, buff)) {
        auto ip_addr_str = ExtractIpFromCsvLine(buff);
        res.emplace_back(String2Addr(ip_addr_str));
    }

    return res;
}
