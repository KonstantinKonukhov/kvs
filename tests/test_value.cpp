#include <gtest/gtest.h>
#include "value.hpp"

TEST(Value, StoresString) {
    Value v("hello");
    EXPECT_EQ(v.str(), "hello");
}

TEST(Value, CopyIsIndependent) {
    Value a("original");
    Value b = a;
    EXPECT_EQ(a.str(), "original");
    EXPECT_EQ(b.str(), "original");
}

TEST(Value, MoveTransfersData) {
    Value a("moved-content");
    Value b(std::move(a));
    EXPECT_EQ(b.str(), "moved-content");
}
