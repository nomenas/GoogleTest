#include <gtest/gtest.h>

struct SimpleParameterizedTest : ::testing::TestWithParam<bool> {};

TEST_P(SimpleParameterizedTest, TestMethod)
{
    EXPECT_TRUE(GetParam());
}

INSTANTIATE_TEST_CASE_P(Default, SimpleParameterizedTest, ::testing::Values(true, false, true));
