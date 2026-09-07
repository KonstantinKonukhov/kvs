#include <gtest/gtest.h>
#include "placeholder.hpp"
TEST(Probe, Works) { EXPECT_EQ(placeholder(), 42); }
