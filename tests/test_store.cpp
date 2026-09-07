#include <gtest/gtest.h>
#include "store.hpp"

TEST(Store, SetAndGet) {
    Store store;
    store.set("key", Value(std::string("value")));
    auto v = store.get("key");
    ASSERT_TRUE(v.has_value());
    EXPECT_EQ(v->to_display_string(), "value");
}

TEST(Store, GetMissingReturnsNullopt) {
    Store store;
    EXPECT_FALSE(store.get("missing").has_value());
}

TEST(Store, Del) {
    Store store;
    store.set("key", Value(std::string("value")));
    EXPECT_TRUE(store.del("key"));
    EXPECT_FALSE(store.get("key").has_value());
    EXPECT_FALSE(store.del("key"));
}

TEST(Store, Size) {
    Store store;
    EXPECT_EQ(store.size(), 0u);
    store.set("a", Value(std::string("1")));
    store.set("b", Value(std::string("2")));
    EXPECT_EQ(store.size(), 2u);
}
