#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

struct UserDefinedStruct
{
    int method() const
    {
        return 5;
    }

    int value;
};

// see matchers.cpp for more examples
TEST(UserDefinedTypeMatchers, UsingMembers)
{
    UserDefinedStruct test{3};
    EXPECT_THAT(test, Field(&UserDefinedStruct::value, 3));
    EXPECT_THAT(&test, Field(&UserDefinedStruct::value, 3));

    EXPECT_THAT(test, Property(&UserDefinedStruct::method, 5));
    EXPECT_THAT(&test, Property(&UserDefinedStruct::method, 5));

    EXPECT_THAT(&test,
        AllOf(
            Property(&UserDefinedStruct::method, 5),
            Field(&UserDefinedStruct::value, 3)
        )
    );
}

MATCHER_P(IsUserTypeStructWithValue, n, "") { return arg.value == n; }
TEST(UserDefinedTypeMatchers, UsingCustomMatcher)
{
    UserDefinedStruct test{3};
    EXPECT_THAT(test, IsUserTypeStructWithValue(3));
}
