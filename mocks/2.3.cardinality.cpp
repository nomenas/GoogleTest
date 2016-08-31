#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

struct CardinalityMock
{
    MOCK_CONST_METHOD0(GetSize, int());
};

TEST(CardinalityTests, TestAnyNumber)
{
    CardinalityMock mock;
    EXPECT_CALL(mock, GetSize()).Times(AnyNumber()).WillRepeatedly(Return(5));

    ASSERT_EQ(5, mock.GetSize());
    ASSERT_EQ(5, mock.GetSize());
    ASSERT_EQ(5, mock.GetSize());
}

TEST(CardinalityTests, TestAtLeast)
{
    CardinalityMock mock;
    EXPECT_CALL(mock, GetSize()).Times(AtLeast(1)).WillRepeatedly(Return(5));

    ASSERT_EQ(5, mock.GetSize());
    ASSERT_EQ(5, mock.GetSize());
    ASSERT_EQ(5, mock.GetSize());
}

TEST(CardinalityTests, TestAtMost)
{
    CardinalityMock mock;
    EXPECT_CALL(mock, GetSize()).Times(AtMost(5)).WillRepeatedly(Return(5));

    ASSERT_EQ(5, mock.GetSize());
    ASSERT_EQ(5, mock.GetSize());
    ASSERT_EQ(5, mock.GetSize());
}

TEST(CardinalityTests, TestBetween)
{
    CardinalityMock mock;
    EXPECT_CALL(mock, GetSize()).Times(Between(1, 5)).WillRepeatedly(Return(5));

    ASSERT_EQ(5, mock.GetSize());
    ASSERT_EQ(5, mock.GetSize());
    ASSERT_EQ(5, mock.GetSize());
}

TEST(CardinalityTests, TestExactly)
{
    CardinalityMock mock;
    EXPECT_CALL(mock, GetSize()).Times(Exactly(3)).WillRepeatedly(Return(5));

    ASSERT_EQ(5, mock.GetSize());
    ASSERT_EQ(5, mock.GetSize());
    ASSERT_EQ(5, mock.GetSize());
}
