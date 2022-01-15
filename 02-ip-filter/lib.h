#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct IpAddress {
    static constexpr size_t kIp4AddressLength = 4;

    bool IsValid() {
        return std::all_of(values, values + kIp4AddressLength, [](int val) {return val >= 0 && val <= 255;});
    }
    int& operator[](size_t pos) {
        return values[pos];
    }

    int values[kIp4AddressLength] = {-1, -1, -1, -1};
};

IpAddress String2Addr(const std::string& str);
std::string ExtractIpFromCsvLine(const std::string& line);
std::vector<IpAddress> GetIpList(std::istream& in);