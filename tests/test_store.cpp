#include <gtest/gtest.h>
#include "store.hpp"

TEST(Store, SetAndGet) {
    Store store;
    store.set("key", Value("value"));
    const Value* v = store.get("key");
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->str(), "value");
}

TEST(Store, GetMissingReturnsNullptr) {
    Store store;
    EXPECT_EQ(store.get("missing"), nullptr);
}

TEST(Store, Del) {
    Store store;
    store.set("key", Value("value"));
    EXPECT_TRUE(store.del("key"));
    EXPECT_EQ(store.get("key"), nullptr);
    EXPECT_FALSE(store.del("key")); // второй раз — уже нет
}

TEST(Store, Size) {
    Store store;
    EXPECT_EQ(store.size(), 0u);
    store.set("a", Value("1"));
    store.set("b", Value("2"));
    EXPECT_EQ(store.size(), 2u);
}
