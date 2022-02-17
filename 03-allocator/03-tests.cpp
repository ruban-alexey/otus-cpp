#include "gtest/gtest.h"

#include <string>
#include <list>

#include "allocator.h"
#include "container.h"

namespace {
    struct TestStructure {
        int integer;
        std::string s;
        int* ptr{nullptr};
    };
    class CustomStructure {
      public:
        CustomStructure() {
            custom_structure_ctor_cnt++;
        }
        CustomStructure(int) {
            custom_structure_ctor_cnt++;
        }
        CustomStructure(const CustomStructure& cs) {
            custom_structure_ctor_cnt++;
        }
        ~CustomStructure() {
            custom_structure_dtor_cnt++;
        }
        static int custom_structure_ctor_cnt;
        static int custom_structure_dtor_cnt;
    };
    int CustomStructure::custom_structure_ctor_cnt = 0;
    int CustomStructure::custom_structure_dtor_cnt = 0;
}

TEST(allocator, with_stl_containers) {
    constexpr int N = 3;
    { // ordinary type
        std::list<int, MyAllocator<int, N>> v;
        ASSERT_TRUE(v.empty());
        ASSERT_EQ(v.size(), 0);
        for (int i = 0; i < N; ++i) {
            v.push_back(i);
        }
        ASSERT_FALSE(v.empty());
        ASSERT_EQ(v.size(), N);
        try {
            v.push_back(N);
        } catch(std::exception& ex) {
            const std::string kBadAlloc = "std::bad_alloc";
            ASSERT_EQ(ex.what(), kBadAlloc);
        }
    }
    { // custom type
        std::list<TestStructure, MyAllocator<int, N>> v;
        ASSERT_TRUE(v.empty());
        ASSERT_EQ(v.size(), 0);
        for (int i = 0; i < N; ++i) {
            v.push_back({i, "qwerty", nullptr});
        }
        ASSERT_FALSE(v.empty());
        ASSERT_EQ(v.size(), N);
    }
}

TEST(container, with_different_allocators) {
    constexpr int N = 3;
    {
        MyContainer<int> list;
        ASSERT_TRUE(list.empty());
        ASSERT_EQ(list.size(), 0);
        std::string expected{};
        for(int i = 0; i < N; ++i) {
            list.push(i);
            expected += std::to_string(i) + ' ';
        }

        ASSERT_FALSE(list.empty());
        ASSERT_EQ(list.size(), N);
        ASSERT_EQ(list.back(), N - 1);
        ASSERT_EQ(list.front(), 0);
        std::stringstream out;
        for (auto& val : list) {
            out << val << ' ';
        }
        ASSERT_EQ(out.str(), expected);
    }
}

TEST(container, custom_structure) {
    {
        CustomStructure::custom_structure_ctor_cnt = 0;
        CustomStructure::custom_structure_dtor_cnt = 0;
        constexpr int N = 3;
        MyContainer<CustomStructure, MyAllocator<CustomStructure, N>> list;
        CustomStructure cs;
        list.push(cs);
        list.emplace_back(3);
        list.emplace_back(34);
    }

    ASSERT_EQ(CustomStructure::custom_structure_ctor_cnt, CustomStructure::custom_structure_dtor_cnt);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

