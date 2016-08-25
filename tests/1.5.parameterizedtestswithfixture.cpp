#include <gtest/gtest.h>

struct TestData
{
    int initial;
    int operand;
    int result;
};

std::ostream& operator<<(std::ostream& os, const TestData& obj)
{
    return os << obj.initial << " op " << obj.operand << " == " << obj.result;
}

struct Fixture : testing::Test
{
    int currentState = 0;
};

struct ParmeterizedTests : Fixture, testing::WithParamInterface<TestData>
{
    void SetUp()
    {
        currentState = GetParam().initial;
    }
};

TEST_P(ParmeterizedTests, DefaultTest)
{
    const auto& testData = GetParam();
    EXPECT_EQ(currentState + testData.operand, testData.result);
}

INSTANTIATE_TEST_CASE_P(Default, ParmeterizedTests,
    testing::Values
    (
        TestData{100, 50, 150},
        TestData{100, 200, 300}
    )
);

INSTANTIATE_TEST_CASE_P(NegativeNumbers, ParmeterizedTests,
    testing::Values
    (
        TestData{-100, -50, -150},
        TestData{-100, -200, -300}
    )
);
