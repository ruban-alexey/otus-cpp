#include "gtest/gtest.h"

#include <vector>
#include <string>
#include <fstream>
#include "lib.h"

TEST(string_2_addr, correct_pairs) {
    std::vector<std::pair<std::string, IpAddress>> testing_pairs =
        {{"1.1.1.1", {1, 1, 1, 1}},
         {"255.255.255.0", {255, 255, 255, 0}},
         {"255.0.12.33", {255, 0, 12, 33}}};
    for(auto [test_string, correct_result] : testing_pairs) {
        auto result_ip = String2Addr(test_string);
        ASSERT_TRUE(result_ip.IsValid());
        ASSERT_EQ(result_ip, correct_result);
    }
}

TEST(string_2_addr, incorrect_pairs) {
    std::vector<std::pair<std::string, IpAddress>> testing_pairs =
        {{"1.1.1.1.1", {1, 1, 1, 1}},
         {"255.255.255.-1", {255, 255, 255, -1}},
         {"255.0.12.256", {255, 0, 12, 256}}};
    for(auto [test_string, correct_result] : testing_pairs) {
        auto result_ip = String2Addr(test_string);
        ASSERT_FALSE(result_ip.IsValid());
    }
}

TEST(large_input, common_test) {
    const std::string filepath_in = std::string(RESOURCES_PATH) + "/ip_filter.tsv";
    const std::string filepath_out = std::string(RESOURCES_PATH) + "/result_ip_filter.txt";
    std::ifstream in(filepath_in);
    std::ofstream out(filepath_out);

    // 1.
    auto all_addresses = GetIpList(in);
    std::sort(all_addresses.begin(), all_addresses.end());
    std::reverse(all_addresses.begin(), all_addresses.end());
    PrintIpList(out, all_addresses);
    // 2.
    std::vector<IpAddress> task2;
    std::copy_if(all_addresses.begin(), all_addresses.end(), std::back_inserter(task2), [](const IpAddress& addr){return addr.values[0] == 1;});
    if (!task2.empty()) {
        out << "\n";
    }
    PrintIpList(out, task2);
    // 3.
    std::vector<IpAddress> task3;
    std::copy_if(all_addresses.begin(), all_addresses.end(), std::back_inserter(task3), [](const IpAddress& addr){return addr.values[0] == 46 && addr.values[1] == 70;});
    if (!task3.empty()) {
        out << "\n";
    }
    PrintIpList(out, task3);
    // 4.
    std::vector<IpAddress> task4;
    std::copy_if(all_addresses.begin(), all_addresses.end(), std::back_inserter(task4), [](const IpAddress& addr){return addr.values[0] == 46 || addr.values[1] == 46 || addr.values[2] == 46 || addr.values[3] == 46;});
    if (!task4.empty()) {
        out << "\n";
    }
    PrintIpList(out, task4);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

