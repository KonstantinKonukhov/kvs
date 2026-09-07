#include <gtest/gtest.h>
#include "command.hpp"
#include "store.hpp"

TEST(Tokenize, SplitsBySpaces) {
    auto tokens = tokenize("SET key value");
    ASSERT_EQ(tokens.size(), 3u);
    EXPECT_EQ(tokens[0], "SET");
    EXPECT_EQ(tokens[1], "key");
    EXPECT_EQ(tokens[2], "value");
}

TEST(Tokenize, HandlesQuotedValueAsOneToken) {
    auto tokens = tokenize("SET greeting \"hello world\"");
    ASSERT_EQ(tokens.size(), 3u);
    EXPECT_EQ(tokens[2], "hello world");
}

TEST(Tokenize, IgnoresExtraSpaces) {
    auto tokens = tokenize("  SET   key    value  ");
    ASSERT_EQ(tokens.size(), 3u);
}

TEST(Tokenize, EmptyStringGivesNoTokens) {
    EXPECT_TRUE(tokenize("").empty());
}

TEST(Parse, UnknownCommandReturnsNullopt) {
    EXPECT_FALSE(parse("FOO bar").has_value());
}

TEST(Parse, EmptyLineReturnsNullopt) {
    EXPECT_FALSE(parse("").has_value());
}

TEST(Parse, SetMissingArgumentsReturnsNullopt) {
    EXPECT_FALSE(parse("SET onlykey").has_value());
}

TEST(Execute, SetThenGet) {
    Store store;
    execute(store, *parse("SET name Konstantin"));
    EXPECT_EQ(execute(store, *parse("GET name")), "Konstantin");
}

TEST(Execute, GetMissingKeyReturnsNil) {
    Store store;
    EXPECT_EQ(execute(store, *parse("GET missing")), "(nil)");
}

TEST(Execute, ExistsAndDel) {
    Store store;
    execute(store, *parse("SET a 1"));
    EXPECT_EQ(execute(store, *parse("EXISTS a")), "1");
    execute(store, *parse("DEL a"));
    EXPECT_EQ(execute(store, *parse("EXISTS a")), "0");
}

TEST(Execute, TypeReportsAlternative) {
    Store store;
    execute(store, *parse("SET s hello"));
    EXPECT_EQ(execute(store, *parse("TYPE s")), "string");
}

TEST(Execute, IncrCreatesAndIncrements) {
    Store store;
    EXPECT_EQ(execute(store, *parse("INCR counter")), "1");
    EXPECT_EQ(execute(store, *parse("INCR counter")), "2");
}

TEST(Execute, IncrOnStringFails) {
    Store store;
    execute(store, *parse("SET s hello"));
    EXPECT_EQ(execute(store, *parse("INCR s")), "ERROR: value is not an integer");
}
