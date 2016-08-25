#include <gtest/gtest.h>

TEST(SimpleTestCase, SimpleTestMethod1)
{
    EXPECT_EQ(1, 0 + 1);
}

TEST(SimpleTestCase, SimpleTestMethod2)
{
    EXPECT_EQ(0, 0 * 1);
}
