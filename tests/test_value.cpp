#include <gtest/gtest.h>
#include "value.hpp"

TEST(Value, StoresString) {
    Value v(std::string("hello"));
    EXPECT_EQ(v.to_display_string(), "hello");
    EXPECT_EQ(v.type_name(), "string");
}

TEST(Value, StoresInt) {
    Value v(std::int64_t{42});
    EXPECT_EQ(v.to_display_string(), "42");
    EXPECT_EQ(v.type_name(), "int");
}

TEST(Value, StoresDouble) {
    Value v(3.14);
    EXPECT_EQ(v.type_name(), "double");
}

TEST(Value, CopyIsIndependent) {
    Value a(std::string("original"));
    Value b = a;
    EXPECT_EQ(a.to_display_string(), "original");
    EXPECT_EQ(b.to_display_string(), "original");
}

TEST(Value, MoveTransfersData) {
    Value a(std::string("moved-content"));
    Value b(std::move(a));
    EXPECT_EQ(b.to_display_string(), "moved-content");
}
