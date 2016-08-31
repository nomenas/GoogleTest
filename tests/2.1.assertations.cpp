#include <gtest/gtest.h>

TEST(AssertationTests, BasicAssertations)
{
    EXPECT_TRUE(true) << "print error message";
    EXPECT_FALSE(false);
}

TEST(AssertationTests, BinaryComparison)
{
    ASSERT_EQ(0, 0);
    ASSERT_NE(0, 1);
    ASSERT_LT(1, 2);
    ASSERT_LE(1, 1);
    ASSERT_GT(2, 1);
    ASSERT_GE(2, 2);
}

TEST(AssertationTests, FloatComparison)
{
    ASSERT_FLOAT_EQ(0.0001, 0.0001);
    ASSERT_DOUBLE_EQ(0.0001, 0.0001);
    ASSERT_NEAR(1.001, 1.002, 0.01);

    EXPECT_PRED_FORMAT2(::testing::FloatLE, 0.1, 0.2);
    EXPECT_PRED_FORMAT2(::testing::DoubleLE, 0.1, 0.2);
}

TEST(AssertationTests, StringComparision)
{
    ASSERT_STREQ("string1", "string1");
    ASSERT_STRNE("string2", "string1");
    ASSERT_STRCASEEQ("string1", "STRING1");
    ASSERT_STRCASENE("string2", "STRING1");
}

template <class T>
void throwException()
{
    throw T{};
}

void nothrowMethod()
{

}

TEST(AssertationTests, ExceptionAssertation)
{
    ASSERT_THROW(throwException<std::string>(), std::string);
    ASSERT_ANY_THROW(throwException<std::string>());
    ASSERT_NO_THROW(nothrowMethod());
}

TEST(AssertationTests, ExplicitSuccessAndFailure)
{
    SUCCEED() << "This doesn't do anything. "
              << "However, in future google may add SUCCEED() messages to Google Test's output.";

    // add not fatal failure
    ADD_FAILURE();
    ADD_FAILURE_AT("my file", 100);

    FAIL() << "fatal failure, stop test execution here";
}

TEST(AssertationTests, PredicateAssertion)
{
    EXPECT_PRED2([](auto, auto)->bool{return true;}, 1., 2.);
    EXPECT_PRED_FORMAT2(::testing::FloatLE, 0.1, 0.2);
    EXPECT_PRED_FORMAT2(::testing::DoubleLE, 0.1, 0.2);
}

