#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

struct ExpectationOrder
{
    MOCK_CONST_METHOD0(initX, void());
    MOCK_CONST_METHOD0(initY, void());
    MOCK_CONST_METHOD0(bar, void());
};

TEST(ExpectationOrderTests, AfterClause)
{
    ExpectationOrder foo;

    Expectation init_x = EXPECT_CALL(foo, initX());
    Expectation init_y = EXPECT_CALL(foo, initY());
    EXPECT_CALL(foo, bar())
        .After(init_x, init_y);

    foo.initX();
    foo.initY();
    foo.bar();
}

TEST(ExpectationOrderTests, InSequence)
{
    ExpectationOrder foo;
    Sequence s1, s2;

    EXPECT_CALL(foo, initX())
            .InSequence(s1);
    EXPECT_CALL(foo, initY())
            .InSequence(s2);
    EXPECT_CALL(foo, bar())
            .InSequence(s1, s2);

    foo.initX();
    foo.initY();
    foo.bar();
}
