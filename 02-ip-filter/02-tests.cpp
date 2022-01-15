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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

