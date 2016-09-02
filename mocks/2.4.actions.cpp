#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

struct ActionTestsMock
{
    MOCK_CONST_METHOD0(voidMethod, void());
    MOCK_CONST_METHOD2(intMethod2, int(int, int));
    MOCK_CONST_METHOD0(intMethod0, const int&());
    MOCK_CONST_METHOD0(factory, int*());
    MOCK_CONST_METHOD1(voidMethod1, void(int*&));
};

TEST(ActionTests, ReturnFromVoid)
{
    ActionTestsMock mock;
    EXPECT_CALL(mock, voidMethod()).WillOnce(Return());
    mock.voidMethod();
}

TEST(ActionTests, ReturnArg)
{
    ActionTestsMock mock;
    EXPECT_CALL(mock, intMethod2(Ge(4), Eq(5))).WillOnce(ReturnArg<0>());
    ASSERT_EQ(8, mock.intMethod2(8, 5));
}

TEST(ActionTests, ReturnPointer)
{
    ActionTestsMock mock;
    EXPECT_CALL(mock, factory()).WillOnce(ReturnNew<int>(3));
    const auto returnValue = mock.factory();
    ASSERT_EQ(3, *returnValue);
    delete returnValue;
}

TEST(ActionTests, ReturnNull)
{
    ActionTestsMock mock;
    EXPECT_CALL(mock, factory()).WillOnce(ReturnNull());
    ASSERT_EQ(nullptr, mock.factory());
}

TEST(ActionTests, ReturnPointee)
{
    ActionTestsMock mock;
    auto temp = 5;
    EXPECT_CALL(mock, intMethod0()).WillOnce(ReturnPointee(&temp));
    const auto& returnValue = mock.intMethod0();
    ASSERT_EQ(returnValue, temp);
    ASSERT_EQ(&returnValue, &temp);
}

TEST(ActionTests, ReturnRef)
{
    ActionTestsMock mock;
    auto temp = 5;
    EXPECT_CALL(mock, intMethod0()).WillOnce(ReturnRef(temp));
    const auto& returnValue = mock.intMethod0();
    ASSERT_EQ(returnValue, temp);
    ASSERT_EQ(&returnValue, &temp);
}

TEST(ActionTests, ReturnRefOfCopy)
{
    ActionTestsMock mock;
    auto temp = 5;
    EXPECT_CALL(mock, intMethod0()).WillOnce(ReturnRefOfCopy(temp));
    const auto& returnValue = mock.intMethod0();
    ASSERT_EQ(returnValue, temp);
    ASSERT_NE(&returnValue, &temp);
}

TEST(ActionTests, SideEffectsWithCompositeActions)
{
    ActionTestsMock mock;
    int* temp = new int{4};
    int* argValue = nullptr;
    // check other side effects on the following link
    // https://github.com/google/googletest/blob/master/googlemock/docs/CheatSheet.md#side-effects
    EXPECT_CALL(mock, voidMethod1(_)).WillOnce(DoAll(SaveArg<0>(&argValue), DeleteArg<0>()));
    mock.voidMethod1(temp);
    ASSERT_EQ(argValue, temp);
}

TEST(ActionTests, FunctionOrFunctorAsAnAction)
{
    ActionTestsMock mock;
    int* temp = new int{4};
    bool isInvoked = false;
    // check other options on the following link:
    // https://github.com/google/googletest/blob/master/googlemock/docs/CheatSheet.md#using-a-function-or-a-functor-as-an-action
    EXPECT_CALL(mock, voidMethod1(_)).WillOnce(Invoke([&isInvoked](int*){isInvoked = true;}));
    mock.voidMethod1(temp);
    delete temp;
    ASSERT_TRUE(isInvoked);
}

ACTION(Sum) { return arg0 + arg1; }
TEST(ActionTests, CustomActions)
{
    ActionTestsMock mock;
    // checko other possibilities on the following link:
    // https://github.com/google/googletest/blob/master/googlemock/docs/CheatSheet.md#defining-actions
    EXPECT_CALL(mock, intMethod2(Ge(4), Eq(5))).WillOnce(Sum());
    ASSERT_EQ(13, mock.intMethod2(8, 5));
}
