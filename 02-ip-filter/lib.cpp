#include "lib.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, const IpAddress& addr) {
    for(size_t i = 0; i < IpAddress::kIp4AddressLength; ++i) {
        out << addr.values[i];
        if (i != IpAddress::kIp4AddressLength - 1) {
            out << '.';
        }
    }
    return out;
}

void PrintIpList(std::ostream& out, const std::vector<IpAddress>& list) {
    for (size_t i = 0; i < list.size(); ++i) {
        out << list[i] << "\n";
    }
}

std::string ExtractIpFromCsvLine(const std::string& line) {
    std::string res = line;
    res.erase(res.find('\t'));
    return res;
}

IpAddress String2Addr(const std::string& str) {
    IpAddress addr;
    if (str.empty()
        || std::count_if(str.begin(), str.end(), [](char ch) {return ch == '.';}) != IpAddress::kIp4AddressLength - 1) {
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

void PerformMainTask(std::istream& in, std::ostream& out) {
    // 1.
    auto all_addresses = GetIpList(in);
    std::sort(all_addresses.begin(), all_addresses.end());
    std::reverse(all_addresses.begin(), all_addresses.end());
    PrintIpList(out, all_addresses);

    auto sort_and_print = [&all_addresses, &out] (auto predicate) {
        std::vector<IpAddress> buf;
        std::copy_if(all_addresses.begin(), all_addresses.end(), std::back_inserter(buf), predicate);
        PrintIpList(out, buf);
    };

    // 2.
    sort_and_print([](const IpAddress& addr){return addr.values[0] == 1;});
    // 3.
    sort_and_print([](const IpAddress& addr){return addr.values[0] == 46 && addr.values[1] == 70;});
    // 4.
    sort_and_print([](const IpAddress& addr){return addr.values[0] == 46 || addr.values[1] == 46 || addr.values[2] == 46 || addr.values[3] == 46;});
}
