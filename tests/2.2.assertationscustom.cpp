#include <gtest/gtest.h>

TEST(CheckResultFuctionTests, NormalChecking)
{
    int value = 0;
    while (value < 5)
    {
        ASSERT_NE(++value, 3);
    }

    FAIL() << "******************** This line code is not reachable ***************************";
}

void checkResult(int value)
{
    // stop execution if value is 3
    ASSERT_NE(value, 3);
}

testing::AssertionResult checkAssertionResult(int n)
{
    if (n != 3)
    {
        return ::testing::AssertionSuccess() << n << " is different than 3";
    }
    else
    {
        return ::testing::AssertionFailure() << n << " is 3";
    }
}

TEST(CheckResultFuctionTests, CheckingResultFunction)
{
    int value = 0;
    while (value < 5)
    {
        char buffer[50];
        sprintf(buffer, "iteration %d", value);

        // This trace point will be included in every failure in this scope.
        SCOPED_TRACE(buffer);
        checkResult(++value);

        // Test function which returns false if assertation happened in subrutine function
        RecordProperty("HasFatalFailure", HasFatalFailure());
        RecordProperty("HasFailure", HasFailure());

        if (HasFatalFailure())
        {
            return;
        }
    }

    FAIL() << "******************** This line code is not reachable ***************************";
}

TEST(CheckResultFuctionTests, CheckingResultFunctionWithAssertNoFatalFailure)
{
    int value = 0;
    while (value < 5)
    {
        char buffer[50];
        sprintf(buffer, "iteration %d", value);

        // This trace point will be included in every failure in this scope.
        SCOPED_TRACE(buffer);
        ASSERT_NO_FATAL_FAILURE(checkResult(++value));
    }

    FAIL() << "******************** This line code is not reachable ***************************";
}

TEST(CheckResultFuctionTests, CustomChecker)
{
    int value = 0;
    while (value < 5)
    {
        ASSERT_TRUE(checkAssertionResult(++value));
    }

    FAIL() << "******************** This line code is not reachable ***************************";
}

