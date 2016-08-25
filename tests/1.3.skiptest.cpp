#include <gtest/gtest.h>

TEST(SimpleTestCase, DISABLED_SimpleTestMethod4)
{
    EXPECT_TRUE(false) << "It is expected that this test case will be skipped becouse it it contains DISABLED_ as name prefix";
}
