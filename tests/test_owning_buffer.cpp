#include <gtest/gtest.h>
#include "owning_buffer.hpp"
#include <cstring>

TEST(OwningBuffer, StoresBytes) {
    OwningBuffer buf("abc", 3);
    EXPECT_EQ(buf.size(), 3u);
    EXPECT_EQ(std::memcmp(buf.data(), "abc", 3), 0);
}

TEST(OwningBuffer, CopyIsIndependentMemory) {
    OwningBuffer a("hello", 5);
    OwningBuffer b(a);
    EXPECT_NE(a.data(), b.data());
    EXPECT_EQ(std::memcmp(a.data(), b.data(), 5), 0);
}

TEST(OwningBuffer, MoveLeavesSourceEmpty) {
    OwningBuffer a("hello", 5);
    OwningBuffer b(std::move(a));
    EXPECT_EQ(b.size(), 5u);
    EXPECT_EQ(a.size(), 0u);
}

TEST(OwningBuffer, SelfAssignmentDoesNotBreakObject) {
    OwningBuffer a("hello", 5);
    a = a;
    EXPECT_EQ(a.size(), 5u);
    EXPECT_EQ(std::memcmp(a.data(), "hello", 5), 0);
}
