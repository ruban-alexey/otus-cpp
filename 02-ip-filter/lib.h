#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct IpAddress {
    static constexpr size_t kIp4AddressLength = 4;

    bool IsValid() {
        return std::all_of(values.begin(), values.end(), [](int val) { return val >= 0 && val <= 255; });
    }
    int& operator[](size_t pos) {
        return values[pos];
    }
    bool operator==(const IpAddress& other) const {
        return std::equal(values.begin(), values.end(), other.values.begin());
    }
    bool operator!=(const IpAddress& other) const {
        return !(*this == other);
    }
    bool operator<(const IpAddress& other) const {
        size_t idx = 0;
        while (idx + 1 < kIp4AddressLength && values[idx] == other.values[idx]) {
            ++idx;
        }
        return values[idx] < other.values[idx];
    }

    std::array<int, kIp4AddressLength> values = {-1, -1, -1, -1};
};

std::ostream& operator<<(std::ostream& out, const IpAddress& addr);

void PrintIpList(std::ostream& out, const std::vector<IpAddress>& list);

void PerformMainTask(std::istream& in = std::cin, std::ostream& out = std::cout);
IpAddress String2Addr(const std::string& str);
std::string ExtractIpFromCsvLine(const std::string& line);
std::vector<IpAddress> GetIpList(std::istream& in);